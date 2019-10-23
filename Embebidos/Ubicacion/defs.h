#ifndef DEFS_H
#define DEFS_H

#define MAX_BUF 50

struct posicion{
 float latitud;
 char ns;
 float longitud;
 char ew;
 char hora[12];
 char estatus; 
};

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
 
#endif
