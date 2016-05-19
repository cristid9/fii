func = function(alfa, pop_mean, sample_mean, n, sigma, case)
{
  z_score = (sample_mean - pop_mean) / (sigma / sqrt(n));

  if (case == 1)
  { # left
    critical_z = qnorm(alfa);
    if (z_score > critical_z)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se respinge H0");
    }
  }
  
  if (case == 2)
  { # middle
    critical_z = qnorm(1 - alfa / 2);
    if (abs(z_score)  < abs(critical_z))
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0");
    }
  }
  if (case == 3)  
  { # right
    critical_z = qnorm(1 - alfa);
    if (z_score < critical_z)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0")
    }
  }
  v = c(critical_z, z_score);
  
  return(v);
}

# z_test(alfa, pop_mean, sample_mean, n, sigma, case)

# I.2.
func(0.01, 90, 90, 49, 12, 1);
func(0.05, 90, 90, 49, 12, 1);

#I.3
func(0.01, 75, 36, 36, sqrt(17), 2);
func(0.05, 75, 36, 36, sqrt(17), 2);

# I.4
func(0.01, 21, 20.5, 100, 2.5, 1);
func(0.05, 21, 20.5, 100, 2.5, 1);

# I.5
func(0.05, 970, 1000, 100, sqrt(85), 1);
func(0.01, 970, 1000, 100, sqrt(85), 1);

# I.6
func(0.01, 22, 20, 16, 3, 2);
func(0.05, 22, 20, 16, 3, 2);




