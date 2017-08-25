img=imread('C:\Users\SYSU\Desktop\data5\studyarea.TIF');
im=img(:,:,1);
BW=edge(im,'sobel');

% hough-line
[H, theta, rho] = hough(BW);
P = houghpeaks(H,6);
lines = houghlines(BW,theta,rho,P,'FillGap', 30);

imshow(img);hold on
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
end

% hough-circle
[centers, radii, metric] = imfindcircles(im,[10 50]);
viscircles(centers, radii,'EdgeColor','b');

clear

% Watershed segmentation ¨C tree detection
 [A,header,ncols,nrows,xllcorner,yllcorner,cellsize,nodata]=imreadasc('C:\Users\SYSU\Desktop\data5\chm.asc');
SE = strel('square', 5);
B=imclose(A,SE);
BT=max(B(:))-B;
L=watershed(BT);
SS=size(L)
x=[];
y=[];
for xx = 1:SS(1)
    for yy=1:SS(2)
        if L(xx,yy)==0
            x=[x,xx];
            y=[y,yy];
        end
    end
end
imshow(B/max(B(:)));
hold
plot(y,x,'.','markersize',3);