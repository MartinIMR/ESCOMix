#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include "defs.h"


void isr(int);
void establecer_servidor(void);

int socket_fd;
struct sockaddr_in direccion_servidor; /* Estructura de la familia AF_INET, que almacena direccion */

int 
main(int argc, char **argv)
{

    int cliente_sockfd;
    char fdarg[12],fname[] = "./serial";
    pid_t pid;
    establecer_servidor();
    while(TRUE)
    {
   	if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0 )
	{
		perror("Ocurrio algun problema al atender a un cliente");
		exit(1);
   	}
        sprintf(fdarg,"%d",cliente_sockfd);
        char * args[3] = {fname,fdarg,NULL};
        pid = fork();
        if(!pid)
        {
          printf("PID hijo:%d\n",getpid());
          execvp(fname,args);
          _exit(0); 
        }
        close(cliente_sockfd);
    }
    close(sockfd);
    return 0;
}


void 
establecer_servidor(void)
{
  /* Llenar la estructura de dirección con ceros */
  memset(&direccion_servidor, 0, sizeof (direccion_servidor));

  /* Asignacion de parametros de la estructura */
  direccion_servidor.sin_family = AF_INET; /* IPv4 */
  direccion_servidor.sin_port = htons(PUERTO); /* htons - El ordenamiento de bytes en la red es siempre big-endian, arquitecturas little-endian revertir bytes */
  direccion_servidor.sin_addr.s_addr = INADDR_ANY; /* La dirección del host puede ser cualquiera */

  /* Creación del socket del servidor, regresa un file descriptor de este mismo */
  printf("Creando Socket ....\n");
  if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
  {
     perror("Ocurrio un problema en la creacion del socket");
     exit(1);
  }

  /* Asociar el fd del socket con una direccion de red */ 
  printf("Configurando socket ...\n");
  if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0 )
  {
     perror ("Ocurrio un problema al configurar el socket");
     exit(1);
  }

  /* El socket estará en espera de solicitudes, esto es, sera pasivo y creara una cola para solicitudes */
  printf ("Estableciendo la aceptacion de clientes...\n");
  if( listen(sockfd, COLA_CLIENTES) < 0 )	
  {
     perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
     exit(1);
  }
  
  /* Asignacion de la señal */
  if(signal(SIGCLD,isr) == SIG_ERR)
  {
     perror("Error al signar la señal");
     exit(-1);
  }

  /* Version señal usuario  
  if(signal(SIGUSR1,isr) == SIG_ERR)
  {
     perror("Error al asignar la senial\n");
     exit(EXIT_FAILURE);
  }
  */

  

}

void 
isr(int sig)
{
   int estado;
   pid_t pid;
   if(sig == SIGCLD)
   {
      pid = wait(&estado);
      printf("señal SIGCLD detectada en proceso hijo: %d\n",pid);
   }
}

/* Version señal del usuario 
void 
isr(int sig)
{
  int estado;
  pid_t pid;
  if(sig == SIGUSR1)
  {
     pid = wait(&estado);
     printf("Senial USR1 detectada en proceso hijo: %d\n", pid);
  }
}
*/
