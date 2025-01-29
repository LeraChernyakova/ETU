clc
clear 
close all 
D = 2.8;
L = 50;
alfa = 10*pi/180;
dy = 0.001;
y1 = 0:dy:D/2;
fun_n = @(y,z) 1.3+0.12*cos(y^2*z);
% 1/4
for i = 1:length(y1)
    n = fun_n(dy,i);
    n1 = fun_n(dy,i+1);
    alfa = acos(n1/n*cos(alfa));
    s(i) = (dy*i)/sin(alfa);
    x1(i) = (dy*i)/tan(alfa);
end
%2/4
x2 = 2*x1(end)-x1(end:-1:1);
y2 = y1(end:-1:1);
x12 = [x1 x2];
y12 = [y1 y2];
%3/4
x3 = 2*x1(end)+x1;
y3 = y1*(-1);
x23 = [x12 x3];
y23 = [y12 y3];
%4/4
x4 = x1(end) - x1(end:-1:1)+3*x1(end);
y4 = y1(end:-1:1)*(-1);
x34 = [x23 x4];
y34 = [y23 y4];
x = x34;
y = y34;
xn =x;
yn= y;
 while xn(end)<=L
     xn = 2*x(end)-x(end:-1:1);
     xn = [x xn];
     yn = [y yn];
     x = xn;
     y = yn;
 end
index = find(xn>L);
xn = xn(1:index);
yn = yn(1:index);
k = length(xn)/length(s);
Len = s(end)*k;
Len
plot(xn,yn,'k-')
axis([0 L -D/2 D/2])
grid on
