#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"

void *
multiplica_matrices(void * args)
{
    struct params * datos = (struct params *) args;
    extern int ** matrizA, ** matrizB, ** matrizC, num_hilos;
    printf("Datos del hilo:\n");
    register int i = datos -> inicio;
    int final = datos -> fin;
    free(datos);
    printf("Inicio:%d y Fin:%d\n",i,final);
    /*
    for( i = datos -> inicio; i < datos->fin; i++)
    {
        resultado[i] = senial[i] * hamming[i];
    }
    */
    pthread_exit(0);
}

struct params *
obtener_rango(int hilo,int filas_hijo)
{
  struct params * args;
  args = (struct params *) malloc(sizeof(struct params));
  if(args == NULL)
  {
   exit(-1);
  }
  args->inicio = hilo * filas_hijo;
  args->fin = (args->inicio) + filas_hijo;
  return args;
}

