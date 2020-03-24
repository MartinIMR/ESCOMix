
#!/bin/bash


arreglo=(12 17 21 45 89)
function suma_acumulada
{
  let suma=0
  for i in 0 1 2 3 4 
  do
    let suma=suma+arreglo[i] 
  done
  echo "La suma acumulada es: $suma"
}

function suma_acumulada2
{
  let suma=0
  for i in ${arreglo[*]}
  do
    let suma=suma+i 
  done
  echo "La suma acumulada 2 es: $suma"
}

function suma_acumulada3
{
  let suma=0
  for (( i=0 ; $i < ${#arreglo[*]} ; i=$i+1 )) 
  do
    let suma=suma+arreglo[i]
  done
  echo "La suma acumulada 3 es: $suma"
}
cadena="Hola mundo"

echo "El elemento 0 del arreglo es: ${arreglo[0]}"
echo "El elemento 1 del arreglo es: ${arreglo[1]}"
echo "El elemento 3 del arreglo es: ${arreglo[3]}"

echo "TODOS los elementos del arreglo son:${arreglo[*]}"
echo "Numero de elementos del arreglo son:${#arreglo[*]}"
suma_acumulada
suma_acumulada2
suma_acumulada3
echo "La cadena es: $cadena"

exit 0
