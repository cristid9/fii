Commands
========
    * `find <path> [optiuni]`
    * `sort`

Snippets
========
    * `find . -name "a*" -or -name "*a"` 
    * `find . \( -name "a*" -or -name "*a" \)`
    * `find . \( -name "a*" -or -name "*a" \) -printf "%f %n %k\n"`
    * `sort /etc/passwd`
    * `sort -r /etc/passwd`
    * `sort -r /etc/passwd > studenti_alfabetic`
    * `sort -k3 -t: /etc/passwd`

Concepte
========
    * recapitulare drepturi de acces (rwx - owner, rwx - group, rwx - o).
    * cum citim man pages (foloseste `/`  pentru cautare).
    * diferenta dintre argumentele cu un dash si cele cu 2 dash-uri.
    * "escaparea" wildcardurilor in bash. (in cazul de fata `;` si `{` & `} `la find ).
    * wildcarduri in shell (pe exemplul cu `find`).
        - `*`
        - `+`
    * expresii in find (`-or`).
    * important la find:
        - `exec`
        - `printf`
        - _combinarea expresiilor_

    * `I/O` redirect:
        - `> <file.txt>`
        - `>> <file.txt>` (face append)
    
Activitate
==========
    * rezolvarea exercitiilor de laborator


