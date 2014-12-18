clear all
clc

temp=importdata('blockAverage_T200.mat');
bA_s(:,1)=temp;
temp=importdata('blockAverage_T300.mat');
bA_s(:,2)=temp;
temp=importdata('blockAverage_s_T400.mat');
bA_s(:,3)=temp;
temp=importdata('blockAverage_s_T500.mat');
bA_s(:,4)=temp;
temp=importdata('blockAverage_s_T600.mat');
bA_s(:,5)=temp;
temp=importdata('blockAverage_s_T660.mat');
bA_s(:,6)=temp;
temp=importdata('blockAverage_s_T700.mat');
bA_s(:,7)=temp;
temp=importdata('blockAverage_s_T800.mat');
bA_s(:,8)=temp;
temp=importdata('blockAverage_s_T900.mat');
bA_s(:,9)=temp;
temp=importdata('blockAverage_s_T1000.mat');
bA_s(:,10)=temp;
temp=importdata('blockAverage_s_T1100.mat');
bA_s(:,11)=temp;
temp=importdata('blockAverage_s_T1200.mat');
bA_s(:,12)=temp;
temp=importdata('blockAverage_s_T1300.mat');
bA_s(:,13)=temp;

%Importera de sparade s från block och corr för alla storheter:
s_block_E=importdata('statInefficiency/statInefficiency_block_E.mat');
s_block_P=importdata('statInefficiency/statInefficiency_block_P.mat');
s_block_r=importdata('statInefficiency/statInefficiency_block_r.mat');
s_corr_E=importdata('statInefficiency/statInefficiency_corr_E.mat');
s_corr_P=importdata('statInefficiency/statInefficiency_corr_P.mat');
s_corr_r=importdata('statInefficiency/statInefficiency_corr_r.mat');

% temp=importdata('correlation_s_T200.mat');
% correlation_s(:,1) =temp;
% temp=importdata('correlation_s_T300.mat');
% correlation_s(:,2) =temp;
% temp=importdata('correlation_s_T400.mat');
% correlation_s(:,3) =temp;
% temp=importdata('correlation_s_T500.mat');
% correlation_s(:,4) =temp;
% temp=importdata('correlation_s_T600.mat');
% correlation_s(:,5) =temp;
% temp=importdata('correlation_s_T660.mat');
% correlation_s(:,6) =temp;
% temp=importdata('correlation_s_T700.mat');
% correlation_s(:,7) =temp;
% temp=importdata('correlation_s_T800.mat');
% correlation_s(:,8) =temp;
% temp=importdata('correlation_s_T900.mat');
% correlation_s(:,9) =temp;
% temp=importdata('correlation_s_T1000.mat');
% correlation_s(:,10) =temp;
% temp=importdata('correlation_s_T1100.mat');
% correlation_s(:,11) =temp;
% temp=importdata('correlation_s_T1200.mat');
% correlation_s(:,12) =temp;
% temp=importdata('correlation_s_T1300.mat');
% correlation_s(:,13) =temp;
% 
% temp = importdata('heatCapacity_T200.mat');
% heatCap(:,1) = temp;
% temp = importdata('heatCapacity_T300.mat');
% heatCap(:,2) = temp;
% temp = importdata('heatCapacity_T400.mat');
% heatCap(:,3) = temp;
% temp = importdata('heatCapacity_T500.mat');
% heatCap(:,4) = temp;
% temp = importdata('heatCapacity_T600.mat');
% heatCap(:,5) = temp;
% temp = importdata('heatCapacity_T660.mat');
% heatCap(:,6) = temp;
% temp = importdata('heatCapacity_T700.mat');
% heatCap(:,7) = temp;
% temp = importdata('heatCapacity_T800.mat');
% heatCap(:,8) = temp;
% temp = importdata('heatCapacity_T900.mat');
% heatCap(:,9) = temp;
% temp = importdata('heatCapacity_T1000.mat');
% heatCap(:,10) = temp;
% temp = importdata('heatCapacity_T1100.mat');
% heatCap(:,11) = temp;
% temp = importdata('heatCapacity_T1200.mat');
% heatCap(:,12) = temp;
% temp = importdata('heatCapacity_T1300.mat');
% heatCap(:,13) = temp;
T=[200 300 400 500 600 660 700 800 900 1000 1100 1200 1300];


%% Plot correlation functions
textStorlek = 14;
legendStorlek = 11;

nbrOfT = size(correlation_s,2);
cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];
hold on
for i=1:nbrOfT
    plot(correlation_s(:,i), 'color', cc(i,:));
end
plot([1, length(correlation_s)], [exp(-2), exp(-2)], '--r')
xlabel('iteration number', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
xlim([0, 6e4])

%% plot statistical inefficiency
for i=1:nbrOfT
    limit(i) = find(correlation_s(:,i) < exp(-2), 1);
    
    statInefficiency(i) = 0;
    for j=1:limit(i)
        statInefficiency(i) = statInefficiency(i) + correlation_s(j,i);
    end
    statInefficiency(i) = 2*statInefficiency(i);
end
plot(T, statInefficiency);
ylabel('statistical inefficiency, s','FontSize', textStorlek)
xlabel('temperature [K]','FontSize', textStorlek)
title('s calculated from correlation function', 'FontSize', textStorlek);
text=legend('statistical inefficiency, s');
set(text, 'FontSize', legendStorlek);

%%  plot s, block average

x=(100:500:100000);
cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];


for i=1:nbrOfT
    sBlockAverage(i) = mean(bA_s(x(end-20:end),i));
    semilogy(x, bA_s(x,i), 'color', cc(i,:), 'LineStyle','.');
    hold on
end
for i=1:nbrOfT
   semilogy([0 1e5], [sBlockAverage(i) sBlockAverage(i)], 'color', cc(i,:), 'LineStyle', '--'); 
end


xlabel('iteration number', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
text=legend('T=400 K', 'T=500 K', 'T=600 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
ylim([2e3 4e4])
%% Plot s through blockAveraging
hold on
plot(T, statInefficiency,'r');
plot(T, sBlockAverage)
xlabel('iteration number', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
title('s from block averaging and correlation function', 'FontSize', textStorlek)
text=legend('s-correlation function', 's-block averaging');
set(text, 'FontSize', legendStorlek);

%% Plot E, r, P with error bars
    




