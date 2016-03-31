density = function(n, p)
{
  return (barplot(dbinom(0:n, n, p), main="grafic", col="red"))
  
}
density(25, 0.3)
density(50, 0.7)