%% HP2 - Find P(T)
clear all
clc
textStorlek = 14;
legendStorlek = 11;

data = importdata('P_T.data'); %Något har hänt med denna!!!!!!!
T = data(:,1);
Pmin = data(:,2);
plot(T, Pmin)
xlabel('Temperature [K]')
ylabel('Long-range order parameter P')
%set(text, 'FontSize', legendStorlek);

%---------- figure with the energies as function of P (at diferent constant T)---------
figure
data = importdata('energyTask1.data');
plot(data(:,1),data(:,2))
title('P(T)', 'FontSize',textStorlek)
xlabel('Temperature [K]', 'FontSize', textStorlek)
ylabel('P', 'FontSize', textStorlek)
text = legend('Long range parameter P');


%% Task1 - plot energy and heat capacity as function of T;
data = importdata('UofT.data');
T_E = data(:,1);
E = data(:,2);
data = importdata('heatCapacity.data');
T_C = data(:,1);
C = data(:,2);

hold on
line(T_E,E,'Color','b')
ax1 = gca; % current axes
set(ax1, 'XColor', 'b')
set(ax1, 'YColor', 'b')
ylabel('mean field energy [eV]', 'FontSize', textStorlek)

ax1_pos = get(ax1, 'Position'); % position of first axes
ax2 = axes('Position',ax1_pos,'XAxisLocation','bottom', 'YAxisLocation','right',...
    'Color','none');

line(T_C, C,'Parent',ax2,'Color','k')
xlabel('temperature [K]', 'FontSize', textStorlek)
ylabel('heat capacity [eV/K]', 'FontSize', textStorlek)


%% TEST - Inte med i rapporten
clear all
clc

