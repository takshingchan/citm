%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

% Load experimental data
essen = load('essen');

% Load results
essen_uid1 = load('essen-uid1');
essen_uid2 = load('essen-uid2');
essen_uid3 = load('essen-uid3');

% Test whether cor(essen, essen_uid1) > 0
fprintf('essen-uid1\t');
printcor(essen, essen_uid1);

% Test whether cor(essen, essen_uid2) > 0
fprintf('essen-uid2\t');
printcor(essen, essen_uid2);

% Test whether cor(essen, essen_uid3) > 0
fprintf('essen-uid3\t');
printcor(essen, essen_uid3);
