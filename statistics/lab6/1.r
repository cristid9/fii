func_z_test = function(alfa, m0, sample_mean1, sample_mean2, sigma1, sigma2, n1, n2, side)
{
  combined_sigma = sqrt((sigma1 ^ 2) / n1 + (sigma2 ^ 2) /n2);
  critical_z = 1; # temp value
  z_score = (sample_mean1 - sample_mean2 - m0) / combined_sigma;
  
  if (side == 1)
  {
    # left
    critical_z = qnorm(alfa, 0, 1);
    if (z_score < critical_z)
    {
      print("Ipoteza nula este respinsa");
    }
    else
    {
      print("Ipoteza nula este acceptata");
    }
    
  }
  
  if (side == 2)
  {
    # simetric
    critical_z = qnorm(1 - alfa / 2, 0, 1);
    
    if (abs(z_score) > abs(critical_z))
    {
      print("Ipoteza nula este respinsa");
    }
    else
    {
      print("Ipoteza nula este acceptata");
    }
            
  }
  
  if (side == 3)
  {
    # right
    critical_z = qnorm(1 - alfa, 0, 1);
  
    if (z_score > critical_z)
    {
      print("Ipoteza nula este respinsa");
    }
    else
    {
      print("Ipoteza nula este acceptata");
    }
    
    
  }
  
  v = c(z_score, critical_z);
  return (v);
}
# func_z_test(alfa, m0, sample_mean1, sample_mean2, sigma1, sigma2, n1, n2, side);

# I.2
func_z_test(0.01, 0, 160, 155, 3.24, 2.25, 80, 70, 2);

# I.3
func_z_test(0.01, 0, 22.8, 23.3, 1.3, 1.9, 100, 100, 2);

# I.4
func_z_test(0.01, 0, 3, 3.5, 0.6, 0.4, 100, 100, 3);
func_z_test(0.05, 0, 3, 3.5, 0.6, 0.4, 100, 100, 3);

# I.5
func_z_test(0.01, 0, 15, 14.5, 0.75, 0.78, 155, 150, 2);
func_z_test(0.05, 0, 15, 14.5, 0.75, 0.78, 155, 150, 2);

