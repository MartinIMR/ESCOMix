#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "procesamiento.h"
#include "arreglos.h"
#include "defs.h"

void * funHilo(void *);
pthread_mutex_t bloqueo; //Variable de condición para crear zona crítica
int * datos;

int 
main(void){
 register int nh;
 pthread_t tids[NUM_HILOS];
 int nhs[NUM_HILOS], *res_nh;
 datos = reservar_memoria(N);
 llenar_arreglo(datos);
 imprimir_arreglo(N,datos); 
 pthread_mutex_init(&bloqueo,NULL);
 for(nh = 0; nh < NUM_HILOS; nh++)
 {
   nhs[nh] = nh;
   pthread_create(&tids[nh], NULL, funHilo, (void *)&nhs[nh]);
 }
 for(nh = 0; nh < NUM_HILOS; nh++)
 {
  pthread_join(tids[nh], (void **)&res_nh);
  printf("Hilo %d terminado\n",*res_nh);
 }
 pthread_mutex_destroy(&bloqueo);
 return 0;
}

void * 
funHilo(void * arg)
{
 int nh = *((int *)arg);
 pthread_mutex_lock(&bloqueo);
 switch (nh)
 {
   case 0: 
     printf("El número mayor del arreglo es: %d\n", buscar_mayor(datos));           
   break;
   case 1: 
     printf("El número menor del arreglo es: %d\n", buscar_menor(datos));           
   break;
   case 2: 
     printf("El promedio del arreglo es: %d\n", promedio(datos));            
   break;
   case 3: 
     printf("El número más frecuente del arreglo es: %d\n", mas_frecuente(datos));
   break;
   case 4: 
     imprimir_arreglo(N,ordenamiento(datos));
   break;
   case 5:  
     imprimir_arreglo(MAX_RAND,histograma(datos));
   break;
   default: 
   perror("Error\n");
   exit(-1);
   break;
 }
 pthread_mutex_unlock(&bloqueo);
 pthread_exit(arg);
}

