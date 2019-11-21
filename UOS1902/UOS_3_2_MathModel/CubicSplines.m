function Yint = CubicSplines(x, y, xint)
% CubicSplines for interpolation with natural cubic splines
% Example 6-8을 그대로 일반화하여 다른 x, y, xint에도
% 적용가능 하도록 수정하였습니다.
% Input variables:
% x, y vectors with the coordinates of the data points
% xint    x coordinate of the interpolated point
% Output variables:
% yint    y value of the interpolated point
% University of Seoul, Gyeongmin Ha

n = length(x);
for i=1:n-1
    hvec(i) = x(i+1) - x(i);
end

% a0, alast = 0
% [mata][p] = [matb]
% make mata dynamically
for i=1:n-2
    for j=1:n % row num is n-2
        mata(i,j) = 0; %initialize mata by inserting 0
    end
end
for i=1:n-2
    mata(i,i) = hvec(i);
    mata(i,i+1) = 2*(hvec(i)+hvec(i+1));
    mata(i,i+2) = hvec(i+1);
end
for i=1:n-2
    mata(i,1) = 0; % a0 = 0
    mata(i,n) = 0; % alast = 0
end
%make matb dynamically
for i=1:n-2
    matb(i,1) = 6*((y(i+2)-y(i+1))/hvec(i+1) - (y(i+1)-y(i))/hvec(i));
end
mata %DEBUG
matb %DEBUG
coef = (mata\matb)' %DEBUG
% get interpolated value
for i=1:n-1
    if( x(i) <= xint && xint <= x(i+1))
        xitv = i; % xitv = xinterval 몇번째 구간인지 나타냄
    end
end
%식을 그대로 일반화하여, 공식이 보기 힘든점 양해부탁드립니다
Yint = (x(xitv+1)-xint)^3*coef(xitv)/(6*hvec(xitv)) + (xint-x(xitv))^3*coef(xitv+1)/(6*hvec(xitv)) + ((y(xitv)/hvec(xitv))-(coef(xitv)*hvec(xitv)/6))*(x(xitv+1)-xint) + ((y(xitv+1)/hvec(xitv))-(coef(xitv+1)*hvec(xitv)/6))*(xint-x(xitv));
