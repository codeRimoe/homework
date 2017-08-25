function [trans]=pieceLinear(data,para,scale)

% help informatiom
%
% This function is use for image enhancing point operation (Piecewise-Linear transform).
%
% author: Luo_Haowen
% usage: [trans]=pieceLinear(data,para[4][,scale])
% example: trans = pieceLinear( data, [0.5,0,0.5,1])
%
% data    -image data
% para    -input x,y of 2 significant point
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<3,scale=255;end
    if nargin<2,para=[0,0,1,1];end
    dd = stretch(data,1);

    L1 = (dd<=para(1));
    L2 = (dd>para(1)) & (dd<para(3));
    L3 = (dd>=para(3));
    dd(L1) = dd(L1)*para(2)/para(1);
    dd(L2) = (dd(L2) - para(3)) / (para(1) - para(3)) * (para(2) - para(4)) + para(4);
    dd(L3) = (dd(L3) - 1) / (para(3) - 1) * (para(4) - 1) + 1;
    trans=dd;

    trans = scale * trans;

end
