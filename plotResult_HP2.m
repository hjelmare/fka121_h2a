%% HP2 - Find P(T)
clear all
clc

data = importdata('P_T.data');
T = data(:,1);
Pmin = data(:,2);
plot(T, Pmin)
xlabel('Temperature [K]')
ylabel('Long-range order parameter P')

%---------- figure with the energies as function of P (at diferent constant T)---------
figure
data = importdata('energyTask1.data');
plot(data(:,1),data(:,2))

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
ylabel('mean field energy [eV]')

ax1_pos = get(ax1, 'Position'); % position of first axes
ax2 = axes('Position',ax1_pos,'XAxisLocation','bottom', 'YAxisLocation','right',...
    'Color','none');

line(T_C, C,'Parent',ax2,'Color','k')
xlabel('temperature [K]')
ylabel('heat capacity [eV/K]')

%%
plot(T_E, E);

plot(T_C, C, 'r');
xlabel('temperature [K]')
ylabel('energy[eV] / heat capacity [eV/K]')

legend('energy(T) [eV]', 'heat capacity(T) [eV/K]')

%% TEST - Inte med i rapporten
clear all
clc

