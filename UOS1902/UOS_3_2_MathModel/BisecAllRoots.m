function R=BisecAllRoots(fun, a, b, TolMAX)
%BisecAllRoots is function that solves for all the real roots in a
%specified domain of a nonlinear function f(x) = 0 using the bisection
%method
% University of Seoul, GyeongminHa

R = zeros(1, 20); %initialize answer vector by zeros

N_subintervals = 10; %initialize number of sub intervals;
h = (b-a)/N_subintervals; %length of subintervals

idx = 1; %initialize R vector's index to fill new element

for n = 1:5
%initialize subinterval, save idx
sub_a = a; %subinterval's a
sub_b = a+h; %subinterval's b
saved_idx = idx; %for count the new roots

    for i = 1:N_subintervals
        Fsub_a = fun(sub_a); Fsub_b = fun(sub_b);
        root_flag = 0; %for count the root in subintervals
        
       if Fsub_a*Fsub_b > 0
            fprintf('same sign, sub_a = %11.6f, sub_b = %11.6f, fsuba=%11.6f, fsubb = %11.6f in loop %i.\n', sub_a, sub_b, Fsub_a, Fsub_b, N_subintervals)
       else
           %check that subinterval has a root already 
           if idx ~= 1
               for j = 1:idx-1
                   if R(j) >= sub_a && R(j) <= sub_b
                       root_flag = root_flag + 1; %check the num of root in this interval
                   end
               end
           end
           %do BisectionRoot
           if root_flag == 0
               R(idx) = BisectionRoot(fun, sub_a, sub_b, TolMAX);
               idx = idx + 1;
               fprintf('add root value in loop %i \n', N_subintervals)
           else
               fprintf('*** this interval already contain the root \n')
           end
       end
       
       %move subinterval
       sub_a = sub_b;
       sub_b = sub_b + h;
    end
fprintf('finish loop over %i subintervals \n ==============================================\n', N_subintervals)

%no new roots have been identified, stop the program
if idx == saved_idx && n > 1
    fprintf('no more roots, program will be stopped. \n')
    break
else
    N_subintervals = N_subintervals * 10; %number of subintervals is multiplied by 10
    h = (b-a)/N_subintervals; %length of subintervals
    fprintf('New #subinterval = %i, length = %11.6f \n', N_subintervals, h)
end

end %for end
end %function end

function Xs = BisectionRoot(Fun, a, b, tol)
%Bisection Root는 Fun 함수에 대해 초기 [a,b] 구간으로 Bisection method를 수행합니다
%a, b is initial two points

imax = 30; %define max number of iter
disp('iteration a b (xNS) Solution f(xNS) Tolerance')
for i = 1:imax
    xNS = (a + b)/2; %ith numerical solution
    toli = (b - a)/2; %ith tolerance
    FxNS = Fun(xNS); %ith F(numeric sol)
    fprintf('%3i %11.6f %11.6f %11.6f %11.6f %11.6f\n', i, a, b, xNS, FxNS, toli)
    if FxNS == 0 % if FxNS = 0, then xNS is true solution. so stop
        fprintf('An exact solution x = %11.6f was found \n', xNS)
        Xs = xNS;
        break
    end
    if toli < tol % find the tolerance under the desired tol
        fprintf('numeric solution x = %11.6f was found, satisfy desired tol \n', xNS)
        Xs = xNS;
        break
    end
    if i == imax % iteration max
        fprintf('Solution was not obtained in %i iterations \n', imax)
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
