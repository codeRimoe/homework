function [trans]=linearNeg(data)

% help informatiom
%
% This function is use for image enhancing point operation（linear-image negatives）.
%
% author: Luo_Haowen
% usage: [trans]=linearNeg(data[,scale])
% example: trans = linearNeg(data)
%
% data    -image data
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<2,scale=255;end
    dd = stretch(data,1);

    trans = 1 - dd;

    trans = scale * trans;

end
