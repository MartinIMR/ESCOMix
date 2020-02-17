#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "hilos.h"
#include "defs.h"


int ** matrizA, ** matrizB, **matrizC;

int ** 
crearMatriz(int, int);

int ** 
imprimeMatriz(int **, int, int);

int 
main(void)
{
 int f1,c1,f2,c2,hilos;
 printf("Introduce las dimensiones de la primera matriz(NxM):"); 
 scanf("%dx%d",&f1,&c1);
 printf("Introduce las dimensiones de la segunda matriz(MxL):"); 
 scanf("%dx%d",&f2,&c2);
 if(c1 != f2)
 {
   printf("Numero columnas y filas no coinciden\n No se puede realizar la multiplicacion...\n");
   return 0;
 }
 printf("Introduce el numero de hilos:"); 
 scanf("%d",&hilos);
 if(hilos > f1)
 {
   printf("Numero de hilos demasiado grande...\n");
   return 0;
 }
 int filas_hilo,filas_padre,hilo;

 /* Filas para los hilos (filas / hilos) */
 filas_hilo = f1 / hilos;

 /* Filas para el padre (filas % hilos) */
 filas_padre = f1 % hilos;

 /* Creacion de las matrices */
 matrizA = crearMatriz(f1,c1); 
 matrizB = crearMatriz(f2,c2);
 matrizC = crearMatriz(f1,c2);
 /*
 printf("Matriz A generada:\n");
 imprimeMatriz(matrizA,f1,c1);
 printf("Matriz B generada:\n");
 imprimeMatriz(matrizB,f2,c2);
 */

 /* Arreglo para guardar los ids de los hilos*/
 pthread_t *tids;
 tids = (pthread_t *) malloc(sizeof(pthread_t) * hilos);
 
 for( hilo = 0 ; hilo < hilos; hilo++)
 {
  printf("Creando hilo %d\n",hilo);
  struct params * args = obtener_parametros(hilo,filas_hilo,c1,c2); 
  pthread_create(&tids[hilo],NULL,multiplica_matrices,(void *)args);
 }
 for( hilo = 0; hilo < hilos; hilo++)
 {
  pthread_join(tids[hilo],NULL);
 }
 printf("Matriz C calculada:\n");
 imprimeMatriz(matrizC,f1,c2);
 return 0;
}


int ** 
crearMatriz(int filas, int columnas)
{
 int ** matriz, i, j;
 matriz = (int **) malloc( sizeof(int *) * filas);
 if( matriz == NULL )
 {
   exit(-1); 
 }
 time_t t;
 srand((unsigned) time(&t));
 for( i = 0; i < filas; i++)
 {
   matriz[i] = (int *) malloc( sizeof(int) * columnas );
   if( matriz[i] == NULL )
   {
     exit(-1); 
   }
    for( j = 0; j < columnas; j++)
    {
      matriz[i][j] = rand() % MAX;
    }
 }
 return matriz;
}

int ** 
imprimeMatriz(int ** matriz, int filas, int columnas)
{
 register int i,j;
 for( i = 0; i < filas; i++)
 {
    for( j = 0; j < columnas; j++)
    {
      printf("%d ",matriz[i][j]);
    }
    printf("\n");
 }
 printf("\n");
}
