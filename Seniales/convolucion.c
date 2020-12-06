#include <stdio.h>
#include <stdlib.h>

struct senial
{
  double * datos;
  size_t elementos;
  int origen; 
};

double * invertir(double *,int );
double * convolucionar(struct senial *,struct senial *);

int
main(void)
{
 /* Datos de muestra */
 double s1[]= {1.0,2.0,3.0,1.0};
 double s2[]= {1.0,2.0,1.0,-1.0};

 struct senial entrada = {s1,sizeof(s1)/sizeof(s1[0]),0};
 struct senial impulso = {s2,sizeof(s2)/sizeof(s2[0]),1};
 struct senial invertida = {invertir(impulso.datos,impulso.elementos),
			    impulso.elementos,
			    impulso.elementos - 1 - impulso.origen};

 struct senial convolucion;
 convolucion.elementos = invertida.elementos + entrada.elementos - 1; 
 //convolucion.datos = (double *) malloc(sizeof(double)*convolucion.elementos);
 convolucion.origen = invertida.origen;
 convolucion.datos = convolucionar(&entrada,&invertida);
 
 printf("La convolucion de las seniales:\n");
 for(int i = 0; i < convolucion.elementos;i++){ 
   printf("%.2f,",convolucion.datos[i]);  
 }
 
 printf("\nCon origen en el dato:%.2f\n",convolucion.datos[convolucion.origen]);
 return 0;
}

double * 
convolucionar(struct senial * entrada,struct senial * invertida)
{
 int elementos = invertida->elementos + entrada->elementos - 1; 
 double * convolucion = (double *) malloc(sizeof(double)*elementos);
 
 return convolucion;
}

double *
invertir(double * datos, int elementos)
{
  double * invertidos = (double *) malloc(sizeof(datos[0]) * elementos);
  printf("La senial a invertir tiene %d elementos\n",elementos);
  int final = elementos-1;
  for(int n = final;n >= 0;n--)
  {
     invertidos[final-n] = datos[n];
     printf("%.2f,",invertidos[final-n]);
  }
  printf("\n");
  return invertidos;
}
