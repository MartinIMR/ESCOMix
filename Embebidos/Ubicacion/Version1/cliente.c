#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "defs.h"
#include "reconocimiento.h"

int tamano_direccion, sockfd;
struct sockaddr_in direccion_servidor;

void inicializar_cliente(void);

int 
main(int argc, char **argv)
{
	
	char leer_mensaje[TAM_BUFFER];
        struct posicion * ubicacion;
	inicializar_cliente();

/*
 *	Inicia el establecimiento de una conexion mediante una apertura
 *	activa con el servidor
 *  connect - ES BLOQUEANTE
 */
	printf ("Estableciendo conexion ...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) 
	{
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}
        ubicacion = (struct posicion *) malloc(sizeof(struct posicion));
        if(read(sockfd,&ubicacion,sizeof(struct posicion)) < 0)
        {
	  perror ("Ocurrio algun problema al recibir datos del cliente");
        }
        imprimir_posicion(ubicacion); 
	close(sockfd);

	return 0;
}

void 
inicializar_cliente()
{
   /* Llenar con ceros */
   memset (&direccion_servidor, 0, sizeof (direccion_servidor));

   direccion_servidor.sin_family = AF_INET;
   direccion_servidor.sin_port = htons(PUERTO);

   /* Convertir la direccion IP a binario y asignarla */
   if( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0 )
   {
	perror("Ocurrio un error al momento de asignar la direccion IP");
	exit(1);
   }

  /*
   *  Creacion de las estructuras necesarias para el manejo de un socket
   *  SOCK_STREAM - Protocolo orientado a conexión
   */
   printf("Creando Socket ....\n");
   if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
   {
       perror("Ocurrio un problema en la creacion del socket");
       exit(1);
   }

}

