function [ out_img , key ] = enc( in_img )
    img_size = size(in_img);
    n_band = 1;
    if size(img_size) ~= 2
        n_band = img_size(3);
    end
    n_pix = img_size(1) * img_size(2);
    key = zeros(n_pix,n_band,'uint64');
    out_img = zeros(n_pix,n_band,'uint8');
    in_img = reshape(in_img,[n_pix,n_band]);
    for i_ = 1:n_band
        key(:,i_) = randperm(n_pix);
    end
    for i_ = 1:n_band
        for j_ = 1:n_pix
            out_img(j_,i_) = in_img(key(j_,i_),i_);
        end
    end 
    out_img = reshape(out_img,img_size);
    key = reshape(key,img_size);
end

