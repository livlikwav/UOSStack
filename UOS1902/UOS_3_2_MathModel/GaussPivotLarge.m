function x = GaussPivotLarge(a, b)
%Pivoting Section을 절댓값이 가장 큰 행과 피보팅하게 수정하였습니다.
%University of Seoul, Gyeongmin Ha

ab = [a,b];
[R, C] = size(ab);
for j =1:R-1
    %Pivoting section starts
    if ab(j,j) == 0 %check if the pivot element is zero
        maxval = 0;
        maxi = j;
        for k = j + 1:R % check maximum absolute value in pivot col
            if abs(ab(k,j)) > maxval
                maxval = abs(ab(k,j));
                maxi = k;
            end
        end
        abTemp = ab(j, :);
        ab(j,:) = ab(maxi,:);
        ab(maxi,:) = abTemp;
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