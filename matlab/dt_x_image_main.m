cd 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\matlab'

clearvars;
close all;
clc;
%% properties
% num_DMs = 2;
total_pix_num = 256;

%% load file
% img_folder = '..\dt_xdemo\xdemo\img';
img_folder = 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\xdemo\img';
% base_name = 'd1_test_d2_norm';
% base_name = 'd2_test_d1_norm';
base_name = 'he01_le12';
% base_name = 'he12_le01';
base_name_1 = sprintf('%s_1', base_name);
baseFileName = sprintf('%s_1.txt', base_name);
fullFileName = fullfile(img_folder, baseFileName);
if not(exist(fullFileName, 'file'))
    message = sprintf('%s does not exists!!!', fullFileName);
    errordlg(message,'File Error');
    error('Error: File Error.')
end

load(fullFileName)
image_16 = uint16(eval(base_name_1));

%% check file
if (total_pix_num ~= size(image_16,2))
    errordlg('Image does not match total_pix_num','File Error');
    error('Error: Image does not match total_pix_num.')
end

%% display file
% figure,
subplot(1,3,1),
% imagesc(image_16,[50 50000]); colormap(gray);
imagesc(image_16), title(base_name)
% imshow(image_16), title(base_name)
colormap gray, axis image

% image_dbl = falan_1/max(falan_1(:));
% figure, image(image_dbl); colormap gray;

%% calibrate
% self_calibrate = true;  % calibrate with pixels in the image
% [image_16_clb, mean_white] = func_calibrate_xray(image_16, self_calibrate);
% figure, imagesc(image_16_clb); colormap(gray);

%% separate low and high
img_lo_en = image_16(:,1:total_pix_num/2);
img_hi_en = image_16(:,total_pix_num/2+1:end);

% figure,
subplot(1,3,2),
imagesc(img_lo_en), title('low eng')
colormap gray, axis image
% figure,
subplot(1,3,3),
imagesc(img_hi_en), title('high eng')
colormap gray, axis image
