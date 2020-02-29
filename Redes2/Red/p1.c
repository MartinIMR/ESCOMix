#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

int 
main(int argc,char *argv[])
{
  char bufer[50];
  struct sockaddr_in servidor,cliente;
  if( argc != 3)
  {
    printf("Se requiere puerto e ip\n");
    return 0;
  }
  int sock_des = socket(AF_INET,SOCK_STREAM,0); //Crear el socket
  if(sock_des == -1)
  {
    printf("No se pudo crear el ");
    return 0;
  }
  servidor.sin_family = AF_INET; //Protocolo
  servidor.sin_port = htons(atoi(argv[2])); //Convertir el puerto 
  servidor.sin_addr.s_addr = inet_addr(argv[1]); //Convertir la cadena a una estructura addr
  bind(sock_des,(struct sockaddr *)&servidor,sizeof(servidor)); //Ligar puerto con direccion ip
  //Empezar a escuchar conexiones
  listen(sock_des,2);
  //Aceptar conexiones
  int val = sizeof(cliente);
  int accp_des = accept(sock_des,(struct sockaddr *)&cliente,&val);
  //Fin configuracion
  int tb = recv(accp_des,bufer,sizeof(bufer), 0); // CERO PARA QUE SEA BLOQUEANte
  bufer[tb] = '\0';
  printf("El cliente envio %s\n",bufer);
  strcpy(bufer,"Mensaje hola");
  tb = send(accp_des, bufer,strlen(bufer),0);
  if(tb != strlen(bufer))
  {
    return 0;
  }
  sleep(5);
  close(accp_des);
  return 0;
}
