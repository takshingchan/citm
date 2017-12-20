%
%  printcor.m
%
%  Print Correlation
%
%  One-tailed test for positive correlation, with MDL statistics.
%
%  Copyright (C) 2006, 2017 Tak-Shing Chan
%

function printcor(x, y)

  if (nargin ~= 2)
    error('usage: printcor(x, y)');
  end

  % Print statistics
  n = length(x);
  r = corr(x, y);
  if (isnan(r))
    r = 0;
  end
  if (r > 0)
    cdf = betainc(1 - r ^ 2, .5 * n - 1, .5) / 2;
  else
    cdf = .5 + betainc(r ^ 2, .5, .5 * n - 1) / 2;
  end
  if (r >= sqrt(1 / n))
    gMDL = n * log(1 - r ^ 2) / 2 + log((n - 1) * (r ^ 2) / (1 - r ^ 2)) / 2 + log(n);
  else
    gMDL = n * log((n - 1) / n) / 2 + log(n) / 2;
  end

  fprintf('r(%.5g) = %.5g (p = %.5g), gMDL+ = %.5g\n', n - 2, r, cdf, gMDL);

end
