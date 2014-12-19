%% Plot saved results.
% importing
clear all
clc

s_block_E=importdata('statInefficiency/statInefficiency_block_E.mat');
s_block_P=importdata('statInefficiency/statInefficiency_block_P.mat');
s_block_r=importdata('statInefficiency/statInefficiency_block_r.mat');
s_corr_E=importdata('statInefficiency/statInefficiency_corr_E.mat');
s_corr_P=importdata('statInefficiency/statInefficiency_corr_P.mat');
s_corr_r=importdata('statInefficiency/statInefficiency_corr_r.mat');

names = {'200', '300', '400', '500', '600', '660', '700', '800', '900', '1000', '1100', '1200', '1300'};
nbrOfT = 13;
%importera data till block plots.
for i= 1:nbrOfT
    eval(['block_E{' num2str(i) '} = importdata(''T' names{i} 'BlockAverage_E.mat'');'])
    eval(['block_P{' num2str(i) '} = importdata(''T' names{i} 'BlockAverage_P.mat'');'])
    eval(['block_r{' num2str(i) '} = importdata(''T' names{i} 'BlockAverage_r.mat'');'])
end

%Konstanter vi använder i resterande celler.
Bmax_small = 100000;
Bmax_large = 300000;
Bmax=[Bmax_large, Bmax_large, Bmax_large, Bmax_large, Bmax_large, Bmax_large, Bmax_large, Bmax_small, Bmax_small, Bmax_small, Bmax_small, Bmax_small, Bmax_small];
Bmin = 10000;
Bstep = 500;

textStorlek=14;
legendStorlek =11;

%% Plott block average - Energy
close all

cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(7,:)=[1 0.8  0.8];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];

markerSize = 3;
legendMarkerSize = 10;
hold on
for i=1:nbrOfT
    x=Bmin:Bstep:Bmax(i);
    plot(x,block_E{i}, 'color', cc(i,:), 'LineStyle', 'd', 'MarkerSize', markerSize)
end
for i =1:nbrOfT
   plot([0 Bmax(i)], [s_block_E(i) s_block_E(i)], 'color', cc(i,:), 'LineStyle', '--') 
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek);
title('Block average - Energy', 'FontSize', textStorlek);
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
a=get(text, 'children');
set(a(1:3:end), 'MarkerSize', legendMarkerSize);

%% Plott block average - long range order parameter (P)
close all

cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(7,:)=[1 0.8  0.8];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];

markerSize = 3;
legendMarkerSize = 10;
hold on
for i=1:nbrOfT
    x=Bmin:Bstep:Bmax(i);
    plot(x,block_P{i}, 'color', cc(i,:), 'LineStyle', 'd', 'MarkerSize', markerSize)
end
for i =1:nbrOfT
   plot([0 Bmax(i)], [s_block_P(i) s_block_P(i)], 'color', cc(i,:), 'LineStyle', '--') 
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek);
title('Block average - Long range order parameter', 'FontSize', textStorlek);
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
a=get(text, 'children');
set(a(1:3:end), 'MarkerSize', legendMarkerSize);

%% Plott block average - short range order parameter (r)
close all

cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(7,:)=[1 0.8  0.8];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];

markerSize = 3;
legendMarkerSize = 10;
hold on
for i=1:nbrOfT
    x=Bmin:Bstep:Bmax(i);
    plot(x,block_r{i}, 'color', cc(i,:), 'LineStyle', 'd', 'MarkerSize', markerSize)
end
for i =1:nbrOfT
   plot([0 Bmax(i)], [s_block_r(i) s_block_r(i)], 'color', cc(i,:), 'LineStyle', '--') 
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek);
title('Block average - Short range order parameter', 'FontSize', textStorlek);
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
a=get(text, 'children');
set(a(1:3:end), 'MarkerSize', legendMarkerSize);


