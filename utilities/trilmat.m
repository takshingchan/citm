%
%  trilmat.m
%
%  Restores a distance matrix from its lower triangular part.
%
%  Copyright (C) 2007 Tak-Shing Chan
%

function d = trilmat(file)

  if (nargin ~= 1)
    error('usage: d = trilmat(file)');
  end

  X = load(file);
  n = (1 + sqrt(1 + 8 * length(X))) / 2;
  d = zeros(n, n);
  for i = 1 : n
    for j = 1 : i - 1
      d(i, j) = X((i - 1) * (i - 2) / 2 + j);
      d(j, i) = d(i, j);
    end
  end

end
