function [trainSam,testSam]=stratiSam(sample,trainPer)
    a=1;
	s=1;
	trainSam={};
	testSam={};
    while s
	    t=(sample(:,1)==a);
		sam=sample(t,:);
	    s=sum(t);
		ranList=randperm(s);
        breakPoi=round(s*trainPer);
		t=logical(ones(1,s));
		test=t;
		test(ranList(1:breakPoi))=0;
		train=logical(t-test);
		if s~=0
		    trainSam{a}=sam(train,:);
			testSam{a}=sam(test,:);
		end
		a=a+1;
	end
end
