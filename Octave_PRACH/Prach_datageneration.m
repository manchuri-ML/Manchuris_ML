clc;
clear all;
close all;
%% Correlation Check
function [index,output]=my_xcorr(input1, input2)
for i=1:length(input2)
      output(i)=corr(input1,circshift(input2,-(i-1)));
endfor
[v,index]=max(output);
end

function [shift,root,output]=my_multi_xcorr(input1, input2)
for j=1:size(input1,1)
  for i=1:length(input2)
        output(j,i)=corr(input1(j,:),circshift(input2,-(i-1)));
  endfor
endfor
[mag1,shift1]=max(abs(output'));
root=find(mag1==max(mag1));
shift=shift1(root)-1;
end
%%
u = 6; % u = Root sequence index
uall=[1:64];
NZc= 839; % NZc = Length of Zadoff Chu Sequence
N_CS=13; % N_cs = Zero Correlation Zone Sequence
n=0:NZc-1;
shift_v=25;
% Generation Sequence
x_u_n = (exp(-1i*pi*u.*n.*(n+1)./NZc));
x_u_n_all= exp(-1i*pi*uall'.*(n.*(n+1))./NZc);
v=[0:1:floor(NZc/N_CS)-1];
for i=1:length(v)
  Preambles(i,:) = circshift(x_u_n,mod((i-1)*N_CS,NZc));
  #Preambles(i,:) = x_u_n(1+mod(n+(i-1)*N_CS,NZc));
end
labels=zeros(128,64*length(v));
Training_data_real=zeros(64*length(v),839);
Training_data_imag=
for i=1:64
  for j=1:length(v)
    Training_data(j+64*(i-1),:) = real(circshift(x_u_n_all(i,:),mod((j-1)*N_CS,NZc)));
    labels(i,j+(i-1)*64)=1;
    labels(j+64,j+(i-1)*64)=1;
  endfor
endfor
[Shift,Root,out]=my_multi_xcorr(x_u_n_all,Preambles(shift_v+1,:));
disp('Root Sequence index=');disp(Root)
disp('Shift index:');disp(Shift/N_CS);
#scatter(n,abs(output));
csvwrite ('Training_Data.csv',Training_data);
csvwrite ('Labels.csv',labels);
