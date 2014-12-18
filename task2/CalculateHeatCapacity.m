clear all
clc

k_B = 8.61734e-5;

% get some data, import from file...
energy = rand(1,1000000);
T = 1;

nPoints = length(energy);
blockSize = 100;
nBlocks = nPoints / blockSize;

for i = 1:(nBlocks - 1)
    bStart = 1+100*i;
    bEnd = 100+100*i;

    blockAverageEnergy(i) = sum(energy(bStart:bEnd)) / blockSize;
end

energyVariance = var(blockAverageEnergy);
heatCapacity = 1/(k_B * T^2) * energyVariance;

meanEnergy = mean(blockAverageEnergy);
fourthMoment = mean( (blockAverageEnergy - meanEnergy).^4 );

heatVariance = 1/(nBlocks) * (fourthMoment - (nBlocks - 3)/(nBlocks - 1)*energyVariance^2);

disp('   C                   Var(C)')
disp([heatCapacity, heatVariance])