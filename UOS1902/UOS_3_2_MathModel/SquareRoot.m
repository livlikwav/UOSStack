function Xs = SquareRoot(p)
%SquareRoot는 p에 대한 루트값을 구하는 함수입니다
% University of Seoul, GyeongminHa

if p < 0 % if p is negative, program stop and display an error message
    fprintf('p = %i, is negative number', p)
    return;
end

Fun = @(x) x^2-p; % problem function
FunDer = @(x) 2*x; % calculates the derivative of Fun for a given x
Xest = p; % Initial estimate of the solution
Err = 1*10^-6; % Maximum error 
iMax = 20;

for i = 1:iMax
    Xi = Xest - Fun(Xest)/FunDer(Xest); %Newton's method determine next NS
    if abs((Xi - Xest)/Xest) < Err %compare by estimated relative error
        Xs = Xi; %Xs is the answer
        break
    end
    Xest = Xi;
end
if i == iMax
    fprintf('Solution was not obtained in %i iteratios. \n', iMax)
    Xs = ('No answer');
end
end