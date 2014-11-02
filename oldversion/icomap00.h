/* file: icomap00.h */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <process.h>
#include <graphics.h>

#define TRUE 1
#define FALSE 0

#define PROGSUCC 0
#define PROGFAIL 1

#define SCALE 100.0
#define PI 3.141592653589793

typedef int FACE;
typedef struct mapptag MAPP;
typedef struct geogtag GEOG;
typedef struct carttag CART;
typedef struct icoparmstag ICOPARMS;

struct mapptag { float x,y; };
struct geogtag { float lat,lon; };
struct carttag { float x,y,z; };
struct icoparmstag { float vcoord[12][2],fcoord[22][2];char *vlabel[12];
  float rotterm3[22],rotterm4[22],rotterm1[22],rotterm2[22];
  float xtranslate[22],ytranslate[22]; };

#ifdef DEFVARS
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN float hold,x1,y1,x2,y2,x3,y3,x4,y4;
EXTERN float coord,p1,p2,p3,p4,p7,p8,base,height,factor;
EXTERN float llat,llon,p5,p6;
EXTERN int i,ii,face,cardno,nexfac,island,ffff,buffer[4000];
EXTERN int count[1000],prefac;

/*
101   format(i7,3x,14f5.2)
char *format101="%7d   %f5.2%f5.2%f5.2%f5.2%f5.2%f5.2%f5.2"
                      "%f5.2%f5.2%f5.2%f5.2%f5.2%f5.2%f5.2\n";

102   format(i5,2f25.16)
char *format102="%5d%f25.16%f25.16\n";

103   format(3i5)
char *format103="%5d%5d%5d\n";

104   format(' ',f20.15,20x,f20.15)
char *format104=" %f20.15                    %f20.15\n";

105   format('1','vcoord1',33x,'vcoord2')
char *format105="\fvcoord1                                 vcoord2\n";

106   format('1')
char *format106="\f";

107   format(i2)
char *format107="%2d\n";

108   format(' ',i5,6f15.10)
char *format108=" %5d%f15.10%f15.10%f15.10%f15.10%f15.10%f15.10\n";
*/

int plot();
int initplot();
int closeplot();
int plotpoint();
int readrecord();
int readparms();
float dist();
float rad();
int writemsg();
int plotbounds();
int plotoutline();
FACE icoproj0();
FACE whichface();
