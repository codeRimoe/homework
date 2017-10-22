function []=imgsave(fileName,data,size,interLeave,dataType,machineFM)

% help informatiom
%
% This function is use to save data into a image file.This function is use to open a image file for reading data.
%
% author: Luo_Haowen
% usage: []=imgsave(fileName,data,size,interLeave,dataType,machineFM)
% example: imgsave('/Users/_nA/Desktop/data1/tm_bil',data,[804,523,7],'bsq','uint8','l')
%
% data       -image data
% fileName   -the filename of the image file save as
% size       -the size of the image, [samples,lines,bands]
% interLeave -the measures of data storage
% dataType   -type of a data
% machineFM  -the byteorder of data, 'l' for Little-endian , 'b' for Big-endian

    fid = fopen(fileName,'w') ;

    %bsqread
    if (interLeave == 'bsq')
	    for k=1:size(3)
		    for i=1:size(2)
			    fwrite(fid, data(i,:,k), dataType, machineFM);
		    end
	    end
    end

%bipread
    if (interLeave == 'bip')
	    for i=1:size(2)
		    for j=1:size(1)
			    for k=1:size(3)
                    fwrite(fid, data(i,j,k), dataType, machineFM);
			    end
		    end
	    end
    end

%bilread
    if (interLeave == 'bil')
    	for i=1:size(2)
	    	for k=1:size(3)
		    	fwrite(fid, data(i,:,k), dataType, machineFM);
		    end
	    end
    end

end
