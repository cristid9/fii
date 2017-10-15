Outline
=======
* Reminder linux
    - drepturi de access
    - comenzi (ls, chmod)
    - __setuid__ bit

Setup
=====
* instalat `libpcap2`

Probleme
=========
* Vazut daca nu au `SUID`-ul setat ce se intampla si de rulat.
    - `passwd` (__token manipulation error__)
    - `chmod` (__merge normal__)
    - `su` (__merge normal__)
    - `sudo` (__sudo must have setuid bit set__)
* _Cerinta initiala era sa copiem binarele de mai sus in /home-ul nostru_
    - Copiezi asa `whereis passwd; cp /usr/binpasswd .`
* Diferenta fata de drepturile normale de access:
    - `passwd` (`-rwxr-xr-x` vs `-rwsr-xr-x`)
    - `chmod` (`-rwxr-xr-x` vs `rwxr-xr-x`)
    - `su` (`-rwxr-xr-x` vs `-rwsr-xr-x`)
    - `sudo` (`-rwxr-xr-x` vs `-rwsr-xr-x`)
* Copiezi `/bin/zsh` in `/tmp`, il faci `SETUID` si ii dai `4755`. Si vezi daca ai privilegii de root din `zsh`-ul din `/tmp`
    - Da, da merge.

Dive deep
==========
    - `/etc/shadow`
