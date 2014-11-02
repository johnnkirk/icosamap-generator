/* file: icomap00.c */

#define DEFVARS TRUE
#include "icomap00.h"

int main(argc,argv) int argc;char **argv; { int yasp,xasp;float ratio;
  float lat[7],lon[7];ICOPARMS parms;MAPP mapp;GEOG geog;int vcount,vert;

  /* calculate parameters for boundaries */
  base=1.323164552735024;height=base*(sqrt(3.0)/2.0);
  getaspectratio(&xasp,&yasp);ratio=0.64;
  factor=SCALE-2.0;base=factor*base;height=factor*height*ratio;
  p1=5.0*height/3.0;p2=2.0*height/3.0;
  p3=(-height)/3.0;p4=(-4.0*height)/3.0;
  p5=(-2.5*base);p6=(-5.0*height)/3.0;
  p7=(-5.0*height)/6.0;p8=(-height);

  printf("x: %d, y: %d, r: %6.3f\n",xasp,yasp,ratio);
  printf("base: %6.2f, height: %6.2f\n",base,height);
  printf("p5: %6.2f, p6: %6.2f\n",p5,p6);
  printf("p1: %6.2f, p2: %6.2f, p3: %6.2f, p4: %6.2f, p7: %6.2f, p8: %6.2f\n",
          p1,p2,p3,p4,p7,p8);
  getch();
  if(!readparms(&parms)) {
    printf("***** readparms error *****\n");return PROGFAIL; }
  printf("parms:\n");for(vcount=0;vcount<12;++vcount) {
    printf("%2d.  %20s %16.12f %16.12f\n",vcount,parms.vlabel[vcount],
      parms.vcoord[vcount][0],parms.vcoord[vcount][1]); }
  getch();
  for(vert=0;vert<12;++vert) {
    for(vcount=0;vcount<12;++vcount) {
      printf("%02d--%02d.",vert,vcount);
      printf(" %10.7f",distll(
           parms.vcoord[vert][0],parms.vcoord[vert][1],
           parms.vcoord[vcount][0],parms.vcoord[vcount][1]));
      printf("\n"); }
    printf("\n");
    getch(); }

  /* initialize plot initplot(); */

  /* draw outline plotoutline(base,height,-p1,-p2,-p3,-p4,p5,p6,-p7,-p8); */

  /* draw boundaries inside outline
  plotbounds(base,height,-p1,-p2,-p3,-p4,p5,p6,-p7,-p8); */

  while(FALSE /*TRUE*/) { writemsg(6,122);prefac=0;
    /* read record with 7 points, EOF? */ if(!readrecord()) break;
    for(i=0;i<7;++i) { /* for each point of an input record */
      /* test for (0,180), end of island? */
      if((abs(lat[i])<=.0001)&&((abs(lon[i]-180.0))<=.0001)) {
        /* housekeep new island marker */ nexfac=0;continue; }

      /* take radian measure */
      lon[i]=180.0-lon[i];lon[i]=rad(lon[i]);lat[i]=rad(lat[i]);

      /* housekeep new island marker */
      if(nexfac==1) nexfac=2; else if(nexfac==0) nexfac=1;

      face=icoproj0(&parms,&geog,&mapp);

      if(face!=prefac) nexfac=1;

      /* apply scaling factor */
      llat=y4*factor;llon=x4*factor;
      /* plot point */
      ii=4-nexfac;plotpoint(llon,llat,ii); }
    /* end of 7 points? if yes: */ }

  getch();
  /* close plot, write summaries (none here now) */
  closeplot();return PROGSUCC; }
