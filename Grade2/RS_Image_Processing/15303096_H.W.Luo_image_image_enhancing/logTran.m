function [trans]=logTran(data,scale)

% help informatiom
%
% This function is use for image enhancing point operation (logarithmic-log).
%
% author: Luo_Haowen
% usage: [trans]=logTran(data[,scale])
% example: trans = logTran(data)
%
% data    -image data
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<2,scale=255;end
    dd = stretch(data,1);

    trans = log(1+dd);
    
    trans = scale * trans;

end
