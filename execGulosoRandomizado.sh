#!/bin/bash

for y in ./*/*.dat_*;
do 
  echo "Teste: Algoritmo construtivo guloso randomizado e adaptativo " > ./SaidasGulosoRandomizado/saida_`basename $y .txt`
  echo "Data: " date >> ./SaidasGulosoRandomizado/Grasp_`basename $y .txt`
  echo "========================================================================" >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`
  echo "   RESULTADOS            " >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`
  echo "========================================================================" >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`

  for x in `seq 1 1 10`;
  do
    ./execGrupo2 "$y" ./ResultadoGulosoRandomizado/`basename $y `_"$x".dot 2 >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`
    echo "========================================================================" >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`
  done; 
  date >> ./SaidasGulosoRandomizado/saida_`basename $y .txt`

  echo "========================================================================" >>  ./SaidasGulosoRandomizado/saida_`basename $y .txt`

done;



