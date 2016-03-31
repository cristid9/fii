ex7 = function()
{
  fd = read.table('test.txt', header=TRUE)
  x = fd[['AA']]
  y = fd[['BB']]
  
  plot(x, y, type='l', col='red')
    
}

ex7()