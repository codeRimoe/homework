function [trans]=powTran(data,para,scale)

% help informatiom
%
% This function is use for image enhancing point operation (Power-function transform).
%
% author: Luo_Haowen
% usage: [trans]=powTran(data,para[,scale])
% example: trans = powTran( data, 1.5)
%
% data    -image data
% para    -input exponent
% scale   -the range of the DN value,set max DN value,[default 255]

    if nargin<3,scale=255;end
    if nargin<2,para=1;end
    dd = stretch(data,1);

    trans = (dd).^para;

    trans = scale * trans;

end
