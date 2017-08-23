cd 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\matlab'

clearvars;
close all;
clc;

img_folder = 'C:\Users\yusuf\Desktop\xview_ubuntu\dt_xdemo\xdemo\img\';
[image_16, base_name] = load_img_txt(img_folder);
%% properties
num_DMs = 10;
total_pix_num = num_DMs * 128;
rows_to_show = 1:800;

%% check file
if (total_pix_num ~= size(image_16,2))
    errordlg('Image does not match total_pix_num','File Error');
    error('Error: Image does not match total_pix_num.')
end

%% display file
figure,
subplot(1,3,1),
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
%%
% figure,
% % subplot(1,3,2),
% % imagesc(img_lo_en(1:800,1:64*9)), title('low eng')
% imagesc(img_lo_en), title('low eng')
% colormap gray, axis image
%%
% overlap_lines = [65, 129, 193, 257, 321, 322, 385, 448, 512, 576, (num_DMs-1)*64+1:(num_DMs)*64];
overlap_lines = [65, 129, 193, 257, 321, 322, 385, 448, 512, 576];
img_lo_no_ol = img_lo_en;
img_lo_no_ol(:,overlap_lines)=[];
figure,
imagesc(img_lo_no_ol(rows_to_show,:)), title('low eng')
colormap gray, axis image
img_hi_no_ol = img_hi_en;
img_hi_no_ol(:,overlap_lines)=[];
figure,
imagesc(img_hi_no_ol(rows_to_show,:)), title('hi eng')
colormap gray, axis image
%%
% figure,
% imshow(img_lo_no_ol(rows_to_show,:)), title('low eng')
% colormap gray, axis image; impixelinfo
% figure,
% imshow(img_hi_no_ol(rows_to_show,:)), title('hi eng')
% colormap gray, axis image; impixelinfo
