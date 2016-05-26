# dreapta
func1 = function(alfa, n, succese, p0)
{
  p_prim = succese / n;
  z_score = (p_prim - p0) / sqrt(p0 * (1 - p0) / n);
  z_critic = qnorm(1 - alfa, 0, 1);
  
  vector = c(z_score, z_critic);
  
  if (z_score > z_critic)
  {
    print("respinsa ");
  } 
  else
  {
    print("acceptata");
  }  
  return(vector); 
}

# stanga
func2 = function(alfa, n, succese, p0)
{
  p_prim = succese / n;
  z_score = (p_prim - p0) / sqrt(p0 * (1 - p0) / n);
  z_critic = qnorm(alfa, 0, 1);
  
  vector = c(z_score, z_critic);
  
  if (z_score < z_critic)
  {
    print("respinsa ");
  } 
  else
  {
    print("acceptata");
  }
  
  return(vector); 
}

# simetric / bilatreral
func3 = function(alfa, n, succese, p0)
{
  p_prim = succese / n;
  z_score = (p_prim - p0) / sqrt(p0 * (1 - p0) / n);
  z_critic = -qnorm(alfa / 2, 0, 1);
  
  vector = c(z_score, z_critic);
  
  if (abs(z_score) < abs(z_critic))
  {
    print("acceptata ");
  } 
  else
  {
    print("respinsa");
  }
  
  return(vector); 
}

func1(0.01, 42, 17, 0.25);
func1(0.05, 128, 10, 0.025);
func2(0.05, 110, 15,0.1);
func1(0.05, 150, 20, 0.1);
