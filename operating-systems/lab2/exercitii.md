Exercitii pentru laboratorul 2
==============================

1. > Să se scrie comanda care să parcurgă recursiv directorul dat ca argument și 
   > să afișeze permisiunile tuturor fișierelor și subdirectoarelor întâlnite. 

   Solutie: 
      * `find . -exec stat --format="%n --> %a" {} \;`
      * `find . -printf "%f %M\n"`
