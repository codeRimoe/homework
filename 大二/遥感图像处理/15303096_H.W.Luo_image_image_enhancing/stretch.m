function [trans]=stretch(data,scale)

% help informatiom
%
% This function is use to strerch image.
%
% author: Luo_Haowen
% usage: [trans]=stretch(data[,scale])
% example: trans = stretch(data)
%
% data    -image data
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<2,scale=255;end
    trans = scale*(data-min(data(:)))/(max(data(:))-min(data(:)));
end
