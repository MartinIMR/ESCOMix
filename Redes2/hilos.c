#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"

void *
multiplica_matrices(void * args)
{
    struct params * datos = (struct params *) args;
    extern int ** matrizA, ** matrizB, ** matrizC, num_hilos;
    int i,j,k;
    int final = datos -> fin;
    int suma; 
    for( i = datos -> inicio; i < final; i++)
    {
       for( j = 0; j < datos -> columnas_m2; j++ )
       {
          suma = 0;
          for( k = 0; k < datos -> columnas_m1; k++ )
	  {
            suma += matrizA[i][k] * matrizB[k][j];
	  }
          matrizC[i][j] = suma; 
       }
    }
    free(datos);
    pthread_exit(0);
}

struct params *
obtener_parametros(int hilo,int filas_hijo,int col_m1,int col_m2)
{
  struct params * args;
  args = (struct params *) malloc(sizeof(struct params));
  if(args == NULL)
  {
   exit(-1);
  }
  args->inicio = hilo * filas_hijo;
  args->fin = (args->inicio) + filas_hijo;
  args->columnas_m1 = col_m1; 
  args->columnas_m2 = col_m2; 
  return args;
}

