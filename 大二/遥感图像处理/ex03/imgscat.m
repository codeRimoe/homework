function []=imgscat(data,dims,band)
    x=reshape(data(:,:,band(1)),1,[]);
    y=reshape(data(:,:,band(2)),1,[]);
    xlabel(['BAND_',num2str(band(1))]);
    ylabel(['BAND_',num2str(band(2))]);
    hold on;
    if (dims == 2)
        scatter(x,y,'+','black');
    end
    if (dims == 3)
        z=reshape(data(:,:,band(3)),1,[]);
        zlabel(['BAND_',num2str(band(3))]);
        scatter3(x,y,z,'+','black');
        view(40,35)
    end
end