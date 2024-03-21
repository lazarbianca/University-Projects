clear all
clc
%clf

x = [7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];
n=length(x);
confidence_level = input("Confidence level = ");
% large sample, compute mean, sigma is given => first function
mean_x = mean(x);
alpha = 1-confidence_level;
sigma = 5;

tl=mean_x-sigma/sqrt(n)*norminv(1-alpha/2);
tu = mean_x - sigma/sqrt(n)*norminv(alpha/2);


fprintf("a) The %2.0f%% confidence interval for the mean is (%5.3f,%5.3f)\n",confidence_level*100, tl,tu)
%2 characters .0 decimals, f=float, %= escape symbol (escapes %)

s = std(x);
%extra argument 1 only if we are computing for the entire population.
tl_2= mean_x-s/sqrt(n)*tinv(1-alpha/2,n-1);
tu_2=mean_x - s/sqrt(n)*tinv(alpha/2,n-1);
fprintf("a) The %2.0f%% confidence interval for the mean is (%5.3f,%5.3f)\n",confidence_level*100, tl_2,tu_2)
%used in medicine, tv ratings and so on; obligated by law to say the
%confidence level

% for the variance! for standard deviation, use sqrt of this
s2=var(x);
tl_3 = (n-1)*s2/chi2inv(1-alpha/2,n-1);
tu_3 = (n-1)*s2/chi2inv(alpha/2, n-1);

fprintf("a) The %2.0f%% confidence interval for the mean is (%5.3f,%5.3f)\n",confidence_level*100, tl_3,tu_3)

x_premium = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
x_regular = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];
n1 = length(x_premium);
n2 = length(x_regular);

mean_premium = mean(x_premium);
mean_regular = mean(x_regular);
% sigma1=sigma2 unknown
s1_4 = var(x_premium);
s2_4 = var(x_regular);
sp = ((n1-1)*s1_4+(n2-1)*s2_4)/n1+n2-2;
tl_4 = mean_premium - mean_regular - tinv(1-alpha/2,n1+n2-2)*sp*sqrt(1/n1+1/n2);
t2_4 = mean_premium - mean_regular %CONTINUE

%b) third formula sigma1 != sigma2
