%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

shmulevich = [1.56 2.12 2.08 1.88 1.80 2.44 2.20 2.56 3.00 2.04 2.76 2.72 3.00 3.16 2.04 2.88 2.60 2.60 2.64 3.24 3.08 3.04 3.04 2.56 2.56 2.84 3.60 2.68 3.28 3.08 3.52 3.60 3.04 2.88 3.08]';

% Load results
ncf_ftd = load('ncf-ftd');
plain_ftd = load('plain-ftd');
cilibrasi = load('cilibrasi');

% Test whether cor(shmulevich, ncf_ftd) > 0
fprintf('ncf-ftd\t\t');
printcor(shmulevich, ncf_ftd);

% Test whether cor(shmulevich, plain_ftd) > 0
fprintf('plain-ftd\t');
printcor(shmulevich, plain_ftd);

% Test whether cor(shmulevich, cilibrasi) > 0
fprintf('cilibrasi\t');
printcor(shmulevich, cilibrasi);
