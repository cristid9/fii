#!/bin/bash

#######################################################################################################
# Enunt a doua problema:
#
# Sa se scrie comanda inlantuita care scrie in fisierul not_studs.txt doar numele utilizatorilor care 
# nu apartin grupului studenti (id 202), in ordine invers alfabetica.
# 
# NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
#######################################################################################################

cat /etc/passwd | grep -v 202 | cut -f1 -d: | sort -r > not_studs.txt

