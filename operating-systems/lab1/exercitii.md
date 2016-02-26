Exercitii de laborator
======================

1.  > Să se scrie comanda care afișează numele de cont și UID-urile tuturor utilizatorilor sistemului. 
    Solutie: `cut -f1,4 -d: --output-delimiter=" " /etc/passwd`

2. > Să se scrie comanda care selectează din fișierul /etc/passwd doar informațiile despre un utilizator
   > specificat ca argument al comenzii. 
    Solutie: `grep cristi /etc/passwd`

3. > Să se scrie comanda care afișează numele și GID-urile tuturor grupurilor de utilizatori ai sistemului.
   > Suplimentar: înlocuiți ":" cu " - " în rezultatele afișate de comandă. 
    Solutie: `cut -f1,3 -d: --output-delimiter="-" /etc/group`

4. > Să se scrie comanda care afișează lista tuturor utilizatorilor care sunt membri ai grupului studs. 
    Solutie: `grep -e "grep -m1 "users" /etc/group | cut -f3 -d:" /etc/passwd` 
    (probabil m-am cam complicat)
