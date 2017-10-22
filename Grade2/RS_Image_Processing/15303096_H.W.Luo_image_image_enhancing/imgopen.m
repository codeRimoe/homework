function [data]=imgopen(fileName,size,interLeave,dataType,machineFM)

% help informatiom
%
% This function is use to open a image file for reading data.
%
% author: Luo_Haowen
% usage: [data]=imgopen(fileName,size,interLeave,dataType,machineFM)
% example: data = imgopen('/Users/_nA/Desktop/data1/tm_bil',[804,523,7],'bil','uint8','l')
%
% data       -image data
% fileName   -the filename of the image file
% size       -the size of the image, [samples,lines,bands]
% interLeave -the measures of data storage
% dataType   -type of a data
% machineFM  -the byteorder of data, 'l' for Little-endian , 'b' for Big-endian

    fid=fopen(fileName,'r');
    data=[];

%bsqread
    if (interLeave == 'bsq')
        for k=1:size(3)
            for i=1:size(2)
                data(i,:,k)=fread(fid,size(1),dataType,machineFM);
            end
        end
    end

%bipread
    if (interLeave == 'bip')
        for i=1:size(2)
            for j=1:size(1)
                for k=1:size(3)
                    data(i,j,k)=fread(fid,1,dataType,machineFM);
                end
            end
        end
    end

%billed
    if (interLeave == 'bil')
        for i=1:size(2)
            for k=1:size(3)
                data(i,:,k)=fread(fid,size(1),dataType,machineFM);
            end
        end
    end

    fclose(fid);

end
