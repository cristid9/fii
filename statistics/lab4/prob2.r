# 1
t_conf_interval = function(alfa, sample_mean, n, s)
{
  se = s / sqrt(n);
  critical_t = qt(1 - alfa / 2, n - 1);
  a = sample_mean - critical_t * s / sqrt(n);
  b = sample_mean + critical_t * s / sqrt(n);
  interval = c(a, b);
  
  return(interval);
}

# 2
t_conf_interval(0.1, 44.65, 196, 2.25);

# 3.a
t_conf_interval(0.1, 12, 49, 1.75);
t_conf_interval(0.5, 12, 49, 1.75);

# 3.b
t_conf_interval(0.5, 13.5, 49, 1.35);

# 4
t_conf_interval_file = function(file_name, alfa)
{
  f = scan(file_name);
  n = length(f);
  s = sd(f);
  sample_mean = mean(f);
  
  se = s / sqrt(n);
  critical_t = qt(1 - alfa / 2, n - 1);
  a = sample_mean - critical_t * s / sqrt(n);
  b = sample_mean + critical_t * s / sqrt(n);
  interval = c(a, b);
  
  return(interval);
}

# 5
t_conf_interval_file("esantion.txt", 0.1);
t_conf_interval_file("esantion.txt", 0.05);
t_conf_interval_file("esantion.txt", 0.01);


