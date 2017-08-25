% Extract the three largest squares in the image
data=imread('/Users/_nA/Desktop/data/data4/binary/squares.tif');
SE = strel('square', 10);
im=imopen(data,SE);
subplot(1,2,1);
imshow(data);
subplot(1,2,2);
imshow(im);
disp('Press any key to continue');
pause;

% Remove the salt-and-pepper noise
data=imread('/Users/_nA/Desktop/data/data4/binary/fingerprint.tif');
SE = strel('square', 3);
im=imopen(data,SE);
im=imclose(im,SE);
subplot(1,2,1);
imshow(data);
subplot(1,2,2);
imshow(im);
disp('Press any key to continue');
pause;

% Boundary extraction
data=imread('/Users/_nA/Desktop/data/data4/binary/utk.tif');
SE = strel('square', 3);
im=imerode(data,SE);
im=data-im;
subplot(1,2,1);
imshow(data);
subplot(1,2,2);
imshow(im);
disp('Press any key to continue');
pause;

% Region filling
data=imread('/Users/_nA/Desktop/data/data4/binary/coin.tif');
data=data(:,:,1);
Cdata=~data;
SE=strel('disk', 1);
X=zeros(size(data));
Y=zeros(size(data));
X(20,20)=1;
while ~isequal(X,Y)
    Y=X;
    X=(imdilate(Y,SE)&Cdata);
end
X=~X;
subplot(1,2,1);
imshow(data);
subplot(1,2,2);
imshow(X*255);
disp('Press any key to continue');
pause;

% Labeling connected components
data=imread('/Users/_nA/Desktop/data/data4/binary/objects.tif');
px=[60,115,180,45,115,180,120,50,120,190];
py=[50,50,50,120,120,120,170,220,220,220];
SE=strel('disk', 1);
im=zeros(size(data));
for i=1:10
    X=zeros(size(data));
    Y=zeros(size(data));
    X(py(i),px(i))=1;
    while ~isequal(X,Y)
        Y=X;
        X=(imdilate(Y,SE)&data);
    end
    im=im+X.*i;
end
subplot(1,2,1);
imshow(data);
subplot(1,2,2);
imshow(im);
disp('Press any key to continue');
pause;

% Morphological gradient
data=imread('/Users/_nA/Desktop/data/data4/gray/aerial.tif');
SE = strel('square', 3);
gd=imdilate(data,SE);
ge=imerode(data,SE);
mg=gd-ge;
subplot(2,2,1);
imshow(data);
subplot(2,2,2);
imshow(mg);
subplot(2,2,3);
imshow(gd);
subplot(2,2,4);
imshow(ge);
disp('Press any key to continue');
pause;

% Open-close filtering
% Close-open filtering
imoc=imopen(data,SE);
imoc=imclose(imoc,SE);
imco=imclose(data,SE);
imco=imopen(imco,SE);
subplot(1,3,1);
imshow(data);
subplot(1,3,2);
imshow(imoc);
subplot(1,3,3);
imshow(imco);
disp('Press any key to continue');
pause;
