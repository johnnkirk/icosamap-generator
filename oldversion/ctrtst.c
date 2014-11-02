/* file: ctrtst.c */

#include "icomap00.h"

int main(argc,argv) int argc;char **argv; {
  ICOPARMS *icos;int vert1,vert2,vert3;GEOG p1,p2,p3,m12,m23,m31;
  readverts("vcoords.doc",icos);
  vert1=2;vert2=5;vert3=6;
  p1.lat=(icos->vcoord)[vert1][0];p1.lon=(icos->vcoord)[vert1][1];
  p2.lat=(icos->vcoord)[vert2][0];p2.lon=(icos->vcoord)[vert2][1];
  p3.lat=(icos->vcoord)[vert3][0];p3.lon=(icos->vcoord)[vert3][1];
  printf("dist12: %8.4f, dist23: %8.4f, dist31: %8.4f\n",
         dist(icos->vcoord[vert1][0],icos->vcoord[vert1][1],
              icos->vcoord[vert2][0],icos->vcoord[vert2][1]),
         dist(icos->vcoord[vert2][0],icos->vcoord[vert2][1],
              icos->vcoord[vert3][0],icos->vcoord[vert3][1]),
         dist(icos->vcoord[vert3][0],icos->vcoord[vert3][1],
              icos->vcoord[vert1][0],icos->vcoord[vert1][1]));
  segctr(&p1,&p2,&m12);segctr(&p2,&p3,&m23);segctr(&p3,&p1,&m31);
  printf("a-mid-dist12: %7.4f, b-mid-dist12: %7.4f\n",
         dist(p1.lat,p1.lon,m12.lat,m12.lon),
         dist(p2.lat,p2.lon,m12.lat,m12.lon));
  return PROGSUCC; }
