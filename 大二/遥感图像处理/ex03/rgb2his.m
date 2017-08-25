function [H,I,S]=rgb2his(R,G,B)

% help informatiom
%
% This function is use to transform image color style from RGB to HIS.
%
% author: Luo_Haowen
% usage: [H,I,S]=rgb2his(R,G,B)
% example: [H,I,S]=rgb2his(R,G,B)

    I=(R+G+B)./3.0;
    r=R./3.0./I;
    g=G./3.0./I;
    b=B./3.0./I;
    sss=size(R);
    for i=1:sss(1)
        for j=1:sss(2)
            X(i,j)=min([r(i,j),g(i,j),b(i,j)]);
        end
    end
    H=acos(((r-g)+(r-b))./(2*sqrt((r-g).^2+(r-b).*(g-b))));
    if  b>g
        H=2*pi-H;
    end
    S=1-3*X;
end
