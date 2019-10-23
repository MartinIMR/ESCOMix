#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

struct posicion * 
obtener_ubicacion(int fd_serie)
{
  
  /* Reservar espacio de las variables una sola vez para toda la ejecucion */
  static unsigned char leido;
  /* Leida la primera G leer los siguientes 4 caracteres para ver si son PGLL*/
  static unsigned char * codigo = (unsigned char *) malloc(sizeof(char) * 5); 
  if(codigo == NULL)
  {
    perror("Hubo un error al reservar memoria");
    return NULL;
  }else
  {
    code[4] = '\0';
  }
  /* Reservar espacio almacenar la cadena */
  static unsigned char * cadena = (unsigned char *) malloc(sizeof(char) * MAX_BUF); 
  if(datos == NULL)
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
       read(fd_serie,leido,1);
       cadena[conteo] = leido;
       conteo++;
       if(conteo > MAX_BUF-2) /* Ampliar el espacio de bufer o hacer algo para evitar desbordamiento */
       {
         /* Por el momento utilizaremos un break */
         break;
       }
      }while(leido != '\n');
      return obtener_estructura(cadena);
    }
  }
  return NULL;
}

struct posicion *
obtener_estructura(char * cadena)
{
  /**
     $GPGLL
     Geographic Position, Latitude / Longitude and time.
     eg1. $GPGLL,3751.65,S,14507.36,E*77
     eg2. $GPGLL,4916.45,N,12311.12,W,225444,A

           4916.46,N    Latitude 49 deg. 16.45 min. North
           12311.12,W   Longitude 123 deg. 11.12 min. West
           225444       Fix taken at 22:54:44 UTC
           A            Data valid

     eg3. $GPGLL,5133.81,N,00042.25,W*75
               1    2     3    4 5

      1    5133.81   Current latitude
      2    N         North/South
      3    00042.25  Current longitude
      4    W         East/West
      5    *75       checksum

     eg4. $GPGLL,8888.8888,S,08888.8888,W,142655.000,A,A*57

    FORMATO:
    $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,A 
    llll.ll = Latitude of position
    a = N or S
    yyyyy.yy = Longitude of position
    a = E or W
    hhmmss.ss = UTC of position
    A = status: A = valid data 
 
  */

  /* Reservar estructura */
  struct posicion * leida = (struct posicion *) malloc(sizeof(struct posicion));
  if(leida == NULL)
  {
    perror("La estructura no pudo ser reservada");
    return NULL;
  }else
  { 
   (leida->hora)[11] = '\0';
  } 
  /*Utilizar sscanf como forma rapida de obtencion de datos */
  sscanf(cadena,",%f,%c,%f,%c,%s,%c",leida->latitud,leida->ns,
  leida->longitud,leida->ew,leida->hora,leida->estatus);
  return leida;
}

unsigned char 
reconocer_entrada(unsigned char * cadena)
{
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
