% -------------------------------------------------------------------------
% controller.m
%
% l.heywang <leonard.heywang@proton.me>
% 21/01/2026
%
% This file provide the base workspace variables for the simulation of the 
% whole class D controller loop.
% -------------------------------------------------------------------------

%% Init of the script
clear variables;
close all;

%% Configure variables
% Project wide parameters
Vcc = 24;       % Volt
Fs = 96e3;      % Hertz
PWM_Cycles = 11;
PWM_Bits = 8;

% LC Reconstructions filters (two stages)
L0 = 22e-6;     % Henry
L1 = 705.6e-9;  % Henry

RL0 = 0.5;      % Ohm
RL1 = 0.5;      % Ohm

C0 = 22e-6;     % Farad
C1 = 100e-9;    % Farad

C0R = 0.5;      % Ohm
C1R = 0.5;      % Ohm

Rspk = 5.9;     % Ohm

% Gate driver parameters
Dgate = 20e-9;  % Second

% Feedback parameters
Feedback_min = -Vcc;
Feedback_max = Vcc;

% ADC parameters
Cs = 1e-7;      % Farad
Rs = 1e4;       % Ohm

% Analog section
Gmax = 1e3;
Vana = 3.3;     % Volt (single ended)
SR = 1e3;       % Volt per second
Fc = 1e6;       % Hz
Rout = 10;      % Ohm
Rin = 1e6;      % Ohm

% Comparator
Hys = 0.1;      % Volt

% Analog protection 
Vmax = 33;      % Volt

% Digital filters
alpha = 0.9999;
dc_gain = -0.1;

% ADC speed (factor of Fpwm clock)
adc_clk = 32;

% Accumulator

accumulator_gain = Vmax / adc_clk;

%% Automated computations : 
% Counter resolution
Cnt_res = 1 / ((2 ^ PWM_Bits) - 1);

% Frequency calculations
Fpwm = Fs * PWM_Cycles;
Fcnt = Fpwm * (2 ^ PWM_Bits);
Fadc = Fpwm * adc_clk;

% Analog computations
AnalogDiv = Vmax / Vana;

%% Linearizing data
analog_plant = linearize("filter_model");
adc_integrator = linearize("adc_model");


