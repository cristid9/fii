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

9.
   Solutie:
      * `who | tr -s " " | cut -f4,1,3,5 -d" " | sort --key="3,3" | tail -15`

10. 
   Solutie:
      * `w -h | tr -s " " | cut -f1,8 -d" " | sort --key="1"` 

11.
   Solutie: 
      Aici m-am uitat la solutia profului, nu mai are sens sa o 
      mai postez pe a mea.

12.
   Solutie: 
      * ` who | cut -f1 -d" " | grep ^a  > a.txt`

13.
   Solutie:
      * `cut -f1,3 -d: /etc/passwd | egrep '* ([5-9][0-9][0-9][0-9])|([1-9][0-9][0-9][0-9][0-9]+)' | cut -f1 -d:
      `
