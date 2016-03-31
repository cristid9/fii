poisson = function(landa, n)
{
  return (dpois(0:n, landa))
}

round(poisson(3, 20), 2)

