function [Brightness,Greenness,Moisture]=kt(data)

% help informatiom
%
% This function is use to count the Brightness, Greenness and Moisture of the image by K-T Transform.
%
% author: Luo_Haowen
% usage: [Brightness,Greenness,Moisture]=kt(data)
% example: [Brightness,Greenness,Moisture]=kt(data)
%
% data       -image data

    Brightness = 0.3561 * data(:,:,1) + 0.3972 * data(:,:,2) + 0.3904 * data(:,:,3) + 0.6966 * data(:,:,4) + 0.2286 * data(:,:,5) + 0.1595 * data(:,:,7);
    Greenness = -0.3344 * data(:,:,1) - 0.3544 * data(:,:,2) - 0.4556 * data(:,:,3) + 0.6966 * data(:,:,4) - 0.0242 * data(:,:,5) - 0.2630 * data(:,:,7);
    Moisture = 0.2626 * data(:,:,1) + 0.2141 * data(:,:,2) + 0.0926 * data(:,:,3) + 0.0656 * data(:,:,4) - 0.7629 * data(:,:,5) - 0.5388 * data(:,:,7);
end
