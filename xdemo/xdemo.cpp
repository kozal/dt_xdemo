#include "../include/xsystem.h"
#include "../include/xdevice.h"
#include "../include/xcommand.h"
#include "../include/xacquisition.h"
#include "../include/xframe_transfer.h"
#include "../include/xgig_factory.h"
#include "../include/xoff_correct.h"
#include "../include/ixcmd_sink.h"
#include "../include/iximg_sink.h"
#include <stdio.h>
#include <iostream>
using namespace std;
uint32_t frame_count = 0;
uint32_t lost_count = 0;

void DisplayMenu()
{
    printf("Please choose one option from following: \n\n");
    printf("1- Find device\n");
    printf("2- Configure device\n");
    printf("3- Open device\n");
    printf("4- Send ASII command\n");
    printf("5- Grab\n");
    printf("6- Stop\n");
    printf("7- Snap\n");
    printf("8- Correct\n");
    printf("9- Close device\n");

    printf("ESC- Exit program\n\n\n");
}

class CmdSink :public IXCmdSink
{
public:
    void OnXError(uint32_t err_id, const char* err_msg_)
    {
    printf("OnXERROR: %u, %s\n", err_id, err_msg_);
    }
    void OnXEvent(uint32_t event_id, float data)
    {
    // switch(event_id)
    // {
    // case XEVENT_CMD_HEARTBEAT_TEMPRA:
    //     printf("X-GCU's temperature: %f\n", data);
    //     break;
    // case XEVENT_CMD_HEARTBEAT_HUMIDITY:
    //     printf("X-GCU's humidity: %f\n",data);
    //     break;
    // }
    }
};

class ImgSink : public IXImgSink
{
    void OnXError(uint32_t err_id, const char* err_msg_)
    {
    printf("OnXERROR: %u, %s\n", err_id, err_msg_);
    }
    void OnXEvent(uint32_t event_id, uint32_t data)
    {
    if(XEVENT_IMG_PARSE_DATA_LOST == event_id ||
        XEVENT_IMG_PARSE_PAC_LOST == event_id)
    {
        lost_count += data;
    }
    }
    void OnFrameReady(XImage* image_)
    {
    printf("Frame %u ready, lost line %u\n", frame_count++, lost_count);
    printf("Firset pixel value: %u\n", image_->GetPixelVal(0,0));
    }
};

CmdSink cmd_sink;
ImgSink img_sink;
int main()
{
    char host_ip[20];
    // printf("Please input IP address of network adapter:\n");
    // cin>>host_ip;
    strcpy(host_ip, "192.168.2.5");

    XSystem xsystem(host_ip);
    XDevice* dev_ = NULL;
    int32_t dev_num = 0;
    char dev_ip[20];
    uint16_t dev_cmd_port;
    uint16_t dev_img_port;
    xsystem.RegisterEventSink(&cmd_sink);    

    XGigFactory xfactory;
    XCommand xcommand(&xfactory);
    xcommand.RegisterEventSink(&cmd_sink);
    
    XFrameTransfer xtransfer(512); //Frame has 512 lines
    xtransfer.RegisterEventSink(&img_sink);

    XAcquisition xacq(&xfactory);
    xacq.RegisterEventSink(&img_sink);
    xacq.RegisterFrameTransfer(&xtransfer);
    xacq.EnableLineInfo(1);

    XOffCorrect xoff_correct;
    string send_str;
    string recv_str;
    char recv_buffer[1024];
    
    DisplayMenu();
    int input_char;
    do
    {
    printf("Please enter option. \n");
    input_char = getchar();

    switch(input_char)
    {
    case '1':

        if(!xsystem.Open())
        return 0;

        dev_num = xsystem.FindDevice();
        if(dev_num <= 0)
        {
        printf("No device found.\n ");
        return 0;
        }
        //Get the first device
        dev_= xsystem.GetDevice(0);
        printf("X-GCU: IP %s, Cmd Port %d, Img Port %d\n",
           dev_->GetIP(),
           dev_->GetCmdPort(),
           dev_->GetImgPort());
        break;
    case '2':
        printf("Please input device IP\n");
        cin>>dev_ip;
        printf("Please input device cmd port\n");
        cin>>dev_cmd_port;
        printf("Please input device img port\n");
        cin>>dev_img_port;

        if(dev_)
        {
        dev_->SetIP(dev_ip);
        dev_->SetCmdPort(dev_cmd_port);
        dev_->SetImgPort(dev_img_port);
        }
        if(1 == xsystem.ConfigureDevice(dev_))
        {
        printf("Configure device successfully, please find device again\n");
        }
        else
        printf("Fail to configure device\n");
        
        break;
    case '3':
        if(xcommand.Open(dev_))
        {
        printf("Command channel open successfully\n");
        if(xacq.Open(dev_, &xcommand))
        {
            printf("Image channel open successfully\n");
            xoff_correct.Open(dev_);
        }
        else
            printf("Image channel fail to open\n");
        }
        else
        printf("Command channel fail to open\n");

        break;
    case '4':
        printf("Please enter ASCII command:\n");
        cin>>send_str;
        // xcommand.SendAscCmd(send_str, recv_str);
        // xcommand.SendAscCmd(send_str.c_str(), recv_str);
        // xcommand.SendAscCmd(send_str, recv_buffer);
        // xcommand.SendAscCmd(send_str.c_str(), recv_buffer);
        xcommand.SendAscCmd( (char*)send_str.c_str(), (char*)recv_buffer); 
        recv_str = recv_buffer;
        printf("Device feedback %s\n", recv_str.c_str());
        break;
    case '5':
        printf("Start grabbing\n");
        frame_count = 0;
        lost_count = 0;
        xacq.Grab(0);
        break;
    case '6':
        printf("Stop grabbing\n");
        xacq.Stop();
        break;
    case '7':
        printf("Snap one fram \n");
        xacq.Snap();
        break;
    case '8':
        printf("Please turn off X-Ray\n");
        xoff_correct.Reset();
        sleep(5);
        //Calculate offset
        xoff_correct.CalculatePara(1, &xacq, &xtransfer,0);
        printf("Please turn on X-Ray\n");
        sleep(5);
        //Calculate gain to target of 50000
        xoff_correct.CalculatePara(0, &xacq, &xtransfer, 5000);

        //Save gain/offset to flash
        xcommand.StopHeartbeat();
        xoff_correct.SaveFlash(&xcommand, 0);
        xcommand.StartHeartbeat();

        //Enable gain/offset correct
        xcommand.SetPara(XPARA_EN_GAIN_CORRECT, 1);
        xcommand.SetPara(XPARA_EN_OFFSET_CORRECT, 1);
        break;
    case '9':
        printf("Close device\n");
        xoff_correct.Close();
        xacq.Close();
        xcommand.Close();
        break;
    default:
        break;
    }
    }while(input_char != 27);
    xoff_correct.Close();
    xacq.Close();
    xcommand.Close();
    xsystem.Close();
    return 1;
}
