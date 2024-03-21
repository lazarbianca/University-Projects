clear all %clears vars
clc
clf %clears figure
n=input("Enter the nr of trials: ");
p=input("Enter the probability of success: ");
k=0:n;
px=pdf('bino',k,n,p);
plot(k,px,'b*')
title("pdf and cdf")
hold on

xx=0:0.1:n;
cx=cdf('bino',xx,n,p);
plot(xx,cx)
legend("pdf","cdf","Location","best")
hold off