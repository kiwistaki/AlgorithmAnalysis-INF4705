close all;
clear all;

saveDir = '../Figures/'; 
if exist(saveDir, 'dir') == 0
    mkdir(saveDir);
end

for i = 1 : 3
    dataX = [];
    dataY = [];
    % Path to each file
    countingData = csvread(['..\counting_serie' num2str(i) '.csv']);
    quick = csvread(['..\quick_serie' num2str(i) '.csv']);
    quickRandom = csvread(['..\quickRandom_serie' num2str(i) '.csv']);
    quickRandomSeuil = csvread(['..\quickRandomSeuil_serie' num2str(i) '.csv']);
    quickSeuil = csvread(['..\quickSeuil_serie' num2str(i) '.csv']);

    % Extraction of data
    [dataX1,dataY1] = extractData(countingData);
    [dataX2,dataY2] = extractData(quick);
    [dataX3,dataY3] = extractData(quickRandom);
    [dataX4,dataY4] = extractData(quickRandomSeuil);
    [dataX5,dataY5] = extractData(quickSeuil);

    % Combining data
    dataC = dataX1;
    dataC(:,:,2) = dataY1;
    dataQ = dataX2;
    dataQ(:,:,2) = dataY2;
    dataQR = dataX3;
    dataQR(:,:,2) = dataY3;
    dataQRS = dataX4;
    dataQRS(:,:,2) = dataY4;
    dataQS = dataX5;
    dataQS(:,:,2) = dataY5;
    


    % Plot calls
    title = ['Test de puissance pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_puissance.png'];
    powerGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, saveName);
    
    title = ['Test du rapport pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_rapportx.png'];
    rapportGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 1, saveName);
    
    title = ['Test du rapport pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_rapportxlogx.png'];
    rapportGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 2, saveName);
    
    title = ['Test du rapport pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_rapportx2.png'];
    rapportGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 3, saveName);  
    
    title = ['Test de la constante pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_constantex.png'];
    constanteGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 1, saveName);
    
    title = ['Test de la constante pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_constantexlogx.png'];
    constanteGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 2, saveName);
    
    title = ['Test de la constante pour la serie ' num2str(i)];
    saveName = [saveDir 'serie' num2str(i) '_constantex2.png'];
    constanteGraph(dataC, dataQ, dataQR, dataQRS, dataQS, title, 3, saveName);
end
