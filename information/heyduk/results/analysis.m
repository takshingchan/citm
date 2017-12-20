%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

heyduk = [3.0 5.4 8.0 9.8]';

% Load results
ncf_ftd = load('ncf-ftd');
plain_ftd = load('plain-ftd');
cilibrasi = load('cilibrasi');

% Test whether cor(heyduk, ncf_ftd) > 0
fprintf('ncf-ftd\t\t');
printcor(heyduk, ncf_ftd);

% Test whether cor(heyduk, plain_ftd) > 0
fprintf('plain-ftd\t');
printcor(heyduk, plain_ftd);

% Test whether cor(heyduk, cilibrasi) > 0
fprintf('cilibrasi\t');
printcor(heyduk, cilibrasi);
