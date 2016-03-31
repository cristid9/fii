# a)
log_nat = function()
{
  x = c(1, 2, 3, 4, 5)
  v = log(x)
  return (v)
}

log_nat()


# b)
minim_max = function()
{
  x = c(1:5)
  v = (x - max(x)) / min(x)
  return (v)  
}

minim_max()
