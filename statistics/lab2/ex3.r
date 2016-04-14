tablou = read.csv("life_expect.csv", header = T, sep = ',')
speranta_b = tablou[['male']] 
speranta_f = tablou[['female']]

intervale_b = 6
intervale_f = 6

hist(speranta_b, breaks = intervale_b, right = T, freq = T, col = 'green')
hist(speranta_f, breaks = intervale_f, right = T, freq = T, col = 'yellow')