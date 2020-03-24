
#!/bin/bash

function opSuma
{

    let suma=$1+$2
    echo "La suma de $n1 + $n2 = $suma"
}

function opResta
{

    let resta=$1-$2
    echo "La resta de $n1 - $n2 = $resta"
}

function opMultiplicacion
{

    let multiplicacion=$1*$2
    echo "La multiplicacion de $n1 * $n2 = $multiplicacion"
}

function opDivision
{

    let division=$1/$2
    echo "La division de $n1 / $n2 = $division"
}

echo "1.- Suma"
echo "2.- Resta"
echo "3.- Multiplicacion"
echo "4.- Division"
read opcion

case $opcion in
    1)
    echo "Dame el numero 1:"
    read n1
    echo "Dame el numero 2:"
    read n2
    opSuma $n1 $n2
    ;;
    2) 
    echo "Dame el numero 1:"
    read n1
    echo "Dame el numero 2:"
    read n2
    opResta $n1 $n2
      ;;
    3)
    echo "Dame el numero 1:"
    read n1
    echo "Dame el numero 2:"
    read n2
    opMultiplicacion $n1 $n2
      ;;
    4)
    echo "Dame el numero 1:"
    read n1
    echo "Dame el numero 2:"
    read n2
    opDivision $n1 $n2
      ;;
    *)
    echo "Opcion incorrecta"
      ;;
esac
