%
%  trilvec.m
%
%  Extracts the lower triangular part of a distance matrix.
%
%  Copyright (C) 2007 Tak-Shing Chan
%

function X = trilvec(file)

  if (nargin ~= 1)
    error('usage: X = trilvec(file)');
  end

  d = load(file);
  if (size(d, 1) ~= size(d, 2))
    error('trilvec: file must contain a square matrix');
  end

  X = [];
  for i = 1 : size(d, 1)
    X = [X; d(i, 1 : i - 1)'];
  end

end
