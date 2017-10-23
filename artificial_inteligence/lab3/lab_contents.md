Lab 3
=====

1. Reprezentarea starilor
```
(m, 1, 1, 1, 1)
```
2. Identificare stari speciale
`SI`, `SF`, `(m, 3, 3, 3)`
3. Validare de tranzitii
4. Strategii
  * Random
  * Hill Climbing
  * Backtracking
  * `A*`

```C
strategie_BKT(sc) {
	for i = 1 .. n
		for j = 1 .. m
			SN = tranzitie(SC, i, j)
			if valid(SN)
				SC = SN
				strategie_BKT(SC)
}
```


```C
strategie_HC() {
	while (!st_finala(SC)) {
		i = random(1..n)
		j = random(1..m)
		SN = tranzitie(SC, i, j)
		if (valid(SN)) {
			if (scor(SN) >= scor(SC)) {
				SC = SN
			}
		}
	}
}
```


|           |  Gas. sol    |    toate   | Optim
|----------:|-------------:|-----------:|--------
|    R      |   DA         |  NU        | NU
|           |              |            |
|	HC      |  NU`*`       |   NU       | NU
|           |              |            |
|   BKT     |  DA          |   DA       | NU`*`
|           |              |            |
|   `A*`    |   DA         |   DA`*`    | DA 


Punctare tema
=============
  * trebuie rulat de 100 de ori
  * trebuie facut si o statistica
  * vrea si lungimea drumului
  * vrea si nr mediu de stari tranzitate
  * durata medie, drum mediu, nr de iteratii
  * la fel si pentru hill climbing
  * asta este pe random si hill climbing
  * la bkt si `A*` nu trebuie afisata niciun fel de statistica
  * adunarea valorilor din vector ca functie de scor
  * de preferat sa nu se faca backtracking-ul in mod recursiv


