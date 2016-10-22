function Hd = lowpass_firfilter
%LOWPASS_FIRFILTER Returns a discrete-time filter object.

%
% MATLAB Code
% Generated by MATLAB(R) 7.12 and the Signal Processing Toolbox 6.15.
%
% Generated on: 22-Aug-2014 18:30:30
%

% Equiripple Lowpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 44211;  % Sampling Frequency

Fpass = 2000;            % Passband Frequency
Fstop = 3000;            % Stopband Frequency
Dpass = 0.057501127785;  % Passband Ripple
Dstop = 0.001;           % Stopband Attenuation
dens  = 20;              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fpass, Fstop]/(Fs/2), [1 0], [Dpass, Dstop]);

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, Fo, Ao, W, {dens});
Hd = dfilt.dffir(b);

% Set the arithmetic property.
set(Hd, 'Arithmetic', 'fixed', ...
    'CoeffWordLength', 16, ...
    'CoeffAutoScale', false, ...
    'NumFracLength', 15, ...
    'Signed',         true, ...
    'InputWordLength', 16, ...
    'inputFracLength', 15, ...
    'FilterInternals',  'SpecifyPrecision', ...
    'OutputWordLength',  16, ...
    'OutputFracLength',  15, ...
    'ProductWordLength', 32, ...
    'ProductFracLength', 31, ...
    'AccumWordLength',   40, ...
    'AccumFracLength',   31, ...
    'RoundMode',         'convergent', ...
    'OverflowMode',      'Wrap');
denormalize(Hd);

% [EOF]