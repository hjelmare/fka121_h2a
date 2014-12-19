%% Plot heat capacity

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

