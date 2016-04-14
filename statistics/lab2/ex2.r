tablou = read.csv("unemploy2012.csv", header = T, sep = ';')
rate = tablou[['rate']]
hist(rate, breaks = c(0, 4, 6, 8, 10, 14, 30), right = T, freq = T, col = 'red')