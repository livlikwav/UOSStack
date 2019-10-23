help BisecAllRoots

TolMax = 0.0001;
fun = @(x) x^4-5.5*x^3-7.2*x^2+43*x+36;

BisecAllRoots(fun, 0, 100, TolMax)
