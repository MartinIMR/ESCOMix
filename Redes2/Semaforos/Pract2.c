#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

void * productor(void *);
void * consumidor(void *);


char letras[4], numeros[4];
int producciones = 10000;
sem_t pro, con, semplet[4], semclet[4], sempnum[4], semcnum[4];


int 
main(void)
{
  pthread_t tids[10];
  char proids[10];
  /* Creacion e inicializacion de los semaforos */
  sem_init(&pro, 0, 4);
  sem_init(&con, 0, 4);
  char i;
  for(i = 0; i < 4; i++)
  {

    /* Semaforos para produccion */
    sem_init(&semplet[i], 0, 1);
    sem_init(&sempnum[i], 0, 1);

    /* Semaforos para consumo */
    sem_init(&semclet[i], 0, 0);
    sem_init(&semcnum[i], 0, 0);

  }
  /* Creacion de los hilos */
  for(i = 0; i < 10; i++)
  {
     proids[i] = i;
     if( i < 5 )
     {
       pthread_create(&tids[i],NULL,productor,(void *)(proids + i));
     }else
     {
       pthread_create(&tids[i],NULL,consumidor,(void *)(proids + i));
     } 
  }
  /* Esperar los hilos */
  for( i = 0; i < 10; i++)
  {
     pthread_join(tids[i],NULL);
  }
  return 0;
}


void * 
productor(void * args)
{   

  char letra, numero;
  char id = *((char *)args);
  numero = id + 1;
  printf("Productor %d creado\n",id);
  switch(id)
  {
    case 0: letra = 'a'; break;
    case 1: letra = 'b'; break;
    case 2: letra = 'c'; break;
    case 3: letra = 'd'; break;
    case 4: letra = 'e'; break;
  }
  int i, j = 0, semval;
  for(i = 0; i < producciones; i++)
  {
    sem_wait(&pro);
     while(1)
     {
           sem_getvalue(&semplet[j],&semval);
	   if( semval == 1)
	   {
		   sem_wait(&semplet[j]);
		   letras[j] = letra;
                   printf("Productor %d produjo %c en zona %d letras\n",id,letra,j);
		   sem_post(&semclet[j]);
		   j = 0;
		   break;
	   }
	   j++;
	   if( j == 4) {  j = 0; }
     } 

     while(1)
     {
           sem_getvalue(&sempnum[j],&semval);
	   if( semval == 1)
	   {
		   sem_wait(&sempnum[j]);
		   numeros[j] = numero;
                   printf("Productor %d produjo %d en zona %d numeros\n",id,numero,j);
		   sem_post(&semcnum[j]);
		   j = 0;
		   break;
	   }
	   j++;
	   if( j == 4) {  j = 0; }
     } 
    sem_post(&pro); 
  } 

}

void * 
consumidor(void * args)
{
  char id = *((char *) args);
  printf("Consumidor %d creado\n",id);
  int i, j = 0, semval;
  for( i = 0; i < producciones; i++)
  {
     sem_wait(&con);
       while(1)
       {
          sem_getvalue(&semclet[j],&semval);
	  if(semval == 1)
	  {
             sem_wait(&semclet[j]);
             printf("Consumidor %d consumio %c en zona %d letras\n",id,letras[j],j);
	     sem_post(&semplet[j]);
	     j = 0;
	     break;
	  }
          j++;
	  if( j == 4 ){ j = 0; }
       }

       while(1)
       {
          sem_getvalue(&semcnum[j],&semval);
	  if(semval == 1)
	  {
             sem_wait(&semcnum[j]);
             printf("Consumidor %d consumio %d en zona %d numeros\n",id,numeros[j],j);
	     sem_post(&sempnum[j]);
	     j = 0;
	     break;
	  }
          j++;
	  if( j == 4 ){ j = 0; }
       }
     sem_post(&con);
  }

}
