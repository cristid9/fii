pmax = function(n, p)
{
  return (max(dbinom(0:n, n, p)))
}

pmax(30, 0.3)