outliers1 = function(x)
{
  j = 0
  y = summary(x)
  q1 = y[2] # valoarea de pe pozitia a doua din sumarul celor 6 valori
  q3 = y[5]
  
  iqr = 0.3 - 0.1
  rez = vector()
 
  for (i in 1:length(x))
  {
    if (x[i] <= iqr - 1.5 * q1 | x[i] >= iqr + 1.5  * q3)
    {
      j = j + 1
      rez[j] = x[i]
      
    }
  }
  rez
}
  
x = scan("sample2.txt")
outliers1(x)
