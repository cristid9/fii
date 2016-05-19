func_f_test_helper = function(alfa, n1, n2, s1, s2, side)
{
  f_score = (s1 ^ 2) / (s2 ^ 2) 
  df = 1  # tmp value
  combined_s = 1  # tmp value
  
  if (side == 1)
  {
    # as. dreapta
    critical_f = qf(1 - alfa, n1 - 1, n2 - 1) 
    
    if (f_score < critical_f)
    {
      df = min(n1 - 1, n2 - 1) 
      combined_s = sqrt(s1 ^ 2 / n1 + s2 ^ 2 / n2) 
    }
    else
    {
      df = n1 + n2 - 2 
      combined_s = sqrt(((n1 - 1) * s1 ^ 2 + (n2 - 1)* s2 ^ 2) / df) * sqrt(1 / n1 + 1 / n2) 
    }
  }
  
  if (side == 2)
  {
    critical_f_s = qf(alfa / 2, n1 - 1, n2 - 1) 
    critical_f_d = qf(1 - alfa / 2, n1 - 1, n2 - 1) 
    
    if (f_score < critical_f_s || f_score > critical_f_d)
    {
      df = min(n1 - 1, n2 - 1) 
      combined_s = sqrt(s1 ^ 2 / n1 + s2 ^ 2 / n2) 
    }
    else
    {
      df = n1 + n2 - 2 
      combined_s = sqrt(((n1 - 1) * s1 ^ 2 + (n2 - 1)* s2 ^ 2) / df) * sqrt(1 / n1 + 1 / n2) 
    }
  }
  
  v = c(df, combined_s) 
  
  return(v) 
}

# func_f_test_helper(alfa, n1, n2, s1, s2, score)
func_t_test = function(alfa, m0, filename, side)
{
  x1 = read.table(filename, header=TRUE)[['A']] 
  x2 = read.table(filename, header=TRUE)[['B']] 
  
  n1 = length(x1) 
  n2 = length(x2) 
  
  s1 = sd(x1) 
  s2 = sd(x2) 
  
  sample_mean1 = mean(x1) 
  sample_mean2 = mean(x2) 
  
  v = 1  # tmp value
  if (side == 2)
  {
    v = func_f_test_helper(alfa, n1, n2, s1, s2, 2) 
  }
  else
  {
    v = func_f_test_helper(alfa, n1, n2, s1, s2, 1) 
  }
  
  df = v[0] 
  combined_s = v[1] 
  t_score = (sample_mean1 - sample_mean2 - m0) / combined_s 
  critical_t = 1  # tmp value
  
  if (side == 1)
  {
    # left
    critical_t = qt(2 * alfa, df) 
    
    if (t_score < critical_t)
    {
      print("Ipoteza nula este respinsa") 
    }
    else
    {
      print("Ipoteza nula este acceptata") 
    }
  }
  
  if (side == 2)
  {
    # middle
    critical_t = qt(1 - alfa / 2, df) 

    if (abs(t_score) > abs(critical_t))
    {
      print("Ipoteza nula este respinsa") 
    }
    else
    {
      print("Ipoteza nula este acceptata") 
    }
    
  }
  
  if (side == 3)
  {
    # right
    critical_t = qt(1 - alfa, df)
    
    # to avoid error
    if (length(critical_t) == 0)
    {
      critical_t = 0;
    }
    
    if ((t_score > critical_t))
    {
      print("Ipoteza nula este respinsa") 

    }
    else
    {
      print("Ipoteza nula este acceptata")
    }
  }
  
  v2 = c(t_score, critical_t)
  
  return(v2)
}

# func_t_test(alfa, m0, filename, side)

# III.2
func_t_test(0.01, 0, "program.txt", 2) 
func_t_test(0.05, 0, "program.txt", 2) 

# III.3
func_t_test(0.01, 0, "program2.txt", 3) 



