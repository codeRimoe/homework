function [trans]=sharpen(data,type,para,scale)

% help informatiom
%
% This function is use for image enhancing local operation (sharpening).
% The shape of filter is 3*3 square only.
%
% author: Luo_Haowen
% usage: [trans]=sharpen(data,type,para,scale)
% example: trans = sharpen(data,2,3)
%
% data    -image data
% type    -filter type,(1:Sobel filter; 2Laplacian filter)
% para    -direction 1:normal 2:rotated 3:all-direction
% scale   -the range of the DN value,set max DN value,[default 255]

if nargin<4,scale=255;end
    if nargin<3,para=3;end
    dd = stretch(data,1);

    % 1:Sobel filter
    if (type == 1)
        filter(:,:,1) = [1,2,1;0,0,0;-1,-2,-1];
        filter(:,:,2) = [1,0,-1;2,0,-2;1,0,-1];
        filter(:,:,3) = sqrt(filter(:,:,1).^2+filter(:,:,2).^2);
    end

    % 2:Laplacian filter
    if (type == 2)
        filter(:,:,1) = [0,-1,0;-1,4,-1;0,-1,0];
        filter(:,:,2) = [-1,0,-1;0,4,0;-1,0,-1];
        filter(:,:,3) = filter(:,:,1)+filter(:,:,2);
    end

    trans = dd+imfilter(dd,filter(:,:,para));

    trans = scale * trans;

end
