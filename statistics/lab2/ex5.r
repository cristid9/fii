tablou = read.csv("life_expect.csv", header = T, sep = ',')
speranta_b = tablou[['male']] 
speranta_f = tablou[['female']]

media_b = mean(speranta_b)
media_f = mean(speranta_f)