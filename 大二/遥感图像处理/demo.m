format long g 

data=imread('C:\Users\SYSU\Desktop\data5\studyarea.tif');

% visualization
imshow(data)
figure;
imshow(data(:,:,1))
figure;
imshow(data(:,:,2))
figure;
imshow(data(:,:,3))
