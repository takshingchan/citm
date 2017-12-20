%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2007 Tak-Shing Chan
%

% Load experimental data
eerola01 = trilvec('eerola01');
eerola07 = trilvec('eerola07');

% Load results
eerola01_dist1 = trilvec('eerola01-dist1');
eerola01_dist2 = trilvec('eerola01-dist2');
eerola01_dist3 = trilvec('eerola01-dist3');
eerola07_dist1 = trilvec('eerola07-dist1');
eerola07_dist2 = trilvec('eerola07-dist2');
eerola07_dist3 = trilvec('eerola07-dist3');

% Test whether cor(eerola01, eerola01_dist1) > 0
fprintf('eerola01-dist1\t');
printcor(eerola01, eerola01_dist1);

% Test whether cor(eerola01, eerola01_dist2) > 0
fprintf('eerola01-dist2\t');
printcor(eerola01, eerola01_dist2);

% Test whether cor(eerola01, eerola01_dist3) > 0
fprintf('eerola01-dist3\t');
printcor(eerola01, eerola01_dist3);

% Test whether cor(eerola07, eerola07_dist1) > 0
fprintf('eerola07-dist1\t');
printcor(eerola07, eerola07_dist1);

% Test whether cor(eerola07, eerola07_dist2) > 0
fprintf('eerola07-dist2\t');
printcor(eerola07, eerola07_dist2);

% Test whether cor(eerola07, eerola07_dist3) > 0
fprintf('eerola07-dist3\t');
printcor(eerola07, eerola07_dist3);

% Metric properties
eerola01 = load('eerola01');
eerola07 = load('eerola07');
eerola01_dist1 = load('eerola01-dist1');
eerola01_dist2 = load('eerola01-dist2');
eerola01_dist3 = load('eerola01-dist3');
eerola07_dist1 = load('eerola07-dist1');
eerola07_dist2 = load('eerola07-dist2');
eerola07_dist3 = load('eerola07-dist3');
fprintf('eerola01\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola01), triangle(eerola01));
fprintf('eerola07\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola07), triangle(eerola07));
fprintf('eerola01-dist1\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola01_dist1), triangle(eerola01_dist1));
fprintf('eerola01-dist2\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola01_dist2), triangle(eerola01_dist2));
fprintf('eerola01-dist3\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola01_dist3), triangle(eerola01_dist3));
fprintf('eerola07-dist1\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola07_dist1), triangle(eerola07_dist1));
fprintf('eerola07-dist2\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola07_dist2), triangle(eerola07_dist2));
fprintf('eerola07-dist3\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(eerola07_dist3), triangle(eerola07_dist3));
