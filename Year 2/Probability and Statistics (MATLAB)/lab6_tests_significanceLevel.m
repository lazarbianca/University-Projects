clc
clear all

x = [7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];
n=length(x);
alpha = input("Enter the significance level: ");
sigma = 5;

% compute the rejection region: -inf to quantile of alpha
q = norminv(alpha);
%rr = (-inf, q);
%TT = (x-mean(x))/ (sigma/sqrt(n))
%m0=input(" test value m0= "); %8.5
[H,P,CI,ZVAL]=ztest(x,8.5,sigma,alpha,-1)
%zval is -1.6667 outside the rejection region
if(H == 0)
    fprintf("We will not reject H0; that is to say, i.e. standard is met")
    fprintf("the rejection region is:")
else 
    fprintf("We will reject H0; that is to say, i.e. standard is NOT met")
end
% for 0.05, we reject
% for 0.01, we do NOT reject
% b) ???
quantile = tinv(1-alpha,n-1);
TT=(x-mean(x))/(sigma/sqrt(n));
RR = [1.6896, +inf];
[H,P,CI,STATS]=ztest(x,5.5,sigma,alpha,1)

%2a)
finv(alpha/2, n-1)
