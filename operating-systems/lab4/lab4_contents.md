Concepte
========
   * liniil e shebang `#!/bin/bash`
   * numarul de argumente `$#`
   * `$@`
   * valoarea rturnata de o functie `$?`
   * variabilele se acceaseaza folosing sintaxa `$nume_variabila`
   * back-tickurile folosite la exepresii
   * pentru numere intregi putem folosi `let` sau `expr`:
      - `let $s=$s+1`
      - `s=`expr s + 1``
      - sau cu `declare -i s; s=$s + 1`
   * Structuri de control:
      - `if`
      ```shell
        if instructiune
        then
            instructiune
        else
            instructiune
        fi

      ```
      - instructiunea `test`:
      ```shell
        test $n -gt 5
                -lt
                -le
                -eq
      ```
      - operatorul de `[  ]`:
      ```shell
        [ $n -gt 5 ]
      ```
      - `for`:
      ```shell
        for variabila in lista
        do
            comenzi
        done
        
        for ((instructiune1; instructiune2; instructiune4))
        do
            comenzi
        done
      ```
      - comanda `seq <start> <stop> <step>`:
         * `seq 1 5`
      - `while`:
      ```shell
        while conditie
        do
           ...
        done
      ```
      - `until`:
      ```shell
        until conditie
        do
           ...
        done
      ```
      - functii:
      ```shell
        function numef()
        {
            
        }
      ```
      * Rezultatul returnat de o functie este retinut intr-un pipe,
        deci exista limita destul de mica pt `$?`.
Snippets
========


Advices
=======
   * Invata sa te misti rapid in _vim_
