function [ dataX, dataY ] = extractData( data )
%EXTRACTDATA Summary of this function goes here
%   Detailed explanation goes here

data1000   = data(find(data==1000),2);
data5000   = data(find(data==5000),2);
data10000  = data(find(data==10000),2);
data50000  = data(find(data==50000),2);
data100000 = data(find(data==100000),2);
data500000 = data(find(data==500000),2);

% mean1000 = mean(data1000);
% mean5000 = mean(data5000);
% mean10000 = mean(data10000);
% mean50000 = mean(data50000);
% mean100000 = mean(data100000);
% mean500000 = mean(data500000);

dataY = [];
dataX = [];
tmp = zeros(10,1);
if (data1000 ~= 0)
    dataY = [dataY data1000];
    dataX = [dataX tmp+1000];
end
if (data5000 ~= 0)
    dataY = [dataY data5000];
    dataX = [dataX tmp+5000];
end
if (data10000 ~= 0)
    dataY = [dataY data10000];
    dataX = [dataX tmp+10000];
end
if (data50000 ~= 0)
    dataY = [dataY data50000];
    dataX = [dataX tmp+50000];
end
if (data100000 ~= 0)
    dataY = [dataY data100000];
    dataX = [dataX tmp+100000];
end
if (data500000 ~= 0)
    dataY = [dataY data500000];
    dataX = [dataX tmp+500000];
end

end

