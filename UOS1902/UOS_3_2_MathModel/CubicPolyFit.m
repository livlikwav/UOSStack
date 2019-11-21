function [a, Er] = CubicPolyFit(x, y)
% CubicPolyFit 함수는 3차 다항식을 Regression하는 함수입니다.
% Input Variables:
% x, y    vectors with the coordinates of the data points
% Output Variables:
% a    four-element vector with the values of the coeffiients a0,a1,a2,a3
% Er    value of the overall error by Eq 6.21
% University of Seoul, GyeongminHa

n = length(x); % n is the number of data points
m = 3; % m is the order of the polynomials
for i = 1:2*m
    xsum(i) = sum(x.^i); % Define a vector with the summation terms of the powers of xi
end
% Assign the first row of the matrix [a] and the first element of the
% column vector [b]
mata(1,1) = n;
matb(1,1) = sum(y);
for j = 2:m+1
    mata(1,j) = xsum(j - 1);
end
% Create rows 2 through 4 of the matrix [a] and elements 2 through 4 of the
% column vector [b]
for i = 2:m+1
    for j = 1:m+1
        mata(i, j) = xsum(j + i - 2);
    end
    matb(i, 1) = sum(x.^(i - 1).*y);
end
% Solve the system [a][p] = [b] for [p]. Transpose the solution such that
% [p] is a row vector.
a = (mata \ matb)'; % coefficient vector p를 이름 a로 바꿔서 출력
for i = 1:n % n is length(x)
    xvec(i) = sum([1 x(i) x(i)^2 x(i)^3].*a); % a가 a0 a1 a2 a3 순서이므로
end
Er = sum((y - xvec).^2);