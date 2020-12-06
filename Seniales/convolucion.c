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
 //double s1[]= {1.0,2.0,3.0,1.0,5.0,6.0,7.0};
 //double s2[]= {1.0,2.0,1.0,-1.0};

 double s1[]= {1,2,0,2,1};
 double s2[]= {1,2,0,2,1};

 struct senial entrada = {s1,sizeof(s1)/sizeof(s1[0]),2};
 struct senial impulso = {s2,sizeof(s2)/sizeof(s2[0]),2};
 struct senial invertida = {invertir(impulso.datos,impulso.elementos),
			    impulso.elementos,
			    impulso.elementos - 1 - impulso.origen};

 struct senial convolucion;
 convolucion.elementos = invertida.elementos + entrada.elementos - 1; 
 //convolucion.datos = (double *) malloc(sizeof(double)*convolucion.elementos);
 convolucion.origen = impulso.origen;
 convolucion.datos = convolucionar(&entrada,&invertida);
 
 printf("La convolucion de las seniales:\n");
 for(int i = 0; i < convolucion.elementos;i++){ 
   printf("%.2f,",convolucion.datos[i]);  
 }
 
 printf("\nCon origen en posicion [%d]=%.2f\n",convolucion.origen,convolucion.datos[convolucion.origen]);
 return 0;
}

double * 
convolucionar(struct senial * entrada,struct senial * invertida)
{
 int elementos = invertida->elementos + entrada->elementos - 1; 
 double * convolucion = (double *) malloc(sizeof(double)*elementos);
 int elEnt = entrada->elementos;
 int elInv = invertida->elementos;
 int oEnt = entrada->origen;
 printf("Elementos entrada:%d // Elementos invertida:%d\n",elEnt,elInv);
 printf("Origen entrada:%d\n",oEnt);
 //Calcular posibles con inversa (incluye origen)
 for(int i = elInv-1;i>=0;i--)
 {
    double suma = 0;
    int pInv,pEnt;
    for(pInv = i,pEnt = oEnt; elInv > pInv && elEnt > pEnt;pEnt++,pInv++)
    {
       suma += entrada->datos[pEnt] * invertida->datos[pInv];
    }
    convolucion[elInv-1-i] = suma;
 }
 //Calcular posibles con la entrada
 for(int i = 1; i < elEnt;i++)
 {
    double suma = 0;
    int pInv,pEnt;
    for(pInv = 0,pEnt = i; elInv > pInv && elEnt > pEnt;pEnt++,pInv++)
    {
       suma += entrada->datos[pEnt] * invertida->datos[pInv];
    }
    convolucion[elInv-1+i] = suma;
 }
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
