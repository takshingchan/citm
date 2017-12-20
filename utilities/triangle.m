%
%  triangle.m
%
%  This function calculates the extent to which a distance matrix
%  violates the triangle inequality (see Johnson et al., 2002).
%
%  Copyright (C) 2007 Tak-Shing Chan
%

function t = triangle(d)

  if (nargin ~= 1)
    error('usage: t = triangle(d)');
  end

  % Calculate the extent of violation
  n = size(d, 1);
  t = 0;
  for i = 1 : n
    for j = 1 : n
      if (i ~= j)
        e = d(i, j);
        for k = 1 : n
          e = min(e, d(i, k) + d(k, j));
        end
        t = t + e / d(i, j);
      end
    end
  end
  t = 1 - t / n / (n - 1);

end
