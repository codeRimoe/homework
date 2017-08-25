function [vi]=viCount(viType,NIR,RED,BLUE,para)

% help informatiom
%
% This function is use to count Vegetation Index.
%
% author: Luo_Haowen
% usage: [vi]=viCount(viType,NIR,RED,BLUE,para)
% example: ndvi=viCount('NDVI',NIR,RED)
%
% viType       -image data
% NIR          -the NIR band data of image;
% RED          -the RED band data of image;
% BLUE         -the BLUE band data of image, useful only when viType is 'ARVI' or 'EVI';
% para         -the parameter of vi, useful only when viType is 'ARVI' or 'EVI'.
%               input para like this: -para = [L],(when viType is 'ARVI'), L is soil adjustment factor, chosen depends on the density of the vegetation, default 1.
%                                     -para = [L,G,C1,C2],L is soil adjustment factor, G is a gain factor set to 2.5, C1 and C2 is two coefficients, default [1,2.5,6.0,7.5].

    if nargin<4,BLUE=[];end
    if nargin<5,para=[1,2.5,6.0,7.5];end

    if strcmp(viType,'DVI')
        vi = NIR - RED;
    elseif strcmp(viType,'RVI')
        vi = NIR ./ RED;
    elseif strcmp(viType,'NDVI')
        vi = (NIR - RED) ./ (NIR + RED);
    elseif strcmp(viType,'SAVI')
        vi = (1+para(1)) * (NIR - RED) ./ (NIR + RED + para(1));
    elseif strcmp(viType,'ARVI')
        RB = RED - (BLUE - RED) * para(1);
        vi = (NIR - RB) ./ (NIR + RB);
    elseif strcmp(viType,'EVI')
        k = para(2) * ( 1 + para(1) );
        vi = (NIR - RED) ./ (NIR + para(3) * RED - para(4) * BLUE + para(1));
        vi = k * vi;
    end

end
