#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

void * productor(void *);
void * consumidor(void *);
void escribir_archivo(char);


char letras[4], numeros[4];
int producciones = 10;
sem_t pro, con, semplet[4], semclet[4], sempnum[4], semcnum[4];
FILE * archivo1, * archivo2, * archivo3, * archivo4, * archivo5;
FILE * archivoa, * archivob, * archivoc, * archivod, * archivoe;


int 
main(void)
{
  pthread_t tids[10];
  char proids[10];

  archivoa = fopen("letras/a.txt","w");
  archivob = fopen("letras/b.txt","w");
  archivoc = fopen("letras/c.txt","w");
  archivod = fopen("letras/d.txt","w");
  archivoe = fopen("letras/e.txt","w");

  archivo1 = fopen("numeros/1.txt","w");
  archivo2 = fopen("numeros/2.txt","w");
  archivo3 = fopen("numeros/3.txt","w");
  archivo4 = fopen("numeros/4.txt","w");
  archivo5 = fopen("numeros/5.txt","w");

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
    fclose(archivo1);
    fclose(archivo2);
    fclose(archivo3);
    fclose(archivo4);
    fclose(archivo5);
    fclose(archivoa);
    fclose(archivob);
    fclose(archivoc);
    fclose(archivod);
    fclose(archivoe);
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
	     escribir_archivo(letras[j]);
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
	     escribir_archivo(numeros[j]);
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


void 
escribir_archivo(char produccion)
{
  switch(produccion)
  {
    case 'a': fprintf(archivoa,"%c\n",produccion); break;
    case 'b': fprintf(archivob,"%c\n",produccion); break;
    case 'c': fprintf(archivoc,"%c\n",produccion); break;
    case 'd': fprintf(archivod,"%c\n",produccion); break;
    case 'e': fprintf(archivoe,"%c\n",produccion); break;
    case 1: fprintf(archivo1,"%d\n",produccion); break;
    case 2: fprintf(archivo2,"%d\n",produccion); break;
    case 3: fprintf(archivo3,"%d\n",produccion); break;
    case 4: fprintf(archivo4,"%d\n",produccion); break;
    case 5: fprintf(archivo5,"%d\n",produccion); break;
  }

}
