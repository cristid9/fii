zconfidence_interval = function(filename, alpha)
{
  file = scan(filename)
  
  n = length(file)
  mn = mean(file)
  sigma = sd(file)
  
  critical_z = qnorm(1 - alpha/2, 0, 1)
  a = mn - critical_z * sigma / sqrt(n)
  b = mn + critical_z * sigma / sqrt(n)
  interval = c(a, b)
  
  return(interval)
}

zconfidence_interval("sample.txt", 0.05)
