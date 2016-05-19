func_f_test = function(alfa, file_name, side)
{
    x1 = read.table(file_name, header=TRUE)[['A']];
    x2 = read.table(file_name, header=TRUE)[['B']];
    
    n1 = length(x1);
    n2 = length(x2);
    
    s1 = sd(x1);
    s2 = sd(x2);
  
    f_score = (s1 ^ 2) / (s2 ^ 2);
    
    v = c(); 
    
    if (side == 1)
    {
      # dreapta
      critical_f = qf(1 - alfa, n1 - 1, n2 - 1);
      if (f_score > critical_f)
      {
        print("Ipoteza nula este respinsa");
      }
      else
      {
        print("Ipoteza nula este acceptata");
      }
      v = c(f_score, critical_f);
    }
    
    if (side == 2)
    {
      # simetrica
      critical_f_s = qf(alfa / 2, n1 - 1, n2 - 1);
      critical_f_d = qf(1 - alfa / 2, n1 - 1, n2 - 1);
      
      if (f_score < critical_f_s || f_score > critical_f_d)
      {
        print("Ipoteza nula este respinsa");
      }
      else
      {
        print("Ipoteza nula este acceptata");
      }
      v = c(f_score, critical_f_s, critical_f_d);
    }
    
    return (v);
}

# I.2
func_f_test(0.01, "program.txt", 2);
func_f_test(0.05, "program.txt", 2);

# I.3
func_f_test(0.05, "program2.txt", 1);
