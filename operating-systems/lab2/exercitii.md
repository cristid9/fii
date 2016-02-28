Exercitii pentru laboratorul 2
==============================

1. > Să se scrie comanda care să parcurgă recursiv directorul dat ca argument și 
   > să afișeze permisiunile tuturor fișierelor și subdirectoarelor întâlnite. 

   Solutie: 
      * `find . -exec stat --format="%n --> %a" {} \;`
      * `find . -printf "%f %M\n"`

2. > Să se scrie comanda ce afișează pentru toate fișierele găsite în directorul dat 
   > ca argument în linia de comandă, parcurs recursiv, fișiere ale căror nume încep 
   > sau se termină cu litera 'a', următoarele proprietăți: numele fișierului, data 
   > ultimei modificări și dimensiunea fișierului în Kbytes. 

   Solutie:
      * `find . \( -name "*a" -or -name "a*" \) -printf "% p %a %k"`
