clear all
clc
clf

p=1;
while(p<=0 || p>=1)
    p=input("Enter probability of success: \n");
end
s = input("Enter nr of simulations: \n");

X=zeros(1,s);
for i=1:s
    counter=0;
    while(true)
        u = rand;   % equivalent to rand(1,1) = rand(1) = rand
        nr = u<p;
        if(nr==0)
            
            counter = counter+1;
        else
            break;
        end
    end
    X(i)=counter;
end
%ux, nx, rel freq, geopdf on 0:max(U_X)
U_X = unique(X);
n_x = hist(X,length(U_X));
f = n_x/s;

plot(U_X,f,'b*')
hold on;
k=0:max(U_X);
B=geopdf(k,p);
plot(k,B,'c--o')
title("random generator and geopdf")
legend("relative frequencies","geopdf","Location","best")
hold off

% OR:
% while(rand >= p)
%   counter = counter+1
