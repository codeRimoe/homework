% 读取数据
R0 = xlsread('r0.xlsx');
raw_Lr = xlsread('lr.xlsx');
raw_Lt = xlsread('lt.xlsx');

length = raw_Lr(:, 1);               % length(x-axid)
raw_Lr(:, 1) = 0;
raw_Lt(:, 1) = 0;
Rr = repmat(R0(1:701), 1, 70);       % R-reference
Lt = zeros(701, 7);                  % L-reference

% 计算反射率
raw_Rr = raw_Lt ./ raw_Lr .* Rr;

% 整合数据
for i = 0:6
    for j = 1:10
        Lt(:,i+1) = Lt(:, i + 1) + raw_Rr (:, i * 10 + j);
    end
end
Lt = Lt / 10;



%%  绘制波谱曲线

figure
hold on

plot(length,Rt(:,2), 'color', [0.00,0.50,0.00])
plot(length,Rt(:,5), 'color', [0.45,0.90,0.45])

plot(length,Rt(:,4), 'color', [0.70,0.70,0.15])

plot(length,Rt(:,3), 'color', [0.80,0.75,0.55])
plot(length,Rt(:,1), 'color', [0.55,0.40,0.15])

plot(length,Rt(:,6), 'color', [0.00,0.00,0.90])
plot(length,Rt(:,7), 'color', [0.55,0.55,0.90])

plot(length,Rr(:,1),'k--')
% grid on
legend('灌木／冠层', '草地', '枯叶', '水泥砖', '湿裸土', '水体（90°）', '水体（45°）', '标准板（30%）');
xlabel('波长/nm')
ylabel('反射率Rt')
title('地物波谱曲线')

%% 

figure
hold on

plot(length,Rt(:,2), 'color', [0.00,0.50,0.00])
plot(length,Rt(:,5), 'color', [0.45,0.90,0.45])


plot(length,Rr(:,1),'k--')
% grid on
legend('灌木／冠层', '草地','标准板（30%）');
xlabel('波长/nm')
ylabel('反射率Rt')
title('植被波谱曲线')     %添加图像标题


%%

figure
hold on

plot(length,Rt(:,6), 'color', [0.00,0.00,0.90])
plot(length,Rt(:,7), 'color', [0.55,0.55,0.90])

plot(length,Rr(:,1),'k--')
% grid on
legend('水体（90°）', '水体（45°）', '标准板（30%）');
xlabel('波长/nm')
ylabel('反射率Rt')
title('水体波谱曲线')     %添加图像标题

%% 

figure
hold on

plot(length,Rt(:,4), 'color', [0.70,0.70,0.15])

plot(length,Rt(:,3), 'color', [0.80,0.75,0.55])
plot(length,Rt(:,1), 'color', [0.55,0.40,0.15])

plot(length,Rr(:,1),'k--')
% grid on
legend('枯叶', '水泥砖', '湿裸土', '标准板（30%）');
xlabel('波长/nm')
ylabel('反射率Rt')
title('水体波谱曲线')     %添加图像标题