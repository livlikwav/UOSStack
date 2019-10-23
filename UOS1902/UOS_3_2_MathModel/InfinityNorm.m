function N = InfinityNorm(A)
%행렬의 무한놈은 행 절댓값의 최대합이다.
%University of Seoul, Gyeongmin Ha

[n, m] = size(A);
vec = zeros(1, n); %for find max 
for i = 1:n
    temp_sum = 0;
    for j = 1:m
        temp_sum = temp_sum + abs(A(i, j)); % column's abs summation
    end
    vec(i) = temp_sum;
end
N = max(vec);

end