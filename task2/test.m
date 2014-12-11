clear all
clc

data = dlmread('T1300.data','\t');
%%


fid = fopen('T1300.bin','w');
fwrite(fid,data,'double');
fclose(fid);


%%

clear all
clc

fid = fopen('T1300.bin','r');
data = fread(fid,[1e6,3],'double');
fclose(fid);
disp(data)