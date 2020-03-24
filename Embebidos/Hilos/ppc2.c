#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4
#define N 32

void * funHilo(void *);

int *A,promedio;
pthread_mutex_t bloqueo;

int *reservar_memoria(void);
void llenar_arreglo(int * datos);
void imprimir(int *datos);
void producto();

int main(){
 register int nh;
 pthread_t tids[NUM_HILOS];
 int nhs[NUM_HILOS], *res_nh;

  A = reservar_memoria();
  llenar_arreglo(A);
  imprimir(A);
  
  pthread_mutex_init(&bloqueo,NULL);
  promedio = 0;

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

promedio = promedio >> 5;
printf("El promedio es: %d\n", promedio);

free(A);
pthread_mutex_destroy(&bloqueo);
 return 0;
}

void * funHilo(void * arg)
{
 int nh = *((int *)arg);
 register int i=0;
 int suma_parcial = 0;
 //int tamBloque = N/NUM_HILOS;
 //int iniBloque = nh * tamBloque;
 //int finBloque = iniBloque + tamBloque;

 printf("Hilo %d ejecutado\n",nh);
 
 //for(i=iniBloque;i<finBloque;i++)
 for(i=nh;i<N;i+=NUM_HILOS)
    suma_parcial += A[i]:
 
 pthread_mutex_lock(&bloqueo);
 promedio += suma_parcial;
 pthread_mutex_unlock(&bloqueo);
 pthread_exit(arg);
}

int *reservar_memoria(void){
    int *mem;
    mem=(int *)malloc(N*sizeof(int));
    
    if (mem == NULL)
    {
        perror("ERROR DE ASIGNACION DE MEMORIA\n");
        exit(EXIT_FAILURE);
    }
    return mem;
}

void 
llenar_arreglo(int * datos){
    register int i;
    for (i = 0; i < N; i++)
        datos[i] = rand() % 256 ;
}

void 
imprimir(int *datos ){
    register int i;
    
    for(i=0;i<N;i++){
        if(!(i%16) )
            printf("\n");
        printf("%3d ",datos[i]);//para que salgan columnas del mismo tamaño
    }
    printf("\n");
}
