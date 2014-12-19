%% Plot Energy, r, P with error
%% Plot Energy with error
close all
errorBarMagnifying = 100;

for i=1:nbrOfT
    eval(['data = T' names{i} ';']) %saves data from a temperature in data
    dataLength = length(data(:,1));
    varData = var(data(:,1));
    errorCorr(i) = (s_corr_E(i)/dataLength)*varData;
    errorBlock(i) = (s_block_E(i)/dataLength)*varData;
    
    Energy(i)=mean(data(end-100000:end,1));
end
errorCorr = errorCorr.^(1/2);
errorBlock = errorBlock.^(1/2);

hold on
errorbar(temperature, Energy, errorCorr*errorBarMagnifying, 'r')
hold on
h=errorbar(temperature, Energy, errorBlock*errorBarMagnifying);
xlabel('temperature', 'FontSize', textStorlek);
ylabel('Energy [eV]','FontSize', textStorlek);
title('Energy over temperature', 'FontSize', textStorlek);
text=legend(h,'Energy');
set(text, 'FontSize', legendStorlek);

%% Plot long/short range order parameter (P and r) with error
close all
errorBarMagnifying_P = 1;
errorBarMagnifying_r = 100;

%Long range order parameter
for i=1:nbrOfT
    eval(['data = T' names{i} ';'])
    dataLength = length(data(:,2));
    varData = var(data(:,2));
    errorCorr(i) = (s_corr_P(i)/dataLength)*varData;
    errorBlock(i) = (s_block_P(i)/dataLength)*varData;
    
    parameter_P(i)=mean(abs(data(end-100000:end,2)));
end
errorCorr = errorCorr.^(1/2);
errorBlock = errorBlock.^(1/2);

hold on
errorbar(temperature, parameter_P, errorCorr*errorBarMagnifying_P, 'r')
h1=errorbar(temperature, parameter_P, errorBlock*errorBarMagnifying_P);

%short range order parameter
for i=1:nbrOfT
    eval(['data = T' names{i} ';'])
    dataLength = length(data(:,3));
    varData = var(data(:,3));
    errorCorr(i) = (s_corr_r(i)/dataLength)*varData;
    errorBlock(i) = (s_block_r(i)/dataLength)*varData;
    
    parameter_r(i)=mean(abs(data(end-100000:end,3)));
end
errorCorr = errorCorr.^(1/2);
errorBlock = errorBlock.^(1/2);

hold on
g=errorbar(temperature, parameter_r, errorCorr*errorBarMagnifying_r);
gc=get(g, 'Children');
set(gc(2), 'color','r')
hold on
h2=errorbar(temperature, parameter_r, errorBlock*errorBarMagnifying_r, 'r');
h2c=get(h2, 'Children');
set(h2c(2), 'color', 'b')
xlabel('temperature', 'FontSize', textStorlek);
ylabel('short-/long- range order parameter','FontSize', textStorlek);
title('Short and long range order parameters over temperature', 'FontSize', textStorlek);
text=legend([h1 h2],'Long range order parameter', 'Short range order parameter');
set(text, 'FontSize', legendStorlek);