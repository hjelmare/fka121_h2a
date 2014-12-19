%% statistal inefficiency - U
% Calculates and plots the statistical inefficiency through correlation
% and block averaging

%% Calculate the statistical inefficiency for Energy!

cc=jet(nbrOfT);
for iTemperature = 1:nbrOfT;
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
%save('statInefficiency/statInefficiency_corr_E', 'statisticalInefficiencyE');
plot([0, xStop], [exp(-2), exp(-2)], 'r')
xlabel('data point displacement', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);

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
    eval(['varData = var(T' dataName{iTemperature} '(:,1) );']) 
    
    sOfB = zeros(Bmax(iTemperature),1);
    for i=Bmin:Bstep:Bmax(iTemperature)    
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
%    eval(['save(''T' dataName{iTemperature} 'BlockAverage_E'', ''sOfB_noZeros'') ']);
end
%save('statInefficiency/statInefficiency_block_E', 'statisticalInefficiencyE_block');

for i=1:nbrOfT %Plot the convergence of the block average.
    plot([0 Bmax], [statisticalInefficiencyE_block(i) statisticalInefficiencyE_block(i)], 'color', cc(i,:), 'Linestyle', '--');
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K', 'e^{-2}');
set(text, 'FontSize', legendStorlek);


