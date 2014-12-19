%% Statistical inefficiency - P
% Calculates and plots the statistical inefficiency through correlation
% and block averaging
%
%% Calculate the statistical inefficiency - correlation
cc=jet(nbrOfT);
for iTemperature = 1:nbrOfT;
    iTemperature
    eval(['correlation_P = xcov(T' dataName{iTemperature} '(:,2), ''coeff''); ']);
    correlationStart = find(correlation_P == 1);
    xStop = length(correlation_P) - correlationStart;
    x = (0: xStop);
     
    hold on
    plot(x, correlation_P(correlationStart: end), 'color', cc(iTemperature,:))
     
    limit = find(correlation_P(correlationStart:end) < exp(-2), 1);
    
    statInefficiency = 0;
    for i=correlationStart:correlationStart+limit
        statInefficiency = statInefficiency + correlation_P(i);
    end
    statInefficiency = 2*statInefficiency;
    
    statisticalInefficiency_P(iTemperature) = statInefficiency; %This variable saves s(T), plot with block averageing
end
%save('statInefficiency/statInefficiency_corr_P', 'statisticalInefficiency_P');
plot([0, xStop], [exp(-2), exp(-2)], 'r')
xlabel('data point displacement', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K', 'e^{-2}');
set(text, 'FontSize', legendStorlek);
%xlim([0, 6e4])

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
    eval(['varData = var(T' dataName{iTemperature} '(:,2) );'])
    
    sOfB = zeros(Bmax(iTemperature),1);
    for i=Bmin:Bstep:Bmax(iTemperature)
        eval(['nbrOfBlocks = fix(length(T' dataName{iTemperature} '(:,2))/B);'])
        meanData = zeros(nbrOfBlocks,1);
        for j=0:nbrOfBlocks-1
            start = j*B + 1;
            stop = (j+1)*B;
            eval(['meanData(' num2str(j) '+1,1) = mean(T' dataName{iTemperature} '(' num2str(start) ':' num2str(stop) ',2));'])
        end
        varOfMean = var(meanData);
         
        sOfB(i) = B*varOfMean/varData;
    end
    sOfB_noZeros = sOfB(Bmin:Bstep:end);
    statisticalInefficiency_block_P(iTemperature) = mean(sOfB_noZeros(end-40:end)); % Plot this with s from correlation function
    plot(sOfB(Bmin:Bstep:end), 'color', cc(iTemperature,:))
%    eval(['save(''T' dataName{iTemperature} 'BlockAverage_P'', ''sOfB_noZeros'') ']);
end
%save('statInefficiency/statInefficiency_block_P', 'statisticalInefficiency_block_P');
for i=1:nbrOfT %Plot the convergence of the block average.
    plot([0 Bmax(i)/Bstep], [statisticalInefficiency_block_P(i) statisticalInefficiency_block_P(i)], 'color', cc(i,:), 'Linestyle', '--');
end
xlabel('block size', 'FontSize', textStorlek);
ylabel('correlation','FontSize', textStorlek)
text=legend('T=200 K', 'T=300 K', 'T=400 K', 'T=500 K', 'T=600 K', 'T=660 K', 'T=680 K', 'T=700 K', 'T=800 K', 'T=900 K', 'T=1000 K', 'T=1100 K', 'T=1200 K', 'T=1300 K');
set(text, 'FontSize', legendStorlek);
