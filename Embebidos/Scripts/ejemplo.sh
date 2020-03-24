#!/bin/bash

lista=(1 2 5 6 7)

for i in ${lista[*]}
do 
  echo "Numero i:$i"
done
echo "El otro for"
for i in 0 1 2 3 4
do
  echo "Numero en $i:${lista[$i]}"
done
echo "El otro for"
for (( i=0 ; $i<8 ; i=$i+1 ))
do 
  echo "La posicion $i:${lista[$i]}"
  echo '$i' >> ./datos.txt
done

exit 0
