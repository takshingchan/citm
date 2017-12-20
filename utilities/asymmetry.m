%
%  asymmetry.m
%
%  This function calculates the extent to which a distance matrix
%  departs from symmetry (see Johnson et al., 2002).
%
%  Copyright (C) 2007 Tak-Shing Chan
%

function a = asymmetry(d)

  if (nargin ~= 1)
    error('usage: a = asymmetry(d)');
  end

  % Calculate the extent of departure
  n = size(d, 1);
  b = 0;
  c = 0;
  for i = 1 : n
    for j = 1 : i - 1
       b = b + abs(d(i, j) - d(j, i));
       c = c + abs(d(i, j) + d(j, i));
    end
  end
  a = b / c;

end
