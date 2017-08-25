function []=imgshow(data,rgbBand)

% help informatiom
%
% This function is use to show a image.
%
% author: Luo_Haowen
% usage: []=imgshow(data, rgbBand)
% example: imgshow(data,[4,3,2])
%
% data    -the image data, you can read it from a image file by using function "imgopen"
% rgbBand -the Bands/Layers you want to show, you can input one number to show the only Band, or input 3 bands [Red, Green, Blue] to composite.
    if nargin<2,rgbBand=1;end
    im=data(:,:,rgbBand);
    imshow(im/max(data(:)));

end
