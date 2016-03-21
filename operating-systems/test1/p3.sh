#!/bin/bash

#######################################################################################################
# Enunt a treia problema:
#
# Sa se scrie un script bash care primeste ca parametri doua valori n si x, numere 
# pozitive, si calculeaza RECURSIV termenul Y[n] al sirului {Y[m]}m>=0, definit prin:
#   Y[0]=x-1, Y[1]=x+1 si Y[m] = (m-1) * Y[m-1] + (m-2) * Y[m-2],
# pentru orice m>=2.
# 
# La final se va afisa valoarea termenului cerut, Y[n].
#
# Valorile parametrilor n si x se vor da ca argumente la linia de comanda 
# sau se vor citi utilizand comanda read in caz contrar.
#
# NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
#######################################################################################################

if [ $# -eq 0 ]
then
    # deci n-a dat nimic
    read n
    read x
else
    n=$1
    x=$2
fi

# de forma compute_term n x
function compute_term ()
{
    # folosim variabile locale pentru a evita buguri subtile, 
    # in bash ele is by default globale...
    if [ $1 -eq 0 ]
    then
        local retval=$(( $2 - 1))
        return $retval
    fi

    if [ $1 -eq 1 ]
    then
        local retval=$(( $2 + 1 ))
        return $retval
    fi

    local mmin1=$(( $1 - 1))
    local mmin2=$(( $1 - 2 ))

    compute_term $mmin1 $2 
    local ym1=$?

    compute_term $mmin2 $2 
    local ym2=$?

    return $(( $mmin1 * $ym1 + $mmin2 * $ym2 ))
}

compute_term $n $x
echo $?
