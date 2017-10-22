function [sign,Overall_Accuracy,Kappa,Acc_Table,class]=minDisCla(data,trainSam,testSam)
    nrows=size(data,1);
    ncols=size(data,2);
	nclass=size(trainSam,2);
	nsign=size(trainSam{1},2);
	sign=[];
	for i=1:nclass
	    for j=9:nsign
	        sign(i,j-8)=mean(trainSam{i}(:,j));
		end
	end
	
	acc=zeros(nclass,nclass);
	for i=1:nclass
	    ntest=size(testSam{1},1);
	    for j=1:ntest
			feature=double(testSam{i}(j,9:nsign));
	        type=classify(sign,feature);
			acc(type,i)=acc(type,i)+1;
		end
    end
    
	Acc_Table=acc;
    Acc_Table(nclass+1,:)=sum(Acc_Table);
    Acc_Table(:,nclass+1)=sum(Acc_Table,2);
    Acc_Table(:,nclass+2)=Acc_Table(:,nclass+1)/Acc_Table(nclass+1,nclass+1);
    Acc_Table(nclass+2,:)=Acc_Table(nclass+1,:)/Acc_Table(nclass+1,nclass+1);
    tempM=(diag(Acc_Table))'./Acc_Table(nclass+1,:);
    Acc_Table(:,nclass+3)=diag(Acc_Table)./Acc_Table(:,nclass+1);
    Acc_Table(nclass+3,:)=[tempM,0];
    Overall_Accuracy=sum(diag(acc))/Acc_Table(nclass+1,nclass+1)
    Acc_Table(nclass+2,nclass+2)=Overall_Accuracy;
    Acc_Table(nclass+2,nclass+3)=sum(Acc_Table(nclass+2,1:5).*(Acc_Table(1:5,nclass+2))');
    pre=Acc_Table(nclass+2,nclass+3);
    Acc_Table(nclass+3,nclass+2)=pre;
    Kappa=(Overall_Accuracy-pre)/(1-pre)
    Acc_Table(nclass+3,nclass+3)=Kappa
%     roundn(Acc_Table,-4);
 	data=double(data);
 	class=zeros(nrows,ncols);
	for i=1:nrows
	    for j=1:ncols
		    for k=1:(nsign-8)
			    feature(k)=double(data(i,j,k));
            end
                class(i,j)=classify(sign,feature);
		end
    end
end

function [type]=classify(sign,feature)
    nClass=size(sign,1);
	typePos=[];
	for i=1:nClass
	    typePosArr=sign(i,:)-feature;
        typePos(i)=typePosArr(1)*typePosArr(1)+typePosArr(2)*typePosArr(2)+typePosArr(3)*typePosArr(3);
	end
	type=find(typePos==min(typePos));
end
