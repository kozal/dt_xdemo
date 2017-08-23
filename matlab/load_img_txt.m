function [ image_16, base_name ] = load_img_txt(img_folder)
%load_img_txt Loads the image file with txt extension capturet with DT
%   Detailed explanation goes here

% save the current path
main_path = pwd;
% go to image path
% img_folder = 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\xdemo\img\';
cd(img_folder)
[FileName, PathName] = uigetfile({'*.txt','Select the Image File'},...
    'Select the MATLAB code file');
if isequal(FileName,0)
   disp('User selected Cancel')
else
   disp(['User selected ', fullfile(PathName, FileName)])
end
cd(main_path)
C = strsplit(FileName,'.txt');

load(fullfile(PathName, FileName))
image_16 = uint16(eval(C{1}));
% image_16 = uint16(C(1));
base_name = C{1};

end


%% load file
% % img_folder = '..\dt_xdemo\xdemo\img';
% % base_name = 'seasoning10';
% % base_name = 'capture_file';
% % base_name = 'test_160';
% base_name = 'test_nine';
% % base_name = 'seasoning';
% % base_name = 'seasoning2';
% img_folder = 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\xdemo\img';
% % base_name = 'd1_test_d2_norm';
% % base_name = 'd2_test_d1_norm';
% % base_name = 'he01_le12';
% % base_name = 'he12_le01';
% base_name_1 = sprintf('%s_1', base_name);
% baseFileName = sprintf('%s_1.txt', base_name);
% fullFileName = fullfile(img_folder, baseFileName);
% if not(exist(fullFileName, 'file'))
%     message = sprintf('%s does not exists!!!', fullFileName);
%     errordlg(message,'File Error');
%     error('Error: File Error.')
% end
% 
% load(fullFileName)
% image_16 = uint16(eval(base_name_1));