function  powerGraph( dataC, dataQ, dataQR, dataQRS, dataQS, str, saveName)

dataC = log(dataC);
dataQ = log(dataQ);
dataQR = log(dataQR);
dataQRS = log(dataQRS);
dataQS = log(dataQS);

maxX = max([max(max(dataC(:,:,1))) max(max(dataQ(:,:,1))) max(max(dataQR(:,:,1))) max(max(dataQRS(:,:,1))) max(max(dataQS(:,:,1)))])*1.1; 
maxY = max([max(max(dataC(:,:,2))) max(max(dataQ(:,:,2))) max(max(dataQR(:,:,2))) max(max(dataQRS(:,:,2))) max(max(dataQS(:,:,2)))])*1.1;

%mean value
mdC(1,:) = mean(dataC(:,:,1),1);
mdC(2,:) = mean(dataC(:,:,2),1);
mdQ(1,:) = mean(dataQ(:,:,1),1);
mdQ(2,:) = mean(dataQ(:,:,2),1);
mdQR(1,:) = mean(dataQR(:,:,1),1);
mdQR(2,:) = mean(dataQR(:,:,2),1);
mdQRS(1,:) = mean(dataQRS(:,:,1),1);
mdQRS(2,:) = mean(dataQRS(:,:,2),1);
mdQS(1,:) = mean(dataQS(:,:,1),1);
mdQS(2,:) = mean(dataQS(:,:,2),1);

tmp = fitlm(mdC(1,:),mdC(2,:));
ord_orig_C = table2array(tmp.Coefficients(1,1));
abs_orig_C = table2array(tmp.Coefficients(2,1));
tmp = fitlm(mdQ(1,:),mdQ(2,:));
ord_orig_Q = table2array(tmp.Coefficients(1,1));
abs_orig_Q = table2array(tmp.Coefficients(2,1));
tmp = fitlm(mdQR(1,:),mdQR(2,:));
ord_orig_QR = table2array(tmp.Coefficients(1,1));
abs_orig_QR = table2array(tmp.Coefficients(2,1));
tmp = fitlm(mdQRS(1,:),mdQRS(2,:));
ord_orig_QRS = table2array(tmp.Coefficients(1,1));
abs_orig_QRS = table2array(tmp.Coefficients(2,1));
tmp = fitlm(mdQS(1,:),mdQS(2,:));
ord_orig_QS = table2array(tmp.Coefficients(1,1));
abs_orig_QS = table2array(tmp.Coefficients(2,1));

legendC = ['CountingSort y=' num2str(abs_orig_C) 'x + ' num2str(ord_orig_C)];
legendQ = ['QuickSort y=' num2str(abs_orig_Q) 'x + ' num2str(ord_orig_Q)];
legendQR = ['QuickRandomSort y=' num2str(abs_orig_QR) 'x + ' num2str(ord_orig_QR)];
legendQRS = ['QuickRandomSeuilSort y=' num2str(abs_orig_QRS) 'x + ' num2str(ord_orig_QRS)];
legendQS = ['QuickSeuilSort y=' num2str(abs_orig_QS) 'x + ' num2str(ord_orig_QS)];

lrC = [ones(length(mdC(1,:)'),1) mdC(1,:)'] *([ones(length(mdC(1,:)'),1) mdC(1,:)'] \ mdC(2,:)');
lrQ = [ones(length(mdQ(1,:)'),1) mdQ(1,:)'] *([ones(length(mdQ(1,:)'),1) mdQ(1,:)'] \ mdQ(2,:)');
lrQR = [ones(length(mdQR(1,:)'),1) mdQR(1,:)'] *([ones(length(mdQR(1,:)'),1) mdQR(1,:)'] \ mdQR(2,:)');
lrQRS = [ones(length(mdQRS(1,:)'),1) mdQRS(1,:)'] *([ones(length(mdQRS(1,:)'),1) mdQRS(1,:)'] \ mdQRS(2,:)');
lrQS = [ones(length(mdQS(1,:)'),1) mdQS(1,:)'] *([ones(length(mdQS(1,:)'),1) mdQS(1,:)'] \ mdQS(2,:)');

figure,
plot(mdC(1,:),lrC, mdQ(1,:),lrQ, mdQR(1,:),lrQR, mdQRS(1,:),lrQRS ,mdQS(1,:),lrQS)
hold on
plot(dataC(:,:,1),  dataC(:,:,2),   'ko')
plot(dataQ(:,:,1),  dataQ(:,:,2),   'ko')
plot(dataQR(:,:,1), dataQR(:,:,2),  'ko')
plot(dataQRS(:,:,1),dataQRS(:,:,2), 'ko')
plot(dataQS(:,:,1), dataQS(:,:,2),  'ko')
xlabel('Taille exemplaire')
ylabel('Temps d''execution(ns)')
xlim([0 maxX])
ylim([0 maxY])
legend(legendC,legendQ,legendQR,legendQRS,legendQS,'Location','best')
title(str)
grid on
saveas(gcf, saveName)
close
end

