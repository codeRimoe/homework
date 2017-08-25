% This Script is use for testing
% author: Luo_Haowen

fN = '/Volumes/NO_NAME/g2_spring/rs/data/data1/tm_bil';
dsize = [804,523,7];
iL = 'bil';
dT = 'uint8';
mFM = 'l';
rgbBand = [4,3,2];
band = [4,3];

data = imgopen(fN,dsize,iL,dT,mFM);
imgshow(data,rgbBand);
disp('original\nplease check the image, press enter to continue.')
pause                                     % wait and check the imgshow
imgscat(data,2,band);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
imgscat(data,3,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow

BLUE=data(:,:,1);
RED=data(:,:,3);
NIR=data(:,:,4);

dvi=viCount('DVI',NIR,RED);
rvi=viCount('RVI',NIR,RED);
ndvi=viCount('NDVI',NIR,RED);
savi=viCount('SAVI',NIR,RED,BLUE);
evi=viCount('EVI',NIR,RED,BLUE);
imgshow(dvi);
disp('please check the image DVI, press enter to continue.')
pause                                     % wait and check the imgshow
imshow(rvi/mean(rvi(:))/2);
disp('please check the image RVI, press enter to continue.')
pause                                     % wait and check the imgshow
imgshow(ndvi);
disp('please check the image NDVI, press enter to continue.')
pause                                     % wait and check the imgshow
imgshow(savi);
disp('please check the image SAVI, press enter to continue.')
pause                                     % wait and check the imgshow
imshow(evi,[-2 2]);
disp('please check the image EVI, press enter to continue.')
pause                                     % wait and check the imgshow

pca1=pca(data,98,'%');
subplot(2,2,1);
imgshow(pca1,1);
subplot(2,2,2);
imgshow(pca1,2);
subplot(2,2,3);
imgshow(pca1,3);
disp('please check the image PCA(98%), press enter to continue.')
pause                                     % wait and check the imgshow

pca2=pca(data,4);
subplot(2,2,1);
imgshow(pca2,1);
subplot(2,2,2);
imgshow(pca2,2);
subplot(2,2,3);
imgshow(pca2,3);
subplot(2,2,4);
imgshow(pca2,4);
disp('please check the image PCA(4-band), press enter to continue.')
pause                                     % wait and check the imgshow

[Brightness,Greenness,Moisture]=kt(data);
imgshow(Brightness);
disp('please check the image(KT-Brightness), press enter to continue.')
pause                                     % wait and check the imgshow
imgshow(Greenness);
disp('please check the image(KT-Greenness), press enter to continue.')
pause                                     % wait and check the imgshow
imgshow(Moisture);
disp('please check the image(KT-Moisture), press enter to continue.')
pause                                     % wait and check the imgshow

TMfN = '/Volumes/NO_NAME/g2_spring/rs/data/data3/TM_SPOT/lon_tm';
TMsize = [1007,560,3];
SPfN = '/Volumes/NO_NAME/g2_spring/rs/data/data3/TM_SPOT/lon_spot';
SPsize = [2820,1569,1];
iL='bil';
TM = imgopen(TMfN,TMsize,iL,dT,mFM);
SP = imgopen(SPfN,SPsize,iL,dT,mFM);
[F1,F2,F3] = fusion(TM,SP);
FUS(:,:,1)=F3;
FUS(:,:,2)=F2;
FUS(:,:,3)=F1;
subplot(1,2,1);
imgshow(TM,[3 2 1]);
subplot(1,2,2);
imgshow(SP);
figure;
imgshow(FUS,[3,2,1]);
disp('please check the image(Fusion), press enter to continue.')
