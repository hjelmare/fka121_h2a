%% PlotResults_HP2_Task2
clear all
clc

N=1000;

granneA = dlmread('granneA.data', '\t');
granneB = dlmread('granneB.data', '\t');

granneA = granneA(:,1:end-1);
granneB = granneB(:,1:end-1);
granneA(:,1)=granneA(:,1)+1;
granneB(:,1)=granneB(:,1)+1;


%Dela upp index på grannen man vill testa:
granne=343;
gx = fix(granne/100);
gy = fix((granne-gx*100)/10);
gz = granne-gx*100-gy*10;

for i=1:8
x(i)=fix(granneA(granne, i)/100);
y(i)=fix((granneA(granne, i)-x(i)*100)/10);
z(i)=granneA(granne,i)-(x(i)*100+y(i)*10);
end


% for i=1:8
% x(i)=fix(granneB(granne, i)/100);
% y(i)=fix((granneB(granne, i)-x(i)*100)/10);
% z(i)=granneB(granne,i)-(x(i)*100+y(i)*10);
% end


a=0;
b=0.5;

subplot(2,2,1);
hold on
for j=1:10
    for k=1:10
            plot(j,k,'b');
            plot(j+0.5,k+0.5,'r');
            plot(x+0.5,y+0.5,'or') %A
            %plot(x,y,'or') %B            
    end
end
plot(gx, gy, 'ob') %A
%plot(gx+0.5, gy+0.5, 'ob') %B
xlabel('X');
ylabel('Y')

subplot(2,2,2)
hold on
for j=1:10
    for k=1:10
            plot(j,k,'b');
            plot(k+0.5,k+0.5,'r');
            plot(x+0.5,z+0.5,'or') %A
            %plot(x,z,'or') %B            
    end
end
plot(gx,gz, 'ob') %A
%plot(gx+0.5, gz+0.5, 'ob') %B
xlabel('X');
ylabel('Z')

subplot(2,2,3)
hold on
for j=1:10
    for k=1:10
            plot(j,k,'b');
            plot(j+0.5,k+0.5,'r');
            plot(y+0.5,z+0.5,'or') %A
            %plot(y,z,'or') %B            
    end
end
plot(gy,gz, 'ob') %A
%plot(gy+0.5, gz+0.5, 'ob') %B
xlabel('Y');
ylabel('Z')

%%
hold on
for i=1:10;
    for j=1:10
        for k=1:10
                %plot3(i,j,k,'b');
                %plot3(i+0.5,j+0.5,k+0.5,'r');
                plot3(x+0.5,y+0.5,z+0.5,'or') %A
                %plot3(x,y,z,'or') %B
        end
    end

end
%%
hold on
plot3(gx, gy,gz, 'ob') %A
%plot3(gx+0.5, gy+0.5,gz+0.5, 'ob') %B
grid on







