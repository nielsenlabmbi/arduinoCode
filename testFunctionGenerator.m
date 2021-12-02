% JK 1 July 2020
%   Test drive the functionGenerator on the Arduino (Adafruit Feather M4 Express, SAMD51)
% JK 30 Sept 2020 
%   updated for 2 channels and amplifier circuit
%


% Commands:
%   !Set chan# wavename amp freq param3 param4
%   !Start
%   !Stop
%  
%  E.G.  cmdStr = '!Set 1 sin 400 4 0.00 0.00'
% 
% Beware!! The format is inflexible : case matters, 1 space separation and no
% trailing stuff.  
%
% so, premake command strings, including a base format string to be
% used later with sprintf to build the final cmdStr
%     '!Set 2 sin 404 1 0.00 0.00'
startStr = '!Start';
stopStr = '!Stop';
cmdFormatStr = '!Set %d %s %0.2f %0.2f %0.2f %0.2f';  % length limited!! 
cmdStr1 = cmdFormatStr;
cmdStr2 = cmdStr1;

% 'const'
BaudRate = 1000000;%  ...  1000000;
MinAmp = 0.1;
MaxAmp = 10.0;
DacRes = 1; % (3.3 / 4096);    % DAC resolution: range = 3.3 V, over 12-bits
ch1 = 1;
ch2 = 2; 

% prot params
blocks = 10; % 1;
numTrials = 20;
trialDur = 2; 
iti = 4;
phase = 0;
dutyCycle = 0;
numWaves = 5;   % sin, saw, ramp, tri, sqr

% "parameters"
% amps = rand([MinAmp, MaxAmp], numTrials, blocks)'; % sin z-p amp
amps = (rand(numTrials, blocks) * MaxAmp)';

freqs = randi([1,6], numTrials, blocks)' .* 20 ;
rampDurs = linspace(0.5, 0.9, numTrials); 
rampDurs = rampDurs(randperm(numTrials));

% convert to volts
amps = amps * DacRes;
    
% setup serial port 

if ~exist('port', 'var')
    % get a list of serial ports 
    allPorts = serialportlist;
    numPorts = size(allPorts, 2);

    for n = 1 : numPorts
        pname = allPorts(n);
        ndx = regexp(pname, 'ACM');      % on ubuntu, the M4 is /dev/ttyACMx

        if ~isempty(ndx)
            break;
        end     
    end

    fprintf('\npname = %s\n', pname);
    port = serialport(pname, BaudRate);
end

% the serial command processor is looking for both
configureTerminator(port,"CR/LF");   % CRUCIAL !!

% processing messages from the arduino?
% maybe not needed ... it's only debug type stuff now
configureCallback(port, "terminator", @processIncoming);


%%
% the trials 
for blockNum = 1 : blocks
     
    for trialNum = 1 : numTrials 
        
        waveSelector = mod(trialNum, numWaves);
        
         if waveSelector == 0
            waveName = 'sin';     
            % use the format string to make the final cmdStr
            cmdStr1 = sprintf(cmdFormatStr, ch1, waveName, amps(blockNum, trialNum), ...
                freqs(blockNum, trialNum), phase, dutyCycle);
            cmdStr2 = sprintf(cmdFormatStr, ch2, waveName, amps(blockNum, trialNum), ...
                freqs(blockNum, trialNum), phase, dutyCycle);
         elseif waveSelector == 1
            waveName = 'saw';
            sawFreq = freqs(blockNum, trialNum); 
            period = 1 / sawFreq;
            rampDur1 = rampDurs(trialNum);
            rampDur2 = period - rampDur1;
            
            if(rampDur1 >= period)
                rampDur1 = period * .8;
                rampDur2 = period - rampDur1;
                fprintf(2, '\nadjusting sawtooth rampDur1 from %0.2f to %0.2f\n', rampDurs(trialNum), rampDur1);
                fprintf(2, 'paused ...');
                pause(1);
            end
            cmdStr1 = sprintf(cmdFormatStr, ch1, waveName, amps(blockNum, trialNum), ...
                sawFreq, rampDur1, rampDur2);
            cmdStr2 = sprintf(cmdFormatStr, ch2, waveName, amps(blockNum, trialNum), ...
                sawFreq, rampDur1, rampDur2);
         
         elseif waveSelector == 2
            waveName = 'ramp';            
            holdDur = trialDur - 2 * rampDurs(trialNum);            
             cmdStr1 = sprintf(cmdFormatStr, ch1, waveName, amps(blockNum, trialNum), ...
                    rampDurs(trialNum), holdDur, rampDurs(trialNum));
             cmdStr2 = sprintf(cmdFormatStr, ch2, waveName, amps(blockNum, trialNum), ...
                    rampDurs(trialNum), holdDur, rampDurs(trialNum));                   
            
         elseif waveSelector == 3
             waveName = 'tri';             
             cmdStr1 = sprintf(cmdFormatStr, ch1, waveName, amps(blockNum, trialNum), ...
                    freqs(blockNum, trialNum), phase, dutyCycle);
             cmdStr2 = sprintf(cmdFormatStr, ch2, waveName, amps(blockNum, trialNum), ...
                    freqs(blockNum, trialNum), phase, dutyCycle);               
            
         elseif waveSelector == 4
             waveName = 'sqr';
             dutyCycle =  randi([20, 80]);        
             cmdStr1 = sprintf(cmdFormatStr, ch1, waveName, amps(blockNum, trialNum), ...
                    freqs(blockNum, trialNum), phase, dutyCycle);
             cmdStr2 = sprintf(cmdFormatStr, ch2, waveName, amps(blockNum, trialNum), ...
                    freqs(blockNum, trialNum), phase, dutyCycle);                
         end        
        
        % finally write the command
        writeline(port, cmdStr1);
        pause(0.05);
        writeline(port, cmdStr2);

        fprintf('\nbegin trial %d:\n\tcommand string =  %s \n', trialNum, cmdStr1);
        pause(0.1); 
        writeline(port, startStr);
        fprintf('\n%s\n', cmdStr1);
        pause(trialDur);
        writeline(port, stopStr);       
        fprintf('\ntrial %d finished\n', trialNum);
        pause(iti);

    end  % trials
end   % blocks

fprintf('\nProtocol finished\n\n');

%%  
% flush(port);
fclose(port);
delete port;
%%
close all;
clear all;
clc;
