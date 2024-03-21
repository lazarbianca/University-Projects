clear all
clc
clf

n = input("Enter the index of success (n): \n");
p=1;
while(p<=0 || p>=1)
    p=input("Enter probability of success: \n");
end
s = input("Enter nr of simulations: \n");

X=zeros(1,s);
for i=1:s
    counterSuccess=0;
    counterFailures=0;
    while(true)
        u = rand;   % equivalent to rand(1,1) = rand(1) = rand
        nr = u<p;
        if(nr==0)
            counterFailures = counterFailures + 1;
        else
            counterSuccess = counterSuccess + 1;
        end
        if(counterSuccess == n)
            break;
        end
    end
    X(i)=counterFailures;
end
%ux, nx, rel freq, geopdf on 0:max(U_X)
U_X = unique(X);
n_x = hist(X,length(U_X));
f = n_x/s;

plot(U_X,f,'b*')
hold on;
k=0:max(U_X);
B=nbinpdf(k,n,p);
plot(k,B,'c--o')
title("random generator and nbinpdf")
legend("relative frequencies","nbinpdf","Location","best")
hold off

