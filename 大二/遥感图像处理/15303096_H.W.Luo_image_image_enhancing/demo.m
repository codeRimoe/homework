% This Script is use for testing
% author: Luo_Haowen

fN = '/Users/_nA/Desktop/data1/tm_bil';
fNnew = '/Users/_nA/Desktop/data1/trans_bil';
fsize = [804,523,7];
iL = 'bil';
dT = 'uint8';
mFM = 'l';
rgbBand = [4,3,2];
pie=[0.5,0,0.5,1];

data = imgopen(fN,fsize,iL,dT,mFM);
figure;
disp('Original');
imgshow(data,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans = linearNeg(data);
figure;
disp('LinearNegative');
imgshow(trans,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans = logTran(data);
figure;
disp('LogTran');
imgshow(trans,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans = pieceLinear(data,[0.3,0,0.8,1]);
figure;
disp('PieceLinear');
imgshow(trans,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans = power(data,0.7);
figure;
disp('0.7 power');
imgshow(trans,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans1 = sharpen(data,1,1);
trans2 = sharpen(data,1,2);
trans3 = sharpen(data,1,3);
figure;
subplot(2,2,1);
imgshow(data,rgbBand);
subplot(2,2,2);
imgshow(trans3,rgbBand);
subplot(2,2,3);
imgshow(trans1,rgbBand);
subplot(2,2,4);
imgshow(trans2,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans1 = histogramEqu(trans1);
trans2 = histogramEqu(trans2);
trans3 = histogramEqu(trans3);
figure;
subplot(2,2,1);
imgshow(data,rgbBand);
subplot(2,2,2);
imgshow(trans3,rgbBand);
subplot(2,2,3);
imgshow(trans1,rgbBand);
subplot(2,2,4);
imgshow(trans2,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans1 = sharpen(data,2,1);
trans2 = sharpen(data,2,2);
trans3 = sharpen(data,2,3);
figure;
subplot(2,2,1);
imgshow(data,rgbBand);
subplot(2,2,2);
imgshow(trans3,rgbBand);
subplot(2,2,3);
imgshow(trans1,rgbBand);
subplot(2,2,4);
imgshow(trans2,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans1 = histogramEqu(trans1);
trans2 = histogramEqu(trans2);
trans3 = histogramEqu(trans3);
figure;
subplot(2,2,1);
imgshow(data,rgbBand);
subplot(2,2,2);
imgshow(trans3,rgbBand);
subplot(2,2,3);
imgshow(trans1,rgbBand);
subplot(2,2,4);
imgshow(trans2,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

trans1 = smooth(data,1,3);
trans2 = smooth(data,2,2);
trans3 = smooth(data,3,1,1.5);
figure;
subplot(2,2,1);
imgshow(data,rgbBand);
subplot(2,2,2);
imgshow(trans3,rgbBand);
subplot(2,2,3);
imgshow(trans1,rgbBand);
subplot(2,2,4);
imgshow(trans2,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')

imgsave('/Users/_nA/Desktop/data1/trans_bil1',trans1,fsize,'bsq',dT,mFM);
imgsave('/Users/_nA/Desktop/data1/trans_bil2',trans2,fsize,'bip',dT,mFM);
imgsave('/Users/_nA/Desktop/data1/trans_bil3',trans3,fsize,'bil',dT,mFM);

data1 = imgopen('/Users/_nA/Desktop/data1/trans_bil1',fsize,'bsq',dT,mFM);
imgshow(data1,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')
data1 = imgopen('/Users/_nA/Desktop/data1/trans_bil2',fsize,'bip',dT,mFM);
imgshow(data1,rgbBand);
disp('please check the image, press enter to continue.')
pause                                     % wait and check the imgshow
disp('counting...')
data1 = imgopen('/Users/_nA/Desktop/data1/trans_bil3',fsize,'bil',dT,mFM);
imgshow(data1,rgbBand);
