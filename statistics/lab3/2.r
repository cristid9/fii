normal_density1 = function(n, d)
{
  sigma = sqrt(d)
  t1 = seq(n - 2 * sigma, n + 2 * sigma, length = 2 * sigma)
  f = 1/sqrt(2 * pi * d) * exp(-((t1 - n)^2) / (2 * d)^2)
  plot(t1, f, type = "l", lwd = 1)
}

normal_density2 = function(n, d)
{
  sigma = sqrt(d)
  t2 = seq(n - 2 * sigma, n + 2 * sigma, length = 4 * sigma)
  f = 1/sqrt(2 * pi * d) * exp(-((t2 - n)^2) / (2 * d)^2)
  plot(t2, f, type = "l", lwd = 1)
}

normal_density3 = function(n, d)
{
  sigma = sqrt(d)
  t3 = seq(n - 2 * sigma, n + 2 * sigma, length = 6 * sigma)
  f = 1/sqrt(2 * pi * d) * exp(-((t3 - n)^2) / (2 * d)^2)
  plot(t3, f, type = "l", lwd = 1)
}

normal_density1(1, 10)
normal_density2(1, 10)
normal_density3(1, 10)