#!/bin/bash
for y in ./*/*.dat_*;
do 
  echo "Teste: Algoritmo construtivo guloso " > ./SaidasGuloso/saida_`basename $y .txt`
  echo "Data: " date >> ./SaidasGuloso/saida_`basename $y .txt`
  echo "========================================================================" >> ./SaidasGuloso/saida_`basename $y .txt`
  echo "   RESULTADOS            " >> ./SaidasGuloso/saida_`basename $y .txt`
  echo "========================================================================" >> ./SaidasGuloso/saida_`basename $y .txt`

  for x in `seq 1 1 10`;
  do
    ./execGrupo2 "$y" ./ResultadoGuloso/`basename $y `_"$x".dot 1 >> ./SaidasGuloso/saida_`basename $y .txt`
  echo "========================================================================" >>  ./SaidasGuloso/saida_`basename $y .txt`
  done; 
  date >> ./SaidasGuloso/saida_`basename $y .txt`

  echo "========================================================================" >>  ./SaidasGuloso/saida_`basename $y .txt`

done;

