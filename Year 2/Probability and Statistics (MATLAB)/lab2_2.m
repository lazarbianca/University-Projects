clear all
clc
clf

n=3;
p=0.5;
k=0:n;
px=pdf('bino',k,n,p);
X=[k;px]

C1=binopdf(0,n,p)
C2=1-binopdf(1,n,p)

D1=cdf('bino',2,n,p)
D2=D1-pdf('bino',2,n,p)

E1=cdf('bino',1,n,p)-pdf('Binomial',1,n,p)   %or 1-X(0)
E2=1-cdf('bino',1,n,p)