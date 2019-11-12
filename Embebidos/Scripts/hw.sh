#!/bin/bash

function abrir_puertos() {
param=($*)
#¿param=("$*")?
for (( i=0 ; $i<${#param[*]} ; i=$i+1 ))
do
 echo "Abriendo Puerto $i:BCM${param[$i]}..."
 sudo echo ${param[$i]} > /sys/class/gpio/export 
 sudo echo "out" > /sys/class/gpio/gpio${param[$i]}/direction
done
}

function serie() {
param=($*)
for i in ${param[*]};
do
        sudo echo "1" > /sys/class/gpio/gpio$i/value
        sleep 2
        sudo echo "0" > /sys/class/gpio/gpio$i/value
        sleep 2
done
}

function boleta() {
param=($*)
echo "Introduce el numero de boleta"
read digitos
for (( i=0 ; i<${#digitos} ; i=$i+1));
do
  #echo "Digito en posicion $i:${digitos:$i:1}"
  digito=${digitos:$i:1}
  lista=$(secuencia $digito)
  #echo "Para el digito $digito la secuencia es ${lista[*]}"
  for j in ${lista[*]}; #Encender los leds
  do 
    echo "Encendiendo puerto BCM$j..."
    sudo echo "1" > /sys/class/gpio/gpio$j/value
  done
  sleep 2 #Esperar dos segundos antes de apagar
  for j in ${lista[*]}; #Apagar los leds
  do 
    echo "Apagando puerto BCM$j..."
    sudo echo "0" > /sys/class/gpio/gpio$j/value
  done
done
}

function secuencia() {
 digito=$1
 # arreglo de digitos(A B C D E F G)=>(5 6 17 22 24 25 27)
 # A => 5
 # B => 6
 # C => 17
 # D => 22
 # E => 24 
 # F => 25
 # G => 27
 case $digito in
 0)
  encendidos=( 5 6 17 22 23 24 )
  ;;
 1)
  encendidos=( 6 17 )
  ;;
 2)
  encendidos=( 5 6 25 23 22 )
  ;;
 3)
  encendidos=( 5 6 17 22 25 )
  ;;
 4)
  encendidos=( 6 17 24 25 )
  ;;
 5)
  encendidos=( 5 17 22 24 25 )
  ;;
 6)
  encendidos=( 5 17 22 23 24 25 )
  ;;
 7)
  encendidos=( 5 6 17 25 )
  ;;
 8)
  encendidos=( 5 6 17 22 23 24 25 )
  ;;
 9)
  encendidos=( 5 6 17 22 24 25 )
  ;;
 *)
  echo "No es un digito numerico..."
  ;;
 esac
 echo ${encendidos[*]}
}

function cerrar_puertos() {
param=($*)
#¿param=("$*")?
for (( i=0 ; $i<${#param[*]} ; i=$i+1 ))
do
 echo "Cerrando Puerto $i:BCM${param[$i]}..."
 sudo echo ${param[$i]} > /sys/class/gpio/unexport 
done
}

puertos=(5 6 17 22 23 24 25 27)
echo "Escoja una opcion:"
echo "1.-Ver serie"
echo "2.-Visualizar boleta"
read opcion
abrir_puertos ${puertos[*]}
  case $opcion in
   1)
    echo "Serie"
    serie ${puertos[*]}
    ;;
   2)
    echo "Boleta"
    boleta ${puertos[*]}
    ;;
   *)
    echo "Opcion invalida..."
    ;; 
   esac
cerrar_puertos ${puertos[*]}
exit 0
