normal_density = function(n, d)
{
  t = seq(n, d, length = 400)
  f = 1/sqrt(2 * pi * d) * exp(-((t - n)^2) / (2 * d)^2)
  plot(t, f, type = "l", lwd = 1)
}

n = 6
d = 1

normal_density(n, d)