#ifndef RECONOCIMIENTO_H
#define RECONOCIMIENTO_H

struct posicion * obtener_posicion(int );
struct posicion * obtener_estructura(char *);
unsigned char reconocer_entrada(unsigned char *);
void imprimir_posicion(struct posicion *);

#endif
