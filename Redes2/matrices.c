#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int ** 
crearMatriz(int, int);

int 
main(void)
{
 int f1,c1,f2,c2;
 printf("Introduce las dimensiones de la primera matriz(NxM):"); 
 scanf("%dx%d",&f1,&c1);
 printf("Introduce las dimensiones de la segunda matriz(MxL):"); 
 scanf("%dx%d",&f2,&c2);
 int ** m1, ** m2, i, j;
 m1 = crearMatriz(f1,c1); 
 m2 = crearMatriz(f2,c2);
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
