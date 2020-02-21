#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

void * pro1(void *);
void * pro2(void *);
void * pro3(void *);
void * consumidor(void *);

char var;
sem_t sem, sem2;


int 
main(void)
{
  pthread_t tid1,tid2,tid3,tid4;
  /* Creacion e inicializacion del semaforo */
  sem_init(&sem, 0, 1);
  sem_init(&sem2, 0, 0);
  /* Creacion de los hilos */
  pthread_create(&tid1,NULL,pro1,NULL);
  pthread_create(&tid2,NULL,pro2,NULL);
  pthread_create(&tid3,NULL,pro3,NULL);
  pthread_create(&tid4,NULL,consumidor,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  pthread_join(tid3,NULL);
  pthread_join(tid4,NULL);

  return 0;
}


void * 
pro1(void * args)
{
  /* Diez numeros */
  char i;
  for( i = 48; i < 58; i++)
  {
     sem_wait(&sem);
     var = i;
     printf("Productor 1 produce:%c\n",var);
     sem_post(&sem2);
  }

}

void * 
pro2(void * args)
{
 /* Diez letras */
  char i;
  for( i = 97 ; i < 107; i++)
  {
     sem_wait(&sem);
     var = i;
     printf("Productor 2 produce:%c\n",var);
     sem_post(&sem2);
  }

}

void * 
pro3(void * args)
{
 /* Diez simbolos */
  char i;
  for( i = 33; i < 43; i++)
  {
     sem_wait(&sem);
     var = i;
     printf("Productor 3 produce:%c\n",var);
     sem_post(&sem2);
  }

}

void * 
consumidor(void * args)
{

  char i;
  for( i = 0; i < 30; i++)
  {
     sem_wait(&sem2);
     printf("Consumi valor:%c\n",var);
     /*
     if( var >= 33 && var <= 43)
     {
        printf("Consumi valor:%c de productor 3\n",var);
     }else if( var >= 48 && var <=58)
     {
        printf("Consumi valor:%c de productor 1\n",var);
     }else if( var >= 97 && var <= 107)
     {
        printf("Consumi valor:%c de productor 2\n",var);
     }
     */  
     sem_post(&sem);
  }

}
