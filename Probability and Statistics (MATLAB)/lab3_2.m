clear all
clc
clf

%the higher n is, the better the approx to bino
p=1;
while(p<0.05 || p>0.95)
    p = input("Enter p within [0.05, 0.95]:\n");
end

for n=1:100
    mu = n*p;
    sigma = sqrt(n*p*(1-p));
    k=0:n;
    y1 = binopdf(k,n,p);
    y2 = normpdf(k,mu,sigma);
    plot(k,y1,k,y2);
    title("n="+n);
    legend("binopdf","normpdf","Location","best")
    pause(0.5);
end
fprintf("%9f",p);