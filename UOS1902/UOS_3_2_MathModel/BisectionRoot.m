function Xs = BisectionRoot(Fun, a, b)
%Bisection Root는 Fun 함수에 대해 초기 [a,b] 구간으로 Bisection method를 수행합니다
%Fun is function that calculates f(x) for a given x
%a, b is initial two points
% University of Seoul, GyeongminHa

imax = 30; tol = 0.000001; %define max number of iter and tol
Fa = Fun(a); Fb = Fun(b);
if Fa*Fb > 0 % stop program if the function has the same sign at points a and b
    disp('Error:The function has the same sign at points a and b.')
else
    disp('iteration a b (xNS) Solution f(xNS) Tolerance')
    for i = 1:imax
        xNS = (a + b)/2; %ith numerical solution
        toli = (b - a)/2; %ith tolerance
        FxNS = Fun(xNS); %ith F(numeric sol)
        fprintf('%3i %11.6f %11.6f %11.6f %11.6f %11.6f\n', i, a, b, xNS, FxNS, toli)
        if FxNS == 0 % if FxNS = 0, then xNS is true solution. so stop
            fprintf('An exact solution x = %11.6f was found', xNS)
            Xs = xNS;
            break
        end
        if toli < tol % find the tolerance under the desired tol
            fprintf('numeric solution x = %11.6f was found, satisfy desired tol', xNS)
            Xs = xNS;
            break
        end
        if i == imax % iteration max
            fprintf('Solution was not obtained in %i iterations', imax)
            Xs = ('No Answer');
            break
        end
        if Fun(a) * FxNS < 0 % sign < 0, [a, xNS]
            b = xNS;
        else
            a = xNS; % sign > 0, [xNS, b]
        end
    end
end


        