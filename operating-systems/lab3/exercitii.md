1. > Să se scrie comanda care calculează câte conturi de utilizatori 
   > (umani) există în sistem. 

   Solutie:
      * `grep -c "/bin/bash" /etc/passwd`
      * `grep "/bin/bash" /etc/passwd | wc -l`
      * `grep -v "/bin/bash" /etc/passwd | wc -l` (Suplimentar)

2. > Să se scrie comanda care afișează numărul total al utilizatorilor 
   > care sunt membri ai grupului studs. 

   Solutie:
      * `grep :202: /etc/passwd | wc -l`

3. 

    Solutie:
       * `finger | cut -f1,1 -d" "| sort -u > utilizatori-logati.txt`

4.

   Solutie:
      * `cut -f7 -d ":" /etc/passwd | sort -u`

5.

   Solutie:
      * `cut -f1 -d: /etc/passwd | grep ana | grep --invert-match -c ioana`


6.

   Solutie:
      * `ps  -U <nume> -pid="" | wc `

7. (mai revizuieste)

   Solutie:
      * `cut -f3,4,5 -d ":" --output-delimiter="->" /etc/passwd | cut -d"," -f1 | sort -n`

8.
   Solutie:
      * `who | grep <nume_user>| tr -s " " | cut -d " " -f3- | sort`
