clear all
clc


data = dlmread('/media/My Passport/compPhys/T600.data','\t');

fid = fopen('/media/My Passport/compPhys/T600.bin','w');
fwrite(fid,data,'double');
fclose(fid);

fid = fopen('/media/My Passport/compPhys/T600.bin','r');

data = fread(fid,[20e6,3],'double');
fclose(fid);
disp(data(1:5,:))

disp('Done!')
