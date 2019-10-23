function c = CondNumb_One(A)
%���Ǽ�(1-norm)�� ����� 1�븧�� �� ������� 1�븧�� ���Դϴ�.
%4.24������ Inverse ����������Լ��� ��Ʈ������ inv()�� ��ü�Ͽ����ϴ�
%University of Seoul, Gyeongmin Ha
    InvA = inv(A);
    c = OneNorm(A) * OneNorm(InvA);
end

function N = OneNorm(A)
%����� 1���� �� ������ �ִ����̴�.

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