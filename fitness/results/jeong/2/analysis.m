%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

jeong = [-8.42 -10.81 -11.04]';

% Load results
one_f_uid1 = load('1-f-uid1');
white_uid1 = load('white-uid1');
brown_uid1 = load('brown-uid1');
one_f_uid2 = load('1-f-uid2');
white_uid2 = load('white-uid2');
brown_uid2 = load('brown-uid2');
one_f_uid3 = load('1-f-uid3');
white_uid3 = load('white-uid3');
brown_uid3 = load('brown-uid3');

% Print correlations
fprintf('jeong-uid1\t');
printcor(jeong, mean([one_f_uid1 white_uid1 brown_uid1])');
fprintf('jeong-uid2\t');
printcor(jeong, mean([one_f_uid2 white_uid2 brown_uid2])');
fprintf('jeong-uid3\t');
printcor(jeong, mean([one_f_uid3 white_uid3 brown_uid3])');
