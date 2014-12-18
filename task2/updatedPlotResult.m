%% Plot and calculate corelationfunction
clear all
clc

%Import result
fid = fopen('T1100.bin','r');
data = fread(fid,[10e6,3],'double');
fclose(fid);

%data = dlmread('T400.data', '\t');
T=1100;


correlation = xcov(data(:,1), 'coeff');
correlationStart = find(correlation == 1);
xStart = 0;
xStop = length(correlation) - correlationStart;
x = (0: xStop);

hold on
plot(x, correlation(correlationStart: end))
plot([0, xStop], [exp(-2), exp(-2)], 'r')

limit = find(correlation(correlationStart:end) < exp(-2), 1);

statInefficiency = 0;
for i=correlationStart:correlationStart+limit
   statInefficiency = statInefficiency + correlation(i);
end
statInefficiency = 2*statInefficiency

saveCorrelation = correlation(correlationStart:end);
save('correlation_s_T1100', 'saveCorrelation')

disp(['statistic inefficiency = ', num2str(statInefficiency)])
%% Plot & Calculate stat. inefficiency by using block averaging
Bmax = 100000;
Bmin = 100;
Bstep = 500;
varData = var(data(:,1));
sOfB = zeros(Bmax,1);
hold on
for i=Bmin:Bstep:Bmax
    B=i;
    nbrOfBlocks = fix(length(data(:,1))/B);
    meanData = zeros(nbrOfBlocks,1);
    for j=0:nbrOfBlocks-1
        start = j*B + 1;
        stop = (j+1)*B;
        meanData(j+1,1) = mean(data(start:stop,1));

    end
    varOfMean = var(meanData);
    
    sOfB(i) = B*varOfMean/varData;
end
save('blockAverage_s_T1100', 'sOfB');
plot(sOfB)

%% Calculate heat capacity
k_b = 8.61734e-5;
meanOfData = mean(data(:,1));
energySquared = data(:,1).^2;
meanOfDataSquared = mean(energySquared);
heatCapacity = (meanOfDataSquared - meanOfData^2)/(k_b*T);
save('heatCapacity_T1100', 'heatCapacity');

%% Save P, r and E as function of temperature
clear all
clc

%Import result
fid = fopen('/media/My Passport/compPhys/T200.bin','r');
T200 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T300.bin','r');
T300 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T400.bin','r');
T400 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T500.bin','r');
T500 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T600.bin','r');
T600 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T660.bin','r');
T660 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T700.bin','r');
T700 = fread(fid,[20e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T800.bin','r');
T800 = fread(fid,[10e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T900.bin','r');
T900 = fread(fid,[10e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T1000.bin','r');
T1000 = fread(fid,[10e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T1100.bin','r');
T1100 = fread(fid,[10e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T1200.bin','r');
T1200 = fread(fid,[10e6,3],'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T1300.bin','r');
T1300 = fread(fid,[10e6,3],'double');
fclose(fid);

textStorlek = 14;
legendStorlek = 11;
nbrOfT = 13;
dataName = {'200', '300', '400', '500', '600', '660', '700', '800', '900', '1000', '1100', '1200', '1300'};
temperature = [200 300 400 500 600 660 700 800 900 1000 1100 1200 1300];

%% Calculate the statistical inefficiency for Energy!

cc=jet(nbrOfT);
for iTemperature = 1:nbrOfT;
    iTemperature
    eval(['correlationEnergy = xcov(T' dataName{iTemperature} '(:,1), ''coeff''); ']);
    correlationStart = find(correlationEnergy == 1);
    xStop = length(correlationEnergy) - correlationStart;
    x = (0: xStop);
     
    hold on
    plot(x, correlationEnergy(correlationStart: end), 'color', cc(iTemperature,:))
     
    limit = find(correlationEnergy(correlationStart:end) < exp(-2), 1);
    
    statInefficiency = 0;
    for i=correlationStart:correlationStart+limit
        statInefficiency = statInefficiency + correlationEnergy(i);
    end
    statInefficiency = 2*statInefficiency;
    
    statisticalInefficiencyE(iTemperature) = statInefficiency; %This variable saves s(T), plot with block averageing
end

save('statInefficiency/statInefficiency_corr_E', 'statisticalInefficiencyE');
plot([0, xStop], [exp(-2), exp(-2)], 'r')
xlabel('data point displacement', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
xlim([0, 6e4])

%%
%-------------------------------------Block averaging-----------------
Bmax_small = 100000;
Bmax_large = 300000;
Bmax = [Bmax_large Bmax_large Bmax_large Bmax_large Bmax_large Bmax_large Bmax_large Bmax_small Bmax_small Bmax_small Bmax_small Bmax_small Bmax_small];
Bmin = 10000;
Bstep = 500;

cc=jet(nbrOfT);
cc(1,:)=[0 0 0 ];
cc(2,:)=[0.6 0.3 0.7];
cc(3,:)=[1 0.8 0.8];
cc(4,:)=[0 0 1];
cc(8,:)=[1 0.7 0];
cc(9,:)=[0.6 0.4 0];
cc(10,:)=[1 0 0];
hold on
for iTemperature = 1:nbrOfT
    iTemperature
    eval(['varData = var(T' dataName{iTemperature} '(:,1) );'])   
    sOfB = zeros(Bmax(iTemperature),1);
    for i=Bmin:Bstep:Bmax(iTemperature)    
        B=i
        eval(['nbrOfBlocks = fix(length(T' dataName{iTemperature} '(:,1))/B);'])
        meanData = zeros(nbrOfBlocks,1);
        for j=0:nbrOfBlocks-1
            start = j*B + 1;
            stop = (j+1)*B;
            eval(['meanData(' num2str(j) '+1,1) = mean(T' dataName{iTemperature} '(' num2str(start) ':' num2str(stop) ',1));'])
        end
        varOfMean = var(meanData);
         
        sOfB(i) = B*varOfMean/varData;
    end
    sOfB_noZeros = sOfB(Bmin:Bstep:end);
    statisticalInefficiencyE_block(iTemperature) = mean(sOfB_noZeros(end-40:end)); % Plot this with s from correlation function
    plot(sOfB(Bmin:Bstep:end), 'color', cc(iTemperature,:), 'LineStyle', '.')
    eval(['save(''T' dataName{iTemperature} 'BlockAverage_E'', ''sOfB_noZeros'') ']);
end
save('statInefficiency/statInefficiency_block_E', 'statisticalInefficiencyE_block');
%%
for i=1:nbrOfT %Plot the convergence of the block average.
    plot([0 Bmax], [statisticalInefficiencyE_block(i) statisticalInefficiencyE_block(i)], 'color', cc(i,:), 'Linestyle', '--');
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K', 'e^{-2}');
set(text, 'FontSize', legendStorlek);
%%

figure %plot statistical inefficiency from correlation & block average
hold on
plot(temperature, statisticalInefficiencyE)
plot(temperature, statisticalInefficiencyE_block, 'r')
xlabel('temperature [K]', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
title('Statistical inefficiency', 'FontSize', textStorlek)
text=legend('Correlation function', 'Block average');
set(text, 'FontSize', legendStorlek);


%% Calculate heatCapacity
k_b = 8.61734e-5;

for i=1:nbrOfT
   eval(['data = T' dataName{i} '(:,1);'])
   eval(['T(i) =' dataName{i} ';'])
   meanData = mean(data);
   energySqr = data.^2;
   meanDataSqr = mean(energySqr);
   heatCapacity(i) = (meanDataSqr - meanData^2)/(k_b*T(i)^2);
end

plot(T, heatCapacity);
xlabel('temperature [K]', 'FontSize', textStorlek);
ylabel('heat capacity [eV/K]','FontSize', textStorlek)
text=legend('C(T)');
set(text, 'FontSize', legendStorlek);






