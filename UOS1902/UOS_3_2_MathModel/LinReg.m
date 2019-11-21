function [a, Er] = LinReg(x, y)
%LinReg는 problem 6.1 LinearRegression을 수정한 함수입니다
% equation y = a1*x + a0 that best fits n data points
% Input variables:
% x    A vector with the coordinates x of the data points.
% y    A vector with the coordinates y of the data points.
% Output variables:
% a1    The coefficient a1
% a0    The coefficient a0
% a    two element vector with the values of the constants a1 and a0
% Er    the value of the overall error
%University Of Seoul, Gyeongmin Ha

nx = length(x);
ny = length(y);
if nx ~= ny 
    %Check if the vectors x and y have the same number of elements.
    disp('ERROR: The number of elements in x must be the same as in y.')
    %if yes, MATLAB displays an error emssage and the constants are not calcuated.
    a1 = 'Error';
    a0 = 'Error';
else
    %Calculate the summation terms in Eqs(6.13).
    Sx = sum(x);
    Sy = sum(y);
    Sxy = sum(x.*y);
    Sxx = sum(x.^2);
    %Calculate the coefficients a1 and a0 in Eqs. (6.14).
    a1 = (nx * Sxy - Sx * Sy) / (nx * Sxx - Sx^2);
    a0 = (Sxx * Sy - Sxy * Sx) / (nx * Sxx - Sx^2);
end
a = [a0, a1];
%Calculate overall error by Eq6.6
toterr = (y - (a1*x - a0)).^2; % 매트랩 요소별 거듭제곱 A.^B
Er = sum(toterr);
