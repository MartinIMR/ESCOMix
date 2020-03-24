
#!/bin/bash

echo "Hola mundo..."
echo "La suma de 4 + 3 = $[4+3]"
echo "Otra forma de sumar 4 + 3 = $(4+3)"

#Declarar variables
var1 = 3
var2 = 4

echo "La variable 1 es: $var1"
echo "La variable 2 es: $var2"

suma1=$var1+$var2

echo "La suma1 es: $suma1"

suma2=$[$var1+$var2]

echo "La suma2 es: $suma2"

suma3=$(($var1+$var2))

echo "La suma3 es: $suma3"

let suma4=var1+va2

echo "La suma4 es: $suma4"

echo "Dame el numero 1:"
read n1

echo "Dame el numero 2:"
read n2

let suma5 = n1 + n2

echo "n1 es:$n1"
echo "n2 es:$n2"
echo "La suma5 es:$suma5"
exit 0
