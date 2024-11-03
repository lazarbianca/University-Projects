clear all
clc
clf

alpha = input("Enter value of alpha:\n");
beta = input("Enter value of beta:\n");
model = input("Select model: Normal, Student, Chi2, Fisher\n", "s");
switch(model)
    case "Normal"
        fprintf("Normal Distribution Model\n")
        mu = input("Give value of mu: ");
        sigma = input("Give value of sigma: ");
        a1=normcdf(0,mu,sigma);
        b1=normcdf(1,mu,sigma)-normcdf(-1,mu,sigma);

        c = norminv(alpha,mu,sigma);
        d = norminv(1-beta,mu,sigma);
    case "Student"
        fprintf("Student Distribution Model\n")
        n = input("Give value of n: ");
        a1=tcdf(0,n);
        b1=tcdf(1,n)-tcdf(-1,n);

        c = tinv(alpha,n);
        d = tinv(1-beta,n);
    case "Chi2"
        fprintf("Chi2 Distribution Model\n")
        n = input("Give value of n: ");
        a1=chi2cdf(0,n);
        b1=chi2cdf(1,n)-chi2cdf(-1,n);

        c = chi2inv(alpha,n);
        d = chi2inv(1-beta,n);
    case "Fisher"
        fprintf("Fisher Distribution Model\n")
        m = input("Give value of m: ");
        n = input("Give value of n: ");
        a1=fcdf(0,m,n);
        b1=fcdf(1,m,n)-fcdf(-1,m,n);

        c = finv(alpha,m,n);
        d = finv(1-beta,m,n);
    otherwise
        fprintf("Not a valid model.")
end
fprintf("a1) P(X<=0) = %9.5f\n", a1);
fprintf("a2) P(X>=0) = %9.5f\n", 1-a1);
fprintf("b1) P(-1<=x<=1) = %9.5f\n",b1);
fprintf("b2) P(x<=-1 or x>=1) = %9.5f\n",1-b1);
fprintf("c) P(X<x_alpha) = %9.5f\n", c);
fprintf("d) P(X>x_beta) = %9.5f\n", d);