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

3. > Să se scrie comanda care să sorteze descrescător liniile de text din fișierul 
   > /etc/passwd, iar rezultatul sortării să fie salvat în fișierul output.txt. 

   Solutie:
      * `sort -r /etc/passwd > output.txt`

4. > Să se scrie comanda care să sorteze crescător după UID liniile de text din 
   > fișierul /etc/passwd. 

   Solutie:
      * `sort /etc/passwd --numeric-sort --key=3 -t:
