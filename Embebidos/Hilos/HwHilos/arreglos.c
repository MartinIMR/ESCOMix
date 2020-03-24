/** @brief arreglos.c, este
 * programa contiene las funciones
 * para reservar memoria, llenar ese
 * espacio de memoria e imprimir 
 * su contenido.
 */
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

int *
reservar_memoria(int n)
{
  int * memoria;
  memoria = (int *) malloc(n*sizeof(int));
  if(memoria == NULL)
  {
    perror("Error en la asignacion de memoria\n Saliendo...\n");
    exit(EXIT_FAILURE);
  }
  return memoria;
}

void
llenar_arreglo(int * arreglo)
{
  /* Llena un arreglo con numeros aleatorios */
  register int i;
  /* srand(ID_PROCESO);  */
  for(i = 0; i < N; i++)
  {
    arreglo[i] = rand() % (MAX_RAND);
  }

}

void
imprimir_arreglo(int n, int * arreglo)
{
  register int i;
  for(i = 0; i < n; i++)
  {
     if(!(i%ESP ))
     {
       printf("\n");
     }
     printf("%3d ",arreglo[i]); 
  }
  printf("\n");
}
