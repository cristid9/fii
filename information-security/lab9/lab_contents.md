Lab9
====

* generare de _nr random_ si _pseudo random_ 

```sh
cat /proc/sys/kernel/random/entropy_availl
head -c 16 /dev/random | hexdump
head -c 1600 /dev/urandom | hexdump
```
* moduri de operare

Exercitii
=========
* cripttat `ubuntu.bmp` cu `cbc` si `ecb`
