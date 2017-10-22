function [out]=reraster(data,x,y)

% help informatiom
%
% This function is use to reset the size of the raster.
%
% author: Luo_Haowen
% usage: [out]=reraster(data,x,y)
% example: [new data]=reraster(data,520,1206)
%
% data       -image data
% x          -pix number of a col in new data;
% y          -pix number of a row in new data.

    inSize=size(data);
    band=1;
    sss=size(inSize);
    if sss(2)==3
        band=inSize(3);
    end
    out=zeros(x,y);
    k1=double(x)/inSize(1);
    k2=double(y)/inSize(2);
    for b=1:band
        for i=1:x
            for j=1:y
                rr=1+round(i/k1);
                cc=1+round(j/k2);
                if rr>inSize(1)
                    rr=inSize(1);
                end
                if cc>inSize(2)
                    cc=inSize(2);
                end
                out(i,j,b)=data(rr,cc,b);
            end
        end
    end
end
