%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

% Load experimental data
chopin = load('chopin');
chopina = load('chopina');

% Load results
chopin_dist1 = trilvec('chopin-dist1');

% Test whether cor(chopin, chopin_dist1) > 0
fprintf('chopin-dist1\t');
printcor(chopin, chopin_dist1);

% Metric properties
chopin_dist1 = load('chopin-dist1');
chopin = trilmat('chopin');
fprintf('chopin-dist1\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(chopin_dist1), triangle(chopin_dist1));
fprintf('chopin\t\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(chopin), triangle(chopin));
fprintf('chopina\t\tasymmetry = %.5g, triangle = %.5g\n', asymmetry(chopina), triangle(chopina));
