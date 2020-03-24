#include <stdio.h>
#include <stdlib.h>

unsigned char * leer_direccion(void);
char obtener_clase(char ip[4]);

int
main(void)
{
 unsigned char * ip;
 ip = leer_direccion();
 char clase = obtener_clase(ip);
 printf("La ip es de clase:%c\n",clase);
 return 0;
}

char 
obtener_clase(char ip[4])
{
  if( (ip[0] & 0xf0) ==  0xf0 )
  {
     return 'E';
  }else if( (ip[0] & 0xe0) == 0xe0 ){
     return 'D';
  }else if( (ip[0] & 0xc0) == 0xc0 ){
     return 'C';
  }else if( (ip[0] & 0x80) == 0x80 ){
     return 'B';
  }
  return 'A';
}

unsigned char * 
leer_direccion(void)
{
  char * buffer = (char *) malloc(sizeof(char) * 16);
  if( buffer == NULL)
  { 
    perror("No se pudo reservar espacio de bufer");
    exit(-1);
  }
  printf("Introduce una direccion ip:\n");
  scanf("%15s",buffer);
  unsigned char * ip = (unsigned char *) malloc(sizeof(char) * 4);
  if( ip == NULL)
  { 
    perror("No se pudo reservar espacio para la ip");
    exit(-1);
  }
  sscanf(buffer,"%d.%d.%d.%d",ip,ip+1,ip+2,ip+3);
  free(buffer);
  return ip;
}
