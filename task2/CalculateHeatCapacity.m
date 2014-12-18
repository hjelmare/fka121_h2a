clear all
clc

k_B = 8.61734e-5;

T = 900;
fid = fopen('/media/My Passport/compPhys/T900.bin','r');
energy = fread(fid,[20e6,3],'double');
fclose(fid);

prefactor = 1/(k_B * T^2);

energyVariance = var(energy);
heatCapacity = prefactor * energyVariance;

disp('   C')
disp([heatCapacity, heatVariance])

