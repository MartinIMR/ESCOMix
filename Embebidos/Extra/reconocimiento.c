#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "reconocimiento.h"
#include "defs.h"

void 
imprimir_posicion(char * ubicacion)
{
  /*** 
  Por hacer darle un buen formato
  FORMATO DE IMPRESION :
  $GPGLL,4916.45,N,12311.12,W,225444,A

           4916.46,N    Latitude 49 deg. 16.45 min. North
           12311.12,W   Longitude 123 deg. 11.12 min. West
           225444       Fix taken at 22:54:44 UTC
           A            Data valid
  */

}

char * 
obtener_posicion(int fd_serie)
{
  
  /* Reservar espacio de las variables una sola vez para toda la ejecucion */
  static unsigned char leido;
  /* Leida la primera G leer los siguientes 4 caracteres para ver si son PGLL*/
  unsigned char * codigo = (unsigned char *) malloc(sizeof(char) * 5); 
  if(codigo == NULL)
  {
    perror("Hubo un error al reservar memoria");
    return NULL;
  }else
  {
    codigo[4] = '\0';
  }
  /* Reservar espacio almacenar la cadena */
  unsigned char * cadena = (unsigned char *) malloc(sizeof(char) * MAX_BUF); 
  if(cadena == NULL)
  {
    perror("Hubo un error al reservar memoria");
    return NULL;
  }else
  {
    cadena[MAX_BUF-1] = '\0';
  }

  read(fd_serie,&leido,1); /* Leer un byte y guardarlo en leido */
  if(leido == 'G')
  {
    read(fd_serie,codigo,4);
    if(reconocer_entrada(codigo)) /* Si la cadena coincide */
    {
      /* Contador para evitar que se desborde el buffer */
      unsigned char conteo = 0;
      /* Leer caracteres hasta el salto de linea */
      do
      {
       read(fd_serie,&leido,1);
       cadena[conteo] = leido;
       conteo++;
       if(conteo > MAX_BUF-2) /* Ampliar el espacio de bufer o hacer algo para evitar desbordamiento */
       {
         /* Por el momento utilizaremos un break */
         break;
       }
      }while(leido != '\n');
      return cadena;
    }
  }
  return NULL;
}


unsigned char 
reconocer_entrada(unsigned char * cadena)
{
  /*printf("La cadena es %s\n",cadena);*/
  /* La cadena $GPGLL - Geographic position, latitude / longitude */
  /* Necesitamos reconcer la parte PGLL */
  if(cadena[0] != 'P')
  {
     return 0;
  }else if(cadena[1] != 'G'){
     return 0;
  }else if(cadena[2] != 'L'){
     return 0;
  }else if(cadena[3] != 'L')
  { 
     return 0;
  }
  /* Si cumplio el patron regresar 1 */
  return 1;

}
