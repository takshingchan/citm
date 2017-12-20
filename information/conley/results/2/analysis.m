%
%  analysis.m
%
%  Simulation Analysis
%
%  Copyright (C) 2006 Tak-Shing Chan
%

list = {'ncf-ftd' 'plain-ftd' 'cilibrasi'};
for i = 1 : length(list)
  % Load results
  results = load(list{i});

  % Test whether cor(conley, results) > 0
  fprintf('%s\n', list{i});
  fprintf('- Graduate  ');
  printcor([-1.65 -0.57 -0.90 0.12 -0.64 0 1.12 0.88 -0.24 -0.08 0.23 0.20 1.49 -0.29 0.69 -0.36]', results);
  fprintf('- Sophomore ');
  printcor([-1.51 -0.99 -1.09 0.14 -0.48 0.40 1.89 0.62 0.11 -0.78 0.09 0.45 0.93 -0.39 0.64 -0.02]', results);
  fprintf('- Non-major ');
  printcor([-1.17 -1.07 -0.95 0.05 -0.22 0.63 1.39 0.29 0.04 -0.53 0.15 0.65 0.62 -0.07 0.60 -0.39]', results);
end
