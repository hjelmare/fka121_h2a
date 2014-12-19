clear all
clc

for i = 4:13
    filename = ['T' num2str(i) '00.data'];
    data = dlmread(filename,'\t');
    E(i-3) = mean(data(:,1));
    P(i-3) = mean(data(:,2));
    r(i-3) = mean(data(:,3));
end

clear data
clear filename
clear i

legendStorlek = 11;
textStorlek = 14;

temps = [4:13]*100;
figure(1)
plot(temps,E);
ylabel('Energy [eV]','FontSize',textStorlek);
xlabel('temperature [K]','FontSize',textStorlek);
h = legend('Energy [eV]');
set(h,'FontSize',legendStorlek);
saveas(gcf,'EofT.png','png');

figure(2)
plot(temps,-P);
ylabel('P','FontSize',textStorlek);
xlabel('temperature [K]','FontSize',textStorlek);
h = legend('P');
set(h,'FontSize',legendStorlek);
saveas(gcf,'PofT.png','png');

figure(3)
plot(temps,r);
ylabel('Short range order r','FontSize',textStorlek);
xlabel('temperature [K]','FontSize',textStorlek);
h = legend('Short range order r');
set(h,'FontSize',legendStorlek);
saveas(gcf,'rofT.png','png');