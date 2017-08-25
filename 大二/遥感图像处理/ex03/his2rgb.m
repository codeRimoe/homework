function [R,G,B]=his2rgb(H,I,S)

% help informatiom
%
% This function is use to transform image color style from HIS to RGB.
%
% author: Luo_Haowen
% usage: [R,G,B]=his2rgb(H,I,S)
% example: [R,G,B]=his2rgb(H,I,S)

    L1=(H>0)&(H<2*pi/3);
    L2=(H>2*pi/3)&(H<4*pi/3);
    L3=(H>4*pi/3)&(H<2*pi);
    r(L1)=((S(L1).*cos(H(L1))./cos(pi/3-H(L1)))+1)./3.0;
    b(L1)=(1-S(L1))./3.0;
    g(L1)=1-r(L1)-b(L1);
    g(L2)=((S(L2).*cos(H(L2)-2.*pi/3)./cos(pi-H(L2)))+1)./3.0;
    r(L2)=(1-S(L2))./3.0;
    b(L2)=1-r(L2)-g(L2);
    b(L3)=((S(L3).*cos(H(L3)-4.*pi/3)./cos(5.*pi/3-H(L3)))+1)./3.0;
    g(L3)=(1-S(L3))./3.0;
    r(L3)=1-g(L3)-b(L3);
    sss=size(I);
    r=reshape(r,sss(1),sss(2));
    g=reshape(g,sss(1),sss(2));
    b=reshape(b,sss(1),sss(2));
    R=3*r.*I;
    G=3*g.*I;
    B=3*b.*I;
end
