% =========================================================================
% l.heywang
% 24.11.2025
%
% Generate a point cloud of class D parameters, and show which one are
% possible. Used to choose the greatest parameters by showing them all.
% =========================================================================

% =========================================================================
% Parameters input
% =========================================================================
% Audio sampling frequency, at which the the PWM target is actuated
FS_min = 88200; % Hz
FS_max = 176400; % Hz

% Number of bits for the PWM. Greater numbers will get to high fabric
% clocks really fast !
PWM_bits_min = 8;   % Bits
PWM_bits_max = 10;  % Bits

% Number of PWM cycles per audio sample (1 / Fs).
PWM_cycles_min = 6;  % N
PWM_cycles_max = 12;  % N

% Resolution of the ADC used to sample (Use a value near the ENOB !)
Feedback_res_min = 16; % Bits
Feedback_res_max = 20; % Bits

% Feedback loop gain taht can be achieved.
Feedback_gain_min = 45; % dB
Feedback_gain_max = 70; % dB

% FPGA Max frequency, used to color points that are impossible.
FPGA_max_freq = 400000000; % 400 MHz

% =========================================================================
% Generating arrays
% =========================================================================
PWM_bits = zeros(1, (PWM_bits_max - PWM_bits_min + 1));
PWM_cycles = zeros(1, (PWM_cycles_max - PWM_cycles_min + 1));
FS = zeros(1, ((FS_max - FS_min) / FS_min + 1));
Feedback_res = zeros(1, (Feedback_res_max - Feedback_res_min + 1));
Feedback_gain = zeros(1, (Feedback_gain_max - Feedback_gain_min + 1));

for k = PWM_bits_min:PWM_bits_max
    PWM_bits((k - PWM_bits_min + 1)) = k;
end
for k = PWM_cycles_min:PWM_cycles_max
    PWM_cycles((k - PWM_cycles_min + 1)) = k;
end
for k = Feedback_res_min:Feedback_res_max
    Feedback_res((k - Feedback_res_min + 1)) = k;
end
for k = Feedback_gain_min:Feedback_gain_max
    Feedback_gain((k - Feedback_gain_min + 1)) = k;
end
for k = (FS_min / FS_min):(FS_max / FS_min)
   FS(k) = k * FS_min;
end

% Create all combinations
cases = combinations(PWM_bits, PWM_cycles, FS, Feedback_res, Feedback_gain);
sz = size(cases);
rows = sz(1);

% Allocate memory for the outputs
Ffabric = zeros(1, sz(1));
EQbits = zeros(1, sz(1));
ratio = zeros(1, sz(1));
labels = cell(rows,1);
colors = zeros(rows, 3);  % R G B

% =========================================================================
% Main loop : 
% =========================================================================
for k = 1:rows
    line = cases(k,:);

    % Calculating the requested FPGA frequency
    Ffabric(k) = line.FS * line.PWM_cycles * (2^line.PWM_bits);
    EQbits(k) = min([ ...
        (line.PWM_bits + (line.Feedback_gain / 6.02)) ...
        line.Feedback_res] ...
    );

    % Getting the ratio to get the color output :
    ratio(k) = Ffabric(k) / FPGA_max_freq;

    if ratio(k) < 0.5
        colors(k,:) = [0.0 0.8 0.0];        % green
    elseif ratio(k) < 0.75
        colors(k,:) = [0.9 0.9 0.1];        % yellow
    elseif ratio(k) < 0.90
        colors(k,:) = [1.0 0.55 0.0];       % orange
    elseif ratio(k) < 1.0
        colors(k,:) = [1.0 0.0 0.0];        % red
    else
        colors(k,:) = [0.5 0.0 0.0];        % dark red
    end

    % Creating the labels names
    labels{k} = sprintf('FS       = %d\nPWM_cycles = %d\nPWM_width  = %d\nLoop gain  = %d\nLoop res   = %d', ...
        line.FS, ...
        line.PWM_cycles, ...
        line.PWM_bits, ...
        line.Feedback_gain, ...
        line.Feedback_res);
end

% =========================================================================
% Plotting data
% =========================================================================figure;
figure(1);
s = scatter(Ffabric, EQbits, 40, colors, 'filled');
xlabel('Ffabric');
ylabel('EQbits');
title('FPGA Feasibility Point Cloud');
grid on;

tipRow = dataTipTextRow('Info', labels);
s.DataTipTemplate.DataTipRows(end+1) = tipRow;