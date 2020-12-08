 /* https://stackoverflow.com/questions/1835986/how-to-use-eof-to-run-through-a-text-file-in-c 
    http://www.mathcs.emory.edu/~cheung/Courses/561/Syllabus/3-C/text-files.html
 */
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1000
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
 double s1[]= {1/2.0,1/4.0,1/8.0,1/16.0,1/32.0,1/64.0};
 double s2[]= {1/4.0,1/16.0,1/64.0,1/256.0,1/1024.0,1/4096.0};

 struct senial entrada = {s1,sizeof(s1)/sizeof(s1[0]),0};
 struct senial impulso = {s2,sizeof(s2)/sizeof(s2[0]),0};
 struct senial invertida = {invertir(impulso.datos,impulso.elementos),
			    impulso.elementos,
			    impulso.elementos - 1 - impulso.origen};

 struct senial convolucion;
 convolucion.elementos = invertida.elementos + entrada.elementos - 1; 
 convolucion.origen = impulso.origen;
 convolucion.datos = convolucionar(&entrada,&invertida);
 
 
 printf("La senial de entrada:\nx(n) = [%f",entrada.datos[0]);
 for(int i = 1; i < entrada.elementos;i++){ 
   printf(",%f",entrada.datos[i]);  
 }
 printf("]\n");

 printf("La respuesta impulso:\nh(n) = [%f",impulso.datos[0]);
 for(int i = 1; i < impulso.elementos;i++){ 
   printf(",%f",impulso.datos[i]);  
 }
 printf("]\n");

 printf("\nLa convolucion de las seniales es:\ny(n) = [%lf",convolucion.datos[0]);
 for(int i = 1; i < convolucion.elementos;i++){ 
   printf(",%lf",convolucion.datos[i]);  
 }
 printf("]\n");
 //printf("\nCon origen en posicion [%d]=%.2f\n",convolucion.origen,convolucion.datos[convolucion.origen]);
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
 //Calcular posibles con inversa
 for(int i = elInv-1;i>=0;i--)
 {
    double suma = 0;
    int pInv,pEnt;
    for(pInv = i,pEnt = 0; elInv > pInv && elEnt > pEnt;pEnt++,pInv++)
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
  int final = elementos-1;
  for(int n = final;n >= 0;n--)
  {
     invertidos[final-n] = datos[n];
     //printf("%.2f,",invertidos[final-n]);
  }
  //printf("\n");
  return invertidos;
}
