// #include "../include/xsystem.h"
// #include "../include/xdevice.h"
// #include "../include/xcommand.h"
// #include "../include/xacquisition.h"
// #include "../include/xframe_transfer.h"
// #include "../include/xgig_factory.h"
// #include "../include/xoff_correct.h"
// #include "../include/ixcmd_sink.h"
// #include "../include/iximg_sink.h"

#include "inc/diag2.h"
#include <stdio.h>
#include <iostream>

//extern XCommand xcommand;

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

void DisplayMenu2()
{
    printf("Please choose one option from following: \n\n");
    printf("1- Find device\n");
    printf("3- Open device\n");
    printf("4- Send ASII command\n");
    printf("9- Close device\n");
    printf("ESC- Exit program\n\n\n");
    uint64_t temp_prt = 0;
    //xcommand.GetPara(XPARA_INT_TIME, temp_prt);
    printf("Integration Time :%lu \n", temp_prt);
    
}


void handle_error_msg(uint32_t err_id)
{
    switch (err_id)
    {
        case 4:
            printf("Ensure network adapter is connected \n");
            printf("Ensure X-GCU is powered on \n");
            // printf("Ensure X-GCU is turned on \n");
            break;
        default:
            printf("error id is %u \n", err_id);
            break;
    }
}
