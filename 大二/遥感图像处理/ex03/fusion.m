function [R,G,B]=fusion(low,highI)

% help informatiom
%
% This function is use to fusion with 2 Image.
%
% author: Luo_Haowen
% usage: [R,G,B]=fusion(low,highI)
% example: [R,G,B]=fusion(TM,SPOT)
%
% low       -low resolution image data(3 band,[R,G,B])
% highI     -high resolution image data(1 band only)

    sss=size(highI);
    x=sss(1);
    y=sss(2);
    low=reraster(low,x,y);
    R=low(:,:,1);
    G=low(:,:,2);
    B=low(:,:,3);
    [H,I,S]=rgb2his(R,G,B);
    [R,G,B]=his2rgb(H,highI,S);
end
