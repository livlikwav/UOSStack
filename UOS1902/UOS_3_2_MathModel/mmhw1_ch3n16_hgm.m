help BisectionRoot

Fun = @ (x) x-2*exp(-x);
a = 0;
b = 1;
%i defined toleration = 0.000001, imx = 30 in BisectionRoot.m
BisectionRoot(Fun, a, b)