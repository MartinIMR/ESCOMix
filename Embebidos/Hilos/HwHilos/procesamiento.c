/** @brief procesamiento.c, este
 * programa contiene las tareas
 * a realizar por los procesos generados.
 */

#include "defs.h"
#include "arreglos.h"

int
buscar_mayor(int * datos)
{
 int mayor = 0;
 register int i;
 for(i = 0; i < N; i++ )
 {
    if(datos[i] > mayor)
    {
       mayor = datos[i];
    }
 }
 return mayor;
}

int
buscar_menor(int * datos)
{
 int menor = datos[0];
 register int i;
 for(i = 0; i < N; i++ )
 {
    if(datos[i] < menor)
    {
       menor = datos[i];
    }
 }
 return menor;
}

int * 
promedio(int * datos)
{
 int promedio = 0;
 register int i;
 for( i = 0; i < N; i++)
 {
   promedio += datos[i];
 }
 return (int)(promedio/N);
}

int 
mas_frecuente(int * datos)
{
  int mf = datos[0];
  int acumulador = 0, acumulado = 0;
  register int i, j;
  for( i = 0; i < N; i++)
  {
     int actual = datos[i];
     for( j = 0; j < N; j++)
     {
        if( datos[j] == actual )
        {
          acumulador++; 
        }
     }
     if( acumulador > acumulado )
     {
        acumulado = acumulador;
        mf = actual;
     }
     acumulador = 0;
  }
  return mf;
}

int *
ordenamiento(int * datos)
{
   register int i,j;
   for( i = 0; i < N; i++)
   {
      for( j = 0; j < N-1; j++)
      {
          if( datos[j] > datos[j+1]   )
          {
              datos[j] = datos[j] + datos[j+1];
              datos[j+1] = datos[j] - datos[j+1];
              datos[j] = datos[j] - datos[j+1];
          }
      }
   }
   return datos;
}

int * 
histograma(int * datos)
{
  register int i,j;
  int * histograma = reservar_memoria(MAX_RAND);
  int count;
  for( i = 0; i < MAX_RAND; i++)
  {
     count = 0;
     for( j = 0; j < N; j++)
     {
       if(datos[j] == i )
       {
          count++;
       }
     }
     histograma[i] = count;
  }
  return histograma;
}

