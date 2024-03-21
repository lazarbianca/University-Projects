%F1 for documentation
clear all
clc
%clf -- no figure

n = input("Enter the nr of trials:\n");
p=1;
while(p<=0 || p>=1)
    p=input("Enter probability of success: \n");
end
s = input("Enter nr of simulations: \n");
U=rand(n,s);
A=U<p;
X=sum(A)

% find all unique values in vector X (0 and 1)(0 and 0), (1 and 1)
U_X=unique(X);
% we can just add up all elems to get the nr of 1s, 
% and compute nr simulations s - nr of 1s = nr of zeroes

% for the sake of future, more complex problems:
n_x = hist(X,length(U_X)); % this computes the nr of occurences of each
% nr in U_X
[U_X;n_x]

% relative frequencies: nr of appearances / nr of simulations
f = n_x/s

%
plot(U_X,f,'b*')
hold on;
k=0:n;
B=binopdf(k,n,p);
plot(k,B,'c--o')
title("random generator and binopdf")
legend("relative frequencies","binopdf","Location","best")
hold off

