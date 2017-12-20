%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

vitz = [3.47 5.74 5.85 5.72 5.43 4.82]';

% Load results
vitz_1_uid1 = load('1-uid1');
vitz_2_uid1 = load('2-uid1');
vitz_3_uid1 = load('3-uid1');
vitz_4_uid1 = load('4-uid1');
vitz_5_uid1 = load('5-uid1');
vitz_6_uid1 = load('6-uid1');
vitz_1_uid2 = load('1-uid2');
vitz_2_uid2 = load('2-uid2');
vitz_3_uid2 = load('3-uid2');
vitz_4_uid2 = load('4-uid2');
vitz_5_uid2 = load('5-uid2');
vitz_6_uid2 = load('6-uid2');
vitz_1_uid3 = load('1-uid3');
vitz_2_uid3 = load('2-uid3');
vitz_3_uid3 = load('3-uid3');
vitz_4_uid3 = load('4-uid3');
vitz_5_uid3 = load('5-uid3');
vitz_6_uid3 = load('6-uid3');

% Print correlations
fprintf('vitz-uid1\t');
printcor(vitz, mean([vitz_1_uid1 vitz_2_uid1 vitz_3_uid1 vitz_4_uid1 vitz_5_uid1 vitz_6_uid1])');
fprintf('vitz-uid2\t');
printcor(vitz, mean([vitz_1_uid2 vitz_2_uid2 vitz_3_uid2 vitz_4_uid2 vitz_5_uid2 vitz_6_uid2])');
fprintf('vitz-uid3\t');
printcor(vitz, mean([vitz_1_uid3 vitz_2_uid3 vitz_3_uid3 vitz_4_uid3 vitz_5_uid3 vitz_6_uid3])');
