clear all
clc
clf
s=input("Enter nr of simulations: ");
n=3;
p=0.5;
A=rand(n,s);
B=A<0.5;
hist(sum(B))