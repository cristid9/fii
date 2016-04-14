outliers = function(x)
{
  j = 0 # nr valori aberante
  m = mean(x)
  s = sd(x)
  rez = vector()
  
  for (i in 1:length(x))
  {
    if (x[i] <= m - 2 * s | x[i] >= m + 2  * s)
    {
      rez[j] = x[i]
      j = j + 1
    }
  }
  rez
}

x = scan("sample1.txt")
summary(x)
quantile(x)
outliers(x)