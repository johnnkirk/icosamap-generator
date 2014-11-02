/* file: trigtest.c */

#include "icomap02.h"

int main(argc,argv) int argc;char **argv; { double a,d,x,y,u,v;
  d=PI/50;
  for(a=(-(PI-(d/3)));a<=(PI-(d/3));a+=d) {
/*    x=sin(a);y=cos(a);u=asin(x);v=acos(y);
    printf("a: %10.7lf, x: %10.7lf, y: %10.7lf, u: %10.7lf, v: %10.7lf\n",
           a,x,y,u,v); } }                                                */
/*    x=sin(a);y=cos(a);u=(y>=0)?asin(x):((x>=0)?acos(y):(-acos(y)));
    printf("a: %10.7lf,      x: %10.7lf, y: %10.7lf,      u: %10.7lf\n",
           a,x,y,u); } }                                                  */
/*    x=sin(a);y=cos(a);u=atan(y/x);v=atan(x/y);
    printf("a: %10.7lf, x: %10.7lf, y: %10.7lf, u: %10.7lf, v: %10.7lf\n",
           a,x,y,u,v); } }                                                */
    x=sin(a);y=cos(a);u=atan(x/y)+((y>=0)?0:((x>=0)?PI:(-PI)));
    printf("a: %10.7lf,      x: %10.7lf, y: %10.7lf,      u: %10.7lf\n",
           a,x,y,u); } }
