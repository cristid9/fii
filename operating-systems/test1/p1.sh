#!/bin/bash

#######################################################################################################
# Enunt prima problema:
#
# a) Cum se numeste comanda folosita pentru a schimba drepturile pe un fisier/director
#    si care este optiunea ce specifica, in cazul unui director, ca schimbarea sa fie recursiva si pentru
#    subdirectoare?
# b) Sa se scrie linia de comanda pentru a schimba drepturile pe directorul 'html' (si pentru subdirectoarele 
#    acestuia) astfel incat DOAR 'owner-ul' sa aiba drepturi de citire, scriere si executie.
#
# NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
#######################################################################################################

# Direct din man pageul pt. chmod: -R change files and directories recursively
a) chmod, si folosim optiunea -R, deci chmod -R <argumente>

# setam bitii de read, write si execute => r + x + w = 7
b) chmod -R 700 ~/html

