% This function is used to count the weighted avg centre;
% W is the weight, [i,j] is the weight in location j in ith year;
% P is the coordinate, the ith row [x,y] is the coordinate of location i.
% return a matrix C,the ith row [x,y] is the coordinate of the central of ith year.
% author: Yue H.W. Luo
% All right reserved.

function C = cen(W,P)
  n = size(W);
  n = n(1);
  C=[];
  for i = 1:n
      [x,y] = wac(W(i,:),P)
      C = [C;[x,y]];
  end
end
  

function [x,y] = wac(W,P)
   x = W*P(:,1)/sum(W);
   y = W*P(:,2)/sum(W);
end