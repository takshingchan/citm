%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2005, 2017 Tak-Shing Chan
%

% Load results
one_f = load('1-f');
white = load('white');
brown = load('brown');

% Test whether 1/f > white
[h, pval, ci, stats] = ttest2(one_f, white, 'tail', 'right', 'vartype', 'unequal');
fprintf('white\t\tt(%.5g) = %.5g (p = %.5g)\n', stats.df, stats.tstat, pval);

% Test whether 1/f > brown
[h, pval, ci, stats] = ttest2(one_f, brown, 'tail', 'right', 'vartype', 'unequal');
fprintf('brown\t\tt(%.5g) = %.5g (p = %.5g)\n', stats.df, stats.tstat, pval);
