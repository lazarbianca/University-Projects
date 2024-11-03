clear all
clc
clf

%the higher n is, the better the approx to bino
p=1;
while(p>0.05)
    p = input("Enter p <= 0.05:\n");
end
n=0;
while(n<30)
    n=input("Enter n >= 30: \n");
end

lambda = n*p;
k=0:n;
y1 = binopdf(k,n,p);
y2 = poisspdf(k,lambda);
plot(k,y1,k,y2);
title("n="+n);
legend("binopdf","poisspdf","Location","best")
fprintf("%9f",p);