function x = GaussPivotLarge(a, b)
%University of Seoul, Gyeongmin Ha

ab = [a,b];
[R, C] = size(ab);
for j =1:R-1
    %Pivoting section starts
    if ab(j,j) == 0 %check if the pivot element is zero
        for k = j + i:R
            if ab(k,j) ~= 0
                abTemp = ab(j, :);
                ab(j,:) = ab(k,:);
                ab(k,:) = abTemp;
                break
            end
        end
    end
    %Pivoting section ends
    for i = j+1:R
        ab(i,j:C) = ab(i,j:C) - ab(i,j)/ab(j,j)*ab(j,j:C);
    end
end
x = zeros(R,1);
x(R) = ab(R,C)/ab(R,R);
for i = R - 1:-1:1
    x(i) = (ab(i,C) - ab(i,i+1:R)*x(i+1:R))/ab(i,i);
end
        
end