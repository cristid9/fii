Turnurile din Hanoi
===================

1. Modalitate de reprezentat starile problemei
```
(n-tije, m-piese)
sc(3, 3, 3, 1)

         =
        ===
====   =====
```

2. Identificarea starilor speciale
```
SI(1, 1, 1, 1)
                   Stare intermediara
SF(3, 3, 3, 3)
```

3. Tranzitii

```
tranzitie(SC, x, y)
{
	SC[x] = y;
	return SC;
}

 ===      
===== --> =====  ===
3211  --> 3221
 
 ==            ==  
==== --> ____ ====

3311 --> 3312


st_initiala()
{
	return SC(1, 1, 1, 1);
}

st_finala(SC)
{
	for (i = 1..n) 
	{
		if SC[i] =/= SF(i)
			return FALSE
	}
	return TRUE
}

```
4. Strategii
   * Random
   ```
   strategie(SC)
   {
   	while (!st_finala(SC))
        {
            y = rand(1..n)
            x = rand(1..m)
            SA = tranzitii(SC, x, y)
            if validare(SC, SA, x)
                SC = SA
                pass++
        }
   }
   ```
   * random optimizat
       - eliminare bucla
       - stari interne

Indicatie
=========
* gandit la o functie de scor pentru hill climbing
* Sa implementam 3/4 startegii: backtracking, hill climbing, A*, random 
