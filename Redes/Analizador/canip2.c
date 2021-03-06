#include <stdio.h>
#include <stdlib.h>

void analiza_trama(unsigned char []);
void analiza_ip(unsigned char []);
void analiza_icmp(unsigned char [],unsigned char);
void analiza_tcp(unsigned char [],unsigned char);
void analiza_udp(unsigned char [],unsigned char);
void puertos_tcp(unsigned short int);
void puertos_udp(unsigned short int);
void hacer_checksum(unsigned char [],unsigned char, unsigned short int);
void suma_icmp(unsigned char []);

int
main(void)
{

 unsigned char T[][200]=
	{ 
{
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, /* .......# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x04, /* .F...... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x23, /* .......# */
0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, /* .F....9. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, /* ........ */
0x39, 0xfe                                      /* 9. */
},

{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x01, /* E....... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x02, 0x00, 0x1f, /* ........ */
0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x39, 0xfe, /* E.....9. */
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00                          /* .... */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x46, 0x00, /* .F....F. */
0x80, 0x42, 0x04, 0x55, 0x34, 0x11, 0x80, 0x11, /* .B.U4... */
0x6b, 0xf0, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* k...9... */
0x67, 0x02, 0xaa, 0xbb, 0xcc, 0xdd, 0x04, 0x0c, /* g....... */
0x00, 0x35, 0x00, 0x2e, 0x85, 0x7c, 0xe2, 0x1a, /* .5...|.. */
0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x03, 0x77, 0x77, 0x77, 0x03, 0x69, /* ...www.i */
0x73, 0x63, 0x05, 0x65, 0x73, 0x63, 0x6f, 0x6d, /* sc.escom */
0x03, 0x69, 0x70, 0x6e, 0x02, 0x6d, 0x78, 0x00, /* .ipn.mx. */
0x00, 0x1c, 0x00, 0x01                          /* .... */
},
{
0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x02, /* ........ */
0xb3, 0x9c, 0xae, 0xba, 0x00, 0x04, 0xf0, 0xf1, /* ........ */
0x09, 0x8d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x9b, 0x6d  /* .....|.m */
},
{
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x23, /* .......# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x06, 0x00, 0x10, /* .F...... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x23, /* .......# */
0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, 0x39, 0xcb, /* .F....9. */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xcc, /* ........ */
0x3a, 0xe1                                      /* :. */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x06, 0x00, 0x10, /* E....... */
0x08, 0x00, 0x06, 0x04, 0x00, 0x04, 0x00, 0x1f, /* ........ */
0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1, /* E.....:. */
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00                          /* .... */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x00, 0x45, 0x00, /* E.....E. */
0x00, 0x6f, 0x90, 0x30, 0x40, 0x00, 0xfb, 0x11, /* .o.0@... */
0x24, 0xe7, 0x94, 0xcc, 0x67, 0x02, 0x94, 0xcc, /* $...g... */
0x39, 0xcb, 0x00, 0x35, 0x04, 0x0c, 0x00, 0x5b, /* 9..5...[ */
0xe8, 0x60, 0xe2, 0x1a, 0x85, 0x80, 0x00, 0x01, /* .`...... */
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x77, /* .......w */
0x77, 0x77, 0x03, 0x69, 0x73, 0x63, 0x05, 0x65, /* ww.isc.e */
0x73, 0x63, 0x6f, 0x6d, 0x03, 0x69, 0x70, 0x6e, /* scom.ipn */
0x02, 0x6d, 0x78, 0x00, 0x00, 0x1c, 0x00, 0x01, /* .mx..... */
0xc0, 0x14, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, /* ........ */
0x0e, 0x10, 0x00, 0x21, 0x04, 0x64, 0x6e, 0x73, /* ...!.dns */
0x31, 0xc0, 0x1a, 0x03, 0x74, 0x69, 0x63, 0xc0, /* 1...tic. */
0x1a, 0x77, 0xec, 0xdf, 0x29, 0x00, 0x00, 0x2a, /* .w..)..* */
0x30, 0x00, 0x00, 0x0e, 0x10, 0x00, 0x12, 0x75, /* 0......u */
0x00, 0x00, 0x00, 0x2a, 0x30                    /* ...*0 */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x45, 0x00, /* .F....E. */
0x00, 0x42, 0x04, 0x56, 0x00, 0x00, 0x80, 0x11, /* .B.V.... */
0x6b, 0xef, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* k...9... */
0x67, 0x02, 0x04, 0x0c, 0x00, 0x35, 0x00, 0x2e, /* g....5.. */
0xff, 0x87, 0x68, 0x2a, 0x01, 0x00, 0x00, 0x01, /* ..h*.... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x77, /* .......w */
0x77, 0x77, 0x03, 0x69, 0x73, 0x63, 0x05, 0x65, /* ww.isc.e */
0x73, 0x63, 0x6f, 0x6d, 0x03, 0x69, 0x70, 0x6e, /* scom.ipn */
0x02, 0x6d, 0x78, 0x00, 0x00, 0x01, 0x00, 0x01  /* .mx..... */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x23, /* ..E....# */
0x8b, 0x46, 0xe9, 0xad, 0x08, 0x00, 0x45, 0x00, /* .F....E. */
0x00, 0x3c, 0x04, 0x57, 0x00, 0x00, 0x80, 0x01, /* .<.W.... */
0x98, 0x25, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, /* .%..9... */
0x3a, 0xe1, 0x08, 0x00, 0x49, 0x5c, 0x03, 0x00, /* :...I\.. */
0x01, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, /* ..abcdef */
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, /* ghijklmn */
0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, /* opqrstuv */
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* wabcdefg */
0x68, 0x69                                      /* hi */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x08, 0x00, 0x45, 0x00, /* E.....E. */
0x00, 0x3c, 0x01, 0xb5, 0x00, 0x00, 0x3f, 0x01, /* .<....?. */
0xdb, 0xc7, 0x94, 0xcc, 0x3a, 0xe1, 0x94, 0xcc, /* ....:... */
0x39, 0xcb, 0x00, 0x00, 0x51, 0x5c, 0x03, 0x00, /* 9...Q\.. */
0x01, 0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, /* ..abcdef */
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, /* ghijklmn */
0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, /* opqrstuv */
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* wabcdefg */
0x68, 0x69                                      /* hi */
},
{
0x00, 0x1f, 0x45, 0x9d, 0x1e, 0xa2, 0x00, 0x1c, /* ..E..... */
0xc0, 0x7b, 0x35, 0xa1, 0x08, 0x00, 0x48, 0x00, /* .{5...H. */
0x00, 0x48, 0x5c, 0x7d, 0x00, 0x00, 0x80, 0x01, /* .H\}.... */
0x6c, 0x88, 0x94, 0xcc, 0x39, 0xc3, 0x94, 0xcc, /* l...9... */
0x00, 0x49, 0x07, 0x0b, 0x04, 0x00, 0x00, 0x00, /* .I...... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, /* ........ */
0x3b, 0x5c, 0x02, 0x00, 0x10, 0x00, 0x61, 0x62, /* ;\....ab */
0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, /* cdefghij */
0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, /* klmnopqr */
0x73, 0x74, 0x75, 0x76, 0x77, 0x61, 0x62, 0x63, /* stuvwabc */
0x64, 0x65, 0x66, 0x67, 0x68, 0x69              /* defghi */
},
{
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x00, 0x1f, /* .#.F.... */
0x45, 0x9d, 0x1e, 0xa2, 0x80, 0x35, 0x00, 0x01, /* E....5.. */
0x08, 0x00, 0x06, 0x04, 0x00, 0x03, 0x00, 0x1f, /* ........ */
0x45, 0x9d, 0x1e, 0xa2, 0x94, 0xcc, 0x3a, 0xe1, /* E.....:. */
0x00, 0x23, 0x8b, 0x46, 0xe9, 0xad, 0x94, 0xcc, /* .#.F.... */
0x39, 0xcb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 9....... */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0xd8, 0xee, 0xdf, 0xb0  /* ........ */
},
{
0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, /* ........ */
0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0, /* ........ */
0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d  /* ....C..m */
},
{
0x02, 0xff, 0x53, 0xc3, 0xe9, 0xab, 0x00, 0xff, /* ..S..... */
0x66, 0x7f, 0xd4, 0x3c, 0x08, 0x00, 0x45, 0x00, /* f..<..E. */
0x00, 0x30, 0x2c, 0x00, 0x40, 0x00, 0x80, 0x06, /* .0,.@... */
0x4b, 0x74, 0xc0, 0xa8, 0x01, 0x02, 0xc0, 0xa8, /* Kt...... */
0x01, 0x01, 0x04, 0x03, 0x00, 0x15, 0x00, 0x3b, /* .......; */
0xcf, 0x44, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, /* .D....p  */
0x20, 0x00, 0x0c, 0x34, 0x00, 0x00, 0x02, 0x04, /*  ..4.... */
0x05, 0xb4, 0x01, 0x01, 0x04, 0x02              /* ...... */
},
{
0x00, 0xff, 0x66, 0x7f, 0xd4, 0x3c, 0x02, 0xff, /* ..f..<.. */
0x53, 0xc3, 0xe9, 0xab, 0x08, 0x00, 0x45, 0x00, /* S.....E. */
0x00, 0x30, 0x05, 0xc4, 0x40, 0x00, 0x80, 0x06, /* .0..@... */
0x71, 0xb0, 0xc0, 0xa8, 0x01, 0x01, 0xc0, 0xa8, /* q....... */
0x01, 0x02, 0x00, 0x15, 0x04, 0x03, 0x21, 0x5d, /* ......!] */
0x3a, 0x44, 0x00, 0x3b, 0xcf, 0x45, 0x70, 0x12, /* :D.;.Ep. */
0x44, 0x70, 0x8c, 0x11, 0x00, 0x00, 0x02, 0x04, /* Dp...... */
0x05, 0xb4, 0x01, 0x01, 0x04, 0x02              /* ...... */
},
{
0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, /* ........ */
0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x12, 0xf0, 0xf0, /* ........ */
0x0a, 0x0b, 0x0e, 0x00, 0xff, 0xef, 0x14, 0x00, /* ........ */
0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x7f, 0x23, /* ..(....# */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
0x00, 0x00, 0x00, 0x00, 0x01, 0x99, 0x98, 0x6d  /* .......m */
}

};
   unsigned char i;
   for( i = 0; i < 16;i++)
   {
      printf("\n****** Analizando trama %d*******\n",i+1);
      analiza_trama(T[i]);
      printf("\n****** Fin de trama %d*******\n",i+1);
   } 
   return 0;
}

void 
analiza_trama(unsigned char trama[])
{
  printf("\n------ CABECERA ETHERNET ------\n");
  printf("MAC destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",trama[0],trama[1],
  trama[2],trama[3],trama[4],trama[5]);
  printf("MAC origen: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",trama[6],trama[7],
  trama[8],trama[9],trama[10],trama[11]);
  unsigned short int ToT = (trama[12]<<8) | (trama[13]);
  if(ToT <= 1500)
  {
    printf("Tipo LLC. Tamanio %d bytes\n",ToT);
  }else if(ToT == 2048){
    printf("Tipo IP.\n");
    analiza_ip(trama);
  }else if(ToT == 2054){ 
    printf("Tipo ARP.\n");
  }else
  {
    printf("Tipo otro.\n");
  }
 return;
}

void 
analiza_ip(unsigned char T[])
{
   printf("------ CABECERA IP------\n");
   if( (T[14]>>4) == 4 )
   {
      printf("Version:IPv4.\n");
   }
   unsigned char ihl = (T[14] & 0x0F);
   printf("Tamanio de la cabecera(IHL):%d palabras.\n",ihl);
   ihl = ihl * 4;
   if( T[15] & 0x10 )
   {
     printf("Bandera D (Minimize delay) activada.\n");
   }else if(T[15] & 0x08){
     printf("Bandera T (Maximize throughout) activada.\n");
   }else if(T[15] & 0x04){
     printf("Bandera R (Maximize reliability) activada.\n");
   }else if(T[15] & 0x02)
   {
     printf("Bandera C (Minimize cost) activada.\n");
   }
   printf("Longitud total:%d.\n", (T[16]<<8|T[17]) );
   printf("Identificacion:%d.\n", (T[18]<<8|T[19]) );
   printf("Desplazamiento de fragmentos:\n");
   if(T[20]&0x20)
   {
    printf("Bandera M(More fragments) activada.\n");
    printf("Posicion del fragmento en el datagrama original:");
    short int posicion = ((T[20] & 0x1f) << 8) | ( T[21]);
    printf("%d bytes desplazado.\n", (posicion*8));
   }else if(T[20]&0x40)
   {
    printf("Bandera D (Do not fragment) activada.\n");
   }
   printf("Tiempo de vida:%d saltos.\n",T[22]);
   printf("Protocolo:");
   switch(T[23])
   {
      case 1:
      printf("ICMP.\n");
      break;
      case 6:
      printf("TCP.\n");
      break;
      case 17:
      printf("UDP.\n");
      break;
      default:
      printf("Otro.\n");
      break;
   }
   printf("Suma de comprobacion:%d\n",((T[24]<<8) | T[25]));
   printf("Direccion origen: %d.%d.%d.%d\n",T[26],T[27],T[28],T[29]);
   printf("Direccion destino: %d.%d.%d.%d\n",T[30],T[31],T[32],T[33]);
   if(ihl > 20)
   {
      printf("Opciones:");
      switch(T[34])
      {
         case 0:
         printf("End of option.\n");
         break;
         case 1:
         printf("No operation (pad).\n");
         break;
         case 7:
         printf("Record route.\n");
         break;
         case 68:
         printf("Timestamp.\n");
         break;
         case 131:
         printf("Loose source route.\n");
         break;
         case 137:
         printf("Strict source route.\n");
         break;
         default:
         printf("Valor:%d\n",T[34]);
         printf("Undefined.\n");
         break;
      }
   }
   printf("Debe terminar en T[%d]\n",13+ihl);
   hacer_checksum(&T[14],ihl,(T[24]<<8) | T[25]);
   switch(T[23])
   {
      case 1:
      analiza_icmp(T,ihl);
      break;
      case 6:
      analiza_tcp(T,ihl);
      break;
      case 17:
      analiza_udp(T,ihl);
      break;
   }
  
}



void 
hacer_checksum(unsigned char T[],unsigned char tamanio,unsigned short int checksum)
{

  printf("---- Realizando la suma de comprobacion ----\n");
  unsigned int acumulador = 0;
  unsigned char i;
  
  /* Para IP */
  for(i = 0; i < (tamanio-1); i += 2)
  {
    /* printf("Tomando posiciones del arreglo T[%d]=%x y T[%d]=%x\n",i,T[i]<<8,i+1,T[i+1]); */
    if(i !=10 ) /* No tomar posicion 10 del arreglo para IP */
    {
      acumulador += (T[i]<<8) + T[i+1];
    }

    /* printf("La suma ahora tiene:%x\n",acumulador); */
  }

  if(tamanio & 0x01) /* Si es impar sumar el faltante */
  {
    acumulador += (T[i]<<8);
  }
  unsigned short int suma = (acumulador >> 16) + (acumulador & 0xffff);
  /* printf("La suma es:%x\n",suma); */
  suma = ~suma;
  /* printf("La comprobacion arrojo:%x\n",~(suma + checksum)); */
  if( suma != checksum )
  {
     printf(" =( Erroneo\n");
     printf("El checksum correcto es:%x.\n",suma); 
  }else
  {
     printf(" =) Checksum correcto \n");
  }
}

void 
analiza_icmp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA ICMP ------\n");
 printf("Iniciando en la posicion T[%d]=%x\n",14+ihl,T[14+ihl]); 
 printf("Tipo:%d.\n",T[14+ihl]); 
 printf("Codigo:%d.\n",T[15+ihl]);
 printf("Suma de comprobacion:%d.\n",(T[16+ihl]<<8|T[17+ihl]));
 printf("Otra informacion:%d.\n",(T[18+ihl]<<24|T[19+ihl]<<16|T[20+ihl]<<8|T[21+ihl]));
 suma_icmp(T);
}

void
analiza_tcp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA TCP ------\n");
 printf("Iniciando en la posicion T[%d]=%x\n",14+ihl,T[14+ihl]); 
 printf("Puerto origen:%d. ",(T[14+ihl]<<8|T[15+ihl])); 
 puertos_tcp((T[14+ihl]<<8 | T[15+ihl]));
 printf("Puerto destino:%d. ",(T[16+ihl]<<8|T[17+ihl])); 
 puertos_tcp((T[16+ihl]<<8 | T[17+ihl]));
 printf("Numero de secuencia:%d\n",(T[18+ihl]<<24|T[19+ihl]<<16|T[20+ihl]<<8|T[21+ihl]));
 printf("Numero de acuse:%d\n",(T[22+ihl]<<24|T[23+ihl]<<16|T[24+ihl]<<8|T[25+ihl]));
 unsigned char offset = T[26+ihl]>>4;
 printf("Offset:%d palabras.\n",offset);
 offset = offset*4;
 printf("Banderas:%d.\n",T[27+ihl]);
 printf("Ventana:%d.\n",(T[28+ihl]<<8|T[29+ihl]));
 printf("Suma de comprobacion:%d\n",(T[30+ihl]<<8|T[31+ihl]));
 printf("Apuntador urgente:%d\n",(T[32+ihl]<<8|T[33+ihl]));
 printf("Termina en la posicion T[%d]=%x\n",33+ihl,T[33+ihl]);
 printf("Debe terminar en T[%d]\n",13+offset+ihl);
 /* hacer_checksum(&T[14+ihl],offset); */
}

void 
suma_icmp(unsigned char T[])
{

   unsigned char ihl = (T[14] & 0x0f) * 4;
   printf("El ihl:%d\n",ihl);
   /* Hacer suma de cabecera ICMP */
   unsigned char i;
   unsigned int acumulador = 0;
   unsigned short int suma;
   /* Suma de la cabecera ICMP */
   acumulador = (T[14+ihl]<<8) + T[15+ihl]; /* Type and Code */
   acumulador += (T[18+ihl]<<8) + T[19+ihl]; /* Other information */
   acumulador += (T[20+ihl]<<8) + T[21+ihl]; /* Other information continuation*/
   suma = (acumulador>>16) + (acumulador & 0xffff);
   suma = ~ suma;
   acumulador = (T[16 + ihl]<<8) | (T[17 + ihl]);
   printf("El campo checksum es:%x\n",acumulador);
   printf("La comprobacion dio:%x\n",suma);
}


void 
puertos_tcp(unsigned short int puerto)
{
  switch(puerto)
  {
    case 7:
    printf("Echo.\n");
    break;
    case 19:
    printf("Chargen.\n");
    break;
    case 20:
    printf("Ftp-data.\n");
    break;
    case 21:
    printf("Ftp-control.\n");
    break;
    case 22:
    printf("SSH.\n");
    break;
    case 23:
    printf("Telnet.\n");
    break;
    case 25:
    printf("Smtp.\n");
    break;
    case 53:
    printf("Domain.\n");
    break;
    case 79:
    printf("Finger.\n");
    break;
    case 80:
    printf("Http.\n");
    break;
    case 110:
    printf("pop3.\n");
    break;
    case 111:
    printf("sunrpc.\n");
    break;
    case 119:
    printf("nntp.\n");
    break;
    case 139:
    printf("netbios-ssn.\n");
    break;
    case 143:
    printf("imap.\n");
    break;
    case 179:
    printf("bgp.\n");
    break;
    case 389:
    printf("ldap.\n");
    break;
    case 443:
    printf("https(ssl).\n");
    break;
    case 445:
    printf("microsoft-ds.\n");
    break;
    case 1080:
    printf("Socks.\n");
    break;
    default:
    printf("\n");
    break;
  }

}

void
analiza_udp(unsigned char T[], unsigned char ihl)
{
 printf("------ CABECERA UDP ------\n");
 printf("Iniciando en la posicion T[%d]\n",14+ihl); 
 printf("Puerto origen:%d. ",(T[14+ihl]<<8|T[15+ihl]));
 puertos_udp((T[14+ihl]<<8|T[15+ihl]));
 printf("Puerto destino:%d. ",(T[16+ihl]<<8|T[17+ihl])); 
 puertos_udp((T[16+ihl]<<8|T[17+ihl]));
 unsigned short int longitud = (T[18+ihl]<<8) | T[19+ihl];
 printf("Longitud:%d.\n", longitud); 
 printf("Suma de comprobacion:%d.\n",(T[20+ihl]<<8|T[21+ihl])); 
 /* hacer_checksum(&T[14+ihl], longitud); */
}


void 
puertos_udp(unsigned short int puerto)
{
  switch(puerto)
  {
    case 7:
    printf("Echo.\n");
    break;
    case 19:
    printf("Chargen.\n");
    break;
    case 37:
    printf("Time.\n");
    break;
    case 53:
    printf("Domain.\n");
    break;
    case 67:
    printf("Bootps (DHCP)\n");
    break;
    case 68:
    printf("Bootpc (DHCP).\n");
    break;
    case 69:
    printf("Tftp.\n");
    break;
    case 137:
    printf("Netbios-ns.\n");
    break;
    case 138:
    printf("Netbios-dgm.\n");
    break;
    case 161:
    printf("Snmp.\n");
    break;
    case 162:
    printf("Snmp-trap.\n");
    break;
    case 500:
    printf("Isakmp.\n");
    break;
    case 514:
    printf("Syslog.\n");
    break;
    case 520:
    printf("Rip.\n");
    break;
    case 33434:
    printf("Traceroute.\n");
    break;
    default:
    printf("\n");
    break;
  }
}


