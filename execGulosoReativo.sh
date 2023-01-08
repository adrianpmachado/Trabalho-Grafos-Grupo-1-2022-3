#!/bin/bash

for y in ./*/*.dat_*;
do 
    echo "Teste: Algoritmo construtivo guloso randomizado reativo " > ./SaidasGulosoReativo/saida_`basename $y .txt`
    echo "Data: " date >> ./SaidasGulosoReativo/saida_`basename $y .txt`
    echo "========================================================================" >> ./SaidasGulosoReativo/saida_`basename $y .txt`
    echo "   RESULTADOS            " >> ./SaidasGulosoReativo/saida_`basename $y .txt`
    echo "========================================================================" >> ./SaidasGulosoReativo/saida_`basename $y .txt`

    for x in `seq 1 1 10`;
    do
      ./execGrupo2 "$y" ./ResultadoGulosoReativo/`basename $y `_"$x".dot 3 >> ./SaidasGulosoReativo/saida_`basename $y .txt`
      echo "========================================================================" >>  ./SaidasGulosoReativo/saida_`basename $y .txt`
    done; 
    date >> ./SaidasGulosoReativo/saida_`basename $y .txt`
    echo "========================================================================" >>  ./SaidasGulosoReativo/saida_`basename $y .txt`  
    

done;

