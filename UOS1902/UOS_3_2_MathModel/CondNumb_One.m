function c = CondNumb_One(A)
%조건수(1-norm)는 행렬의 1노름과 그 역행렬의 1노름의 곱입니다.
%4.24문제의 Inverse 사용자정의함수는 매트랩내의 inv()로 대체하였습니다
%University of Seoul, Gyeongmin Ha
    InvA = inv(A);
    c = OneNorm(A) * OneNorm(InvA);
end

function N = OneNorm(A)
%행렬의 1놈은 열 절댓값의 최대합이다.

[n, m] = size(A);
vec = zeros(1, m); %for find max 
for i = 1:m
    temp_sum = 0;
    for j = 1:n
        temp_sum = temp_sum + abs(A(j, i)); % column's abs summation
    end
    vec(i) = temp_sum;
end
N = max(vec);

end