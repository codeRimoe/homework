function [out]=pca(data,para,per)

% help informatiom
%
% This function is use to PCA Transform.
%
% author: Luo_Haowen
% usage: [out]=pca(data,para,per)
% example: [PCAdata]=pca(data,99,'%')
% example: [PCAdata]=pca(data,4)
%
% data       -image data
% para       -the data you want to retent,input band number of percent;
% per        -if retent data by percentage,input '%',else if retent data by band number,input 'b' or ignore.

    if nargin<3,per='b';end
    inSize=size(data);
    dataSet=reshape(data,[],inSize(3));
    meanSet=mean(dataSet);
    moveSet=bsxfun(@minus,dataSet,meanSet);
    covMtr=cov(moveSet);
    [V,D]=eig(covMtr);
    lll=size(V);
    lll=lll(1);
    V=V';
    for i=1:lll
        V(i,lll+1)=D(i,i);
    end
    V=sortrows(V,-lll-1);
    D=[];
    D=V(:,lll+1);
    D=100*D./sum(D);
    V(:,lll+1)=[];
    if strcmp(per,'%')
        sss=0;
        for i=1:lll
            sss=sss+D(i);
            if sss>para
                para=i;
                break;
            end
        end
    end
    for i=1:para
        VX(i,:)=V(i,:);
    end
    dataSet=abs(dataSet*VX');
    out=[];
    for i=1:para
        out(:,:,i)=reshape(dataSet(:,i),inSize(1),inSize(2));
    end
end
