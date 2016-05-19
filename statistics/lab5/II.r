func1 = function(alfa, pop_mean, sample_mean, n, s, case)
{
  se = s / sqrt(n);
  t_score = (sample_mean - pop_mean) / se;
  critical_z = 1; # tmp value
  
  if (case == 1)
  {
    # left  
    critical_t = qt(alfa, n - 1)
    if (t_score > critical_t)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se respinge H0");
    }
  }
    
  if (case == 2)
  {
    # middle
    critical_t = qt(1 - alfa / 2, n - 1)
    if (abs(t_score) < abs(critical_t))
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0");
    }
    
  }
  
  if (case == 3)
  {
    # right
    critical_t = qt(1 - alfa, n - 1)
    if (t_score < critical_t)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0")
    }
  }
  
  v = c(critical_z, t_score);
  
  return (v);
}

func2 = function(alfa, fl, pop_mean, case)
{
  x = scan(fl);
  n = length(x);
  sample_mean = mean(x);
  s = sd(x);
  se = s / sqrt(n);
  t_score = (sample_mean - pop_mean) / se;
  critical_z = 1; # test
  
    
  if (case == 1)
  {
    # left  
    critical_t = qt(alfa, n - 1)
    if (t_score > critical_t)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se respinge H0");
    }
  }
  
  if (case == 2)
  {
    # middle
    critical_t = qt(1 - alfa / 2, n - 1)
    if (abs(t_score) < abs(critical_t))
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0");
    }
    
  }
  
  if (case == 3)
  {
    # right
    critical_t = qt(1 - alfa, n - 1)
    if (t_score < critical_t)
    {
      cat("Se accepta H0");
    }
    else
    {
      cat("Se resp H0")
    }
  }
  
  v = c(critical_z, t_score);
  
  return (v);
  
}

# II.2
func2(0.01, "esantion.txt", 34, 2);

# II.3
func1(0.01, 11.4, 11.9, 100, 0.25, 3);
func1(0.05, 11.4, 11.9, 100, 0.25, 3);

# II.4
func2 (0.01, "history.txt", 80, 2);
func2 (0.05, "history.txt", 80, 2);

# II.5
func1(0.01, 49, 52, 64, sqrt(89.5), 2);
func1(0.01, 49, 52, 64, sqrt(89.5), 1);
func1(0.01, 49, 52, 64, sqrt(89.5), 3);

# II.6
func1(0.05, 30, 29, 40, sqrt(5), 1);
  


  

  
  
  
  

