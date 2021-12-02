%% JK 13 Jan 2021 
%   Function generator calibration.  Use the scope peak-to-peak
%   measurements for ~100 counts
%

%% JK 6 Apr 2021, bench4 rig

cmd    = [   100,  200,   300,  400,  640, 1024, 1300, 1600, 2000];
voltsA = [ 0.538, 1.04,  1.54, 2.03, 3.20, 5.27, 6.64, 8.20, 10.00 ];
voltsB = [ 0.513, 1.02,  1.51, 2.02, 3.21, 5.21, 6.55, 8.00, 9.90 ];


%%
figure(342);
clf; hold on;
plot(cmd, voltsA);
plot(cmd, voltsA, 'ro', 'MarkerSize', 10);

%%
plot(cmd, voltsB);
plot(cmd, voltsB, 'k*', 'MarkerSize', 10);

%%
[coeffsA, mu] = polyfit(voltsA, cmd,   1);
[coeffsB, mu] = polyfit(voltsB, cmd,   1);
%%
fitA = polyval(coeffsA, voltsA);
fitB = polyval(coeffsB, voltsB);


%%
figure(342);
clf; hold on;
subplot(2, 1, 1);
hold on;
plot(voltsA, cmd, 'ro');
subplot(2, 1, 1);
plot(voltsA,fitA,  'b');
%%
subplot(2, 1, 2);
hold on;
plot(voltsB, cmd, 'ro');
subplot(2, 1, 2);
plot(voltsB,fitB,  'b');
