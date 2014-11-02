/* file: icomap02.c */

#define DEFVARS TRUE
#include "icomap02.h"

int main(argc,argv) int argc;char **argv; { int yasp,xasp;double ratio,len;
  double lat[7],lon[7];ICOPARMS parms;MAPP mapp;GEOG geog,*point;
  int vcount,mcount,ccount,vert;

  /* calculate parameters for boundaries */
  base=1.323164552735024;height=base*(sqrt(3.0)/2.0);
  getaspectratio(&xasp,&yasp);ratio=0.64;
  factor=SCALE-2.0;base=factor*base;height=factor*height*ratio;
  p1=5.0*height/3.0;p2=2.0*height/3.0;
  p3=(-height)/3.0;p4=(-4.0*height)/3.0;
  p5=(-2.5*base);p6=(-5.0*height)/3.0;
  p7=(-5.0*height)/6.0;p8=(-height);

  printf("x: %d, y: %d, r: %6.3lf\n",xasp,yasp,ratio);
  printf("base: %6.2lf, height: %6.2lf\n",base,height);
  printf("p5: %6.2lf, p6: %6.2lf\n",p5,p6);
  printf("p1: %6.2lf, p2: %6.2lf, p3: %6.2lf, p4: %6.2lf, p7: %6.2lf, p8: %6.2lf\n",
          p1,p2,p3,p4,p7,p8);
  getch();
  if(!readparms(&parms)) {
    printf("***** readparms error *****\n");return PROGFAIL; }
  printf("parms:\n");for(vcount=0;vcount<12;++vcount) {
    printf("%2d.  %20s %16.12lf %16.12lf\n",vcount,parms.vlabel[vcount],
      parms.vertex[vcount].lat,parms.vertex[vcount].lon); }
  getch();
  mcount=0;for(vert=0;vert<12;++vert) {
    for(vcount=0;vcount<12;++vcount) {
      printf("%02d--%02d.",vert,vcount);
      printf(" %10.7lf",len=geogdist(&(parms.vertex[vert]),
                                     &(parms.vertex[vcount])));
      if((len>1.0)&&(len<2.0)) {
        point=segctr(&(parms.vertex[vert]),&(parms.vertex[vcount]),
                     &(parms.midpoint[mcount]));
        printf(" %7.4lf %7.4lf",point->lat,point->lon);
        printf(" -- %10.7lf",geogdist(point,&(parms.vertex[vert])));
        printf(" %10.7lf",geogdist(point,&(parms.vertex[vcount])));++mcount; }
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
