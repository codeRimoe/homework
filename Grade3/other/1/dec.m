function [ out_img ] = dec( in_img , key )
    img_size = size(in_img);
    n_band = 1;
    if size(img_size) ~= 2
        n_band = img_size(3);
    end
    n_pix = img_size(1) * img_size(2);
    in_img = reshape(in_img,[n_pix,n_band]);
    key = reshape(key,[n_pix,n_band]);
    out_img = zeros(n_pix,n_band,'uint8');
    for i_ = 1:n_band
        for j_ = 1:n_pix
            out_img(key(j_,i_),i_) = in_img(j_,i_);
        end
    end
    out_img = reshape(out_img,img_size);
end

