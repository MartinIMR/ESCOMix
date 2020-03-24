#!/bin/bash

function mostrar
{
  ls ./dire/gpi$1/oc
}

echo "Introduce una carpeta para ver su contenido"
read carp
mostrar $carp
exit 0
