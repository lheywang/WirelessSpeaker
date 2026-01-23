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
Fclk =  270e6;  % Hertz
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
Feedback_min = -100;
Feedback_max = 100;

% ADC parameters
Cs = 1e-7;      % Farad
Rs = 1e4;       % Ohm

Gmax = 1e3;
Vana = 5;       % Volt (symetrical)
SR = 1e3;       % Volt per second
Fc = 1e6;       % Hz
Rout = 10;      % Ohm
Rin = 1e6;      % Ohm

alpha = 0.9999;


%% Automated computations : 
% Frequency calculations
Fpwm = Fclk / PWM_Cycles;

%% Linearizing data
analog_plant = linearize("filter_model");
adc_integrator = linearize("adc_model");


