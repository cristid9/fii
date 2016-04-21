zconfidence_interval = function(n, mn, alpha, sigma)
{
  critical_z = qnorm(1 - alpha/2, 0, 1)
  a = mn - critical_z * sigma / sqrt(n)
  b = mn + critical_z * sigma / sqrt(n)
  interval = c(a, b)
  
  return(interval)
}

# III.1 - 2
zconfidence_interval(25, 67.53, 0.1, 10)

# III.3
zconfidence_interval(50, 5, 0.05, 0.5)

# III.4
zconfidence_interval(100, 1280, 0.1, 140)

# III.5
zconfidence_interval(35, 60, 0.1, 5)
zconfidence_interval(35, 60, 0.05, 5)
zconfidence_interval(35, 60, 0.01, 5)

# III.6




