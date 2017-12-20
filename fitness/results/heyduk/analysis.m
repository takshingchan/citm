%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

heyduk = [5.3 8.1 9.7 8.8]';

% Load results
heyduk_uid1 = load('heyduk-uid1');
heyduk_uid2 = load('heyduk-uid2');
heyduk_uid3 = load('heyduk-uid3');

% Test whether cor(heyduk, heyduk_uid1) > 0
fprintf('heyduk_uid1\t');
printcor(heyduk, heyduk_uid1);

% Test whether cor(heyduk, heyduk_uid2) > 0
fprintf('heyduk-uid2\t');
printcor(heyduk, heyduk_uid2);

% Test whether cor(heyduk, heyduk_uid3) > 0
fprintf('heyduk-uid3\t');
printcor(heyduk, heyduk_uid3);
