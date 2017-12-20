%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

% Dummy variable for point-biserial correlations
dummy = [0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1]';

% Load results
bach_dist1 = load('bach-dist1');
bach_dist2 = load('bach-dist2');
bach_dist3 = load('bach-dist3');

% Test whether cor(dummy, bach_dist1(:, 1) - bach_dist1(:, 2)) > 0
fprintf('bach-dist1\t');
printcor(dummy, bach_dist1(:, 1) - bach_dist1(:, 2));

% Test whether cor(dummy, bach_dist2(:, 1) - bach_dist2(:, 2)) > 0
fprintf('bach-dist2\t');
printcor(dummy, bach_dist2(:, 1) - bach_dist2(:, 2));

% Test whether cor(dummy, bach_dist3(:, 1) - bach_dist3(:, 2)) > 0
fprintf('bach-dist3\t');
printcor(dummy, bach_dist3(:, 1) - bach_dist3(:, 2));
