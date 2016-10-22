function Hd = My_filter
%MY_FILTER Returns a discrete-time filter object.

%
% MATLAB Code
% Generated by MATLAB(R) 7.12 and the DSP System Toolbox 8.0.
%
% Generated on: 10-Dec-2013 21:19:23
%

% Equiripple Lowpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 48000;  % Sampling Frequency

Fpass = 1000;            % Passband Frequency
Fstop = 2000;            % Stopband Frequency
Dpass = 0.057501127785;  % Passband Ripple
Dstop = 0.063095734448;  % Stopband Attenuation
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