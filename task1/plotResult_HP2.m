%% Colorful plot of F(P) for different T
clear all
clc
clf

textStorlek = 14;
legendStorlek = 11;

data = dlmread('freeEnergy.data','\t');

P = data(:,1);
T = data(:,2);
F = data(:,3);

nPoints = find(P==0, 2);
nPoints = nPoints(2)-1;
nIterations = length(P)/nPoints;

cc=jet(nIterations);

figure(1)
hold on
for i= 0:nIterations-1
    plot(P(i*nPoints + 1 :(i+1)*nPoints), F(i*nPoints + 1 :(i+1)*nPoints), 'color', cc(i+1,:));
end

colorbar('YTick', [1 32 65], 'YTickLabel', ...
    {['T=' num2str(T(1)) ' K'], ['T=' num2str(T(length(T)/2)) ' K'], ['T=' num2str(T(end))  ' K']}, 'FontSize', textStorlek)

xlabel('Long range order parameter, P', 'FontSize', textStorlek)
ylabel('Mean field free energy [eV]', 'FontSize', textStorlek)

saveas(gcf,'task1freeEnergy.png','png')

%% P(T)
clear all
clc

textStorlek = 14;

data = dlmread('upc.data');
T = data(:,1);
P = data(:,3);

figure(2)

plot(T,P)
title('P(T)', 'FontSize',textStorlek)
xlabel('Temperature [K]', 'FontSize', textStorlek)
ylabel('P', 'FontSize', textStorlek)
text = legend('Long range parameter P');

saveas(gcf,'task1longRange.png','png')

%% E(T) and C(T)
clear all
clc
clf

textStorlek = 14;

data = dlmread('upc.data');
T = data(:,1);
E = data(:,2);
C = data(:,4);

E  = smooth(E,25);
C = smooth(diff(E),10);
C = [ C ; C(end) ]; % just patching to equal length

figure(3)

hold on
line(T,E,'Color','b')
ax1 = gca; % current axes
set(ax1, 'XColor', 'b')
set(ax1, 'YColor', 'b')
ylabel('mean field energy U [eV]', 'FontSize', textStorlek)

ax1_pos = get(ax1, 'Position'); % position of first axes
ax2 = axes('Position',ax1_pos,'XAxisLocation','bottom', 'YAxisLocation','right',...
    'Color','none');

line(T, C,'Parent',ax2,'Color','k')
xlabel('temperature [K]', 'FontSize', textStorlek)
ylabel('heat capacity [eV/K]', 'FontSize', textStorlek)

saveas(gcf,'task1heat.png','png')
