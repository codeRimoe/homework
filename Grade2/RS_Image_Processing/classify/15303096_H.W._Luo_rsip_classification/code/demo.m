format long g 

data=imread('/Users/_nA/Desktop/data/data5/studyarea.tif');
sample=dlmread('/Users/_nA/Desktop/data/data5/sample.csv',',',1,0);

[trainSam,testSam]=stratiSam(sample,0.6);
[sign,accOverall_Accuracy,Kappa,Acc_Table,class]=minDisCla(data,trainSam,testSam);

classRGB(:,:,1)=(class==1)*255+(class==4)*255+(class==5)*255;
classRGB(:,:,2)=(class==2)*255+(class==4)*255;
classRGB(:,:,3)=(class==3)*255+(class==5)*255;

% visualization
imshow(classRGB);
figure;
imshow(data)