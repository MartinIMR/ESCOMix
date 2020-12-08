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

double * correlacionar(struct senial *,struct senial *);

int
main(void)
{
 double s1[]= {2,-1,3,7,1,2,-3};
 double s2[]= {1,-1,2,-2,4,1,-2,5};

 struct senial secuencia1 = {s1,sizeof(s1)/sizeof(s1[0]),0};
 struct senial secuencia2 = {s2,sizeof(s2)/sizeof(s2[0]),0};

 struct senial correlacion;
 correlacion.elementos = secuencia2.elementos + secuencia1.elementos - 1; 
 correlacion.origen = secuencia2.origen;
 correlacion.datos = correlacionar(&secuencia1,&secuencia2);
 
 
 printf("La secuencia 1:\nx(n) = [%.2f",secuencia1.datos[0]);
 for(int i = 1; i < secuencia1.elementos;i++){ 
   printf(",%.2f",secuencia1.datos[i]);  
 }
 printf("]\n");

 printf("La secuencia 2:\ny(n) = [%.2f",secuencia2.datos[0]);
 for(int i = 1; i < secuencia2.elementos;i++){ 
   printf(",%.2f",secuencia2.datos[i]);  
 }
 printf("]\n");

 printf("\nLa correlacion de las seniales es:\nr(n) = [%.2f",correlacion.datos[0]);
 for(int i = 1; i < correlacion.elementos;i++){ 
   printf(",%.2f",correlacion.datos[i]);  
 }
 printf("]\n");
 //printf("\nCon origen en posicion [%d]=%.2f\n",convolucion.origen,convolucion.datos[convolucion.origen]);
 return 0;
 
}

double * 
correlacionar(struct senial * secuencia1,struct senial * secuencia2)
{
 int datos = secuencia2->elementos + secuencia1->elementos - 1; 
 double * correlacion = (double *) malloc(sizeof(double)*datos);
 
 int els1 = secuencia1->elementos;
 int els2 = secuencia2->elementos;
 //Calcular posibles con secuencia 2
 for(int i = els1;i>=0;i--)
 {
    double suma = 0;
    int ps2,ps1;
    for(ps2 = i,ps1 = 0; els2 > ps2 && els1 > ps1;ps1++,ps2++)
    {
       suma += secuencia1->datos[ps1] * secuencia2->datos[ps2];
    }
    printf("\nSUma:%f",suma);
    correlacion[els2-1-i] = suma;
 }
 //Calcular posibles con la entrada
 for(int i = 1; i < els1;i++)
 {
    double suma = 0;
    int ps2,ps1;
    for(ps2 = 0,ps1 = i; els2 > ps2 && els1 > ps1;ps1++,ps2++)
    {
       suma += secuencia1->datos[ps1] * secuencia2->datos[ps2];
    }
    printf("\nSUma:%f",suma);
    correlacion[els2-1+i] = suma;
 }
 return correlacion;
}

