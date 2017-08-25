function [trans]=histogramEqu(data,scale)

% help informatiom
%
% This function is use for image enhancing point operation (Histogram equalization).
%
% author: Luo_Haowen
% usage: [trans]=histogramEqu(data,type[,scale])
% example: trans = histogramEqu(data)
%
% data    -image data
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<4,scale=255;end
    if nargin<3,para=[0,0,1,1];end
    dd = stretch(data,1);

    m = 1;
    tempsize = size(dd);
    tsize = size(tempsize);
    if (tsize(2)==3)
        m=tempsize(3);
    end
    for i=1:m
        im=dd(:,:,i);
        trans(:,:,i)=histeq(im);
    end
    
    trans = scale * trans;

end
