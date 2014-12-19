%% import data
% This data is used in the different matlab programs.

clear all
clc

%Used by all matlab files.
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

%Import saved s-values from correlation function and block averaging:
% Used by "plotQuantitiesWithError.m"
s_block_E=importdata('statInefficiency/statInefficiency_block_E.mat');
s_block_P=importdata('statInefficiency/statInefficiency_block_P.mat');
s_block_r=importdata('statInefficiency/statInefficiency_block_r.mat');
s_corr_E=importdata('statInefficiency/statInefficiency_corr_E.mat');
s_corr_P=importdata('statInefficiency/statInefficiency_corr_P.mat');
s_corr_r=importdata('statInefficiency/statInefficiency_corr_r.mat');

%variables that are used in the following cells
nbrOfT=13;
textStorlek=14;
legendStorlek =11;

names = {'200', '300', '400', '500', '600', '660', '700', '800', '900', '1000', '1100', '1200', '1300'};
temperature = [200 300 400 500 600 660 700 800 900 1000 1100 1200 1300];
%%
