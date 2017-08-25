function [trans]=smooth(data,type,r,para,scale)

% help informatiom
%
% This function is use for image enhancing local operation (smoothing).
% The shape of filter is square only.
%
% author: Luo_Haowen
% usage: [trans]=smooth(data,type,r,para,scale)
% example: trans = smooth(data,1,1,1)
%
% data    -image data
% type    -filter type,(1:Averaging filter; 2:Median filter; 3:Gaussian filter)
% r       -filter radius,[default 1]
% para    -useful only when type = 3,input SD of Gaussian function,[default 1]
% scale   -the range of the DN value,set max DN value,[default 255]

if nargin<5,scale=255;end
    if nargin<4,para=1;end
    if nargin<3,r=1;end
    dd = stretch(data,1);
    r=2*r+1;
    filter = zeros(r,r);

    % 1:power-function transform
    if (type == 1)
        for i=1:r
            for j=1:r
                filter(i,j)=1/r/r;
            end
        end
    end

    % 3:logarithmic-log
    if (type == 3)
        s = 0;
        for i=1:r
            for j=1:r
                x = i-(r+1)/2;
                y = j-(r+1)/2;;
                n = -(x*x+y*y)/2/para/para;
                filter(i,j)=exp(n)/2/3.14159/para/para;
                s=s+filter(i,j);
            end
        end
        for i=1:r
            for i=1:r
                filter(i,j)=filter(i,j)/s;
            end
        end
    end

    m = 1;
    tempsize = size(dd);
    tsize = size(tempsize);
    if (tsize(2)==3)
        m=tempsize(3);
    end
    
    % 2:linear-image negatives
    if (type == 2)
        for k=1:m
            trans(:,:,k) = medfilt2(dd(:,:,k), [r r]);
        end
    else
        trans = imfilter(dd,filter);
    end

    trans = scale * trans;

end
