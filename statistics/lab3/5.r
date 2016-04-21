selection_mean = function(filename) 
{
  x = scan(filename)
  m = mean(x)
  d = sd(x)
}

selection_mean("sample.txt")
