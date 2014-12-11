clear all
clc

data = dlmread('T500.data','\t');

fid = fopen('T500.bin','w');
fwrite(fid,data,'double');
fclose(fid);

fid = fopen('T500.bin','r');
data = fread(fid,[10e6,3],'double');
fclose(fid);
disp(data(1:5,:))

disp('Done!')