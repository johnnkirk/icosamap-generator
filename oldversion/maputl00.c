/* file: maputl00.c */

#include "icomap01.h"

int writemsg(unit,format) int unit,format; { }

char *strip(str) char *str; { char *whspc=" \t\r\n";char *pos,ch,*loc;
  for(pos=str+strlen(str)-1;pos>=str;--pos) {
    for(ch=*pos,loc=whspc;*loc!='\0';++loc) if(*loc==ch) break;
    if(*loc=='\0') { pos[1]='\0';break; } } return str; }

int initplot() { int ret;int gdr,lomode,himode,gmode;

  /* initialize plot */
  gdr=0;initgraph(&gdr,&gmode,"c:\\borland\\turboc\\lib");
  if((ret=graphresult())<0) {
    printf("initgraph error: #%s.\n",grapherrormsg(ret));return FALSE; }
  getmoderange(gdr,&lomode,&himode);
/*  closegraph();
  printf("ret: %d, lo: %d, hi: %d\n",gdr,lomode,himode);
  getch();
  getgraphmode();
  setgraphmode();  */

/*  bar(0,0,getmaxx()/2,getmaxy());  */

  /* set pen at paper corner (origin)
  call plot(10.0*SCALE,-11.0*SCALE,3)
  call plot(10.0*SCALE,-5.0*SCALE,-3)     */ }

int closeplot() { closegraph(); }

int plot(x,y,penpos) float x,y;int penpos; { return plotpoint(x,y,penpos); }

int plotpoint(fx,fy,penpos) float fx,fy;int penpos; { int x,y;
  switch(penpos) { case 1: break;
    case 2: lineto((x=fx),(y=fy));break;
    case 3: moveto((x=fx),(y=fy));break; default: break; } }

int readrecord() { /* read one record containing 7 points of data */ }

int readverts(fname,ico) char *fname;ICOPARMS *ico; {
  char *punct=". \t\r\n";char *whspc=punct+1;
  FILE *ifile;char iline[1024];int ret,len,vert,deg,min;float sec,lat,lon;
  char *loc,*pos,ch;
  if(!(ifile=fopen(fname,"r"))) {
    printf("***** error opening %s *****\n",fname);return FALSE; }
  for(vert=0;vert<12;++vert) {
    /* read latitude record */
    if((ret=fgets(iline,1024,ifile))==NULL) { printf("***** error reading");
      printf(" vertex %d latitude line from file: %s *****\n",vert,fname);
      return FALSE; }
/*    printf("reading vert %d.  (from %s)\n",vert,fname);printf(">>%s",iline);
    getch();    */

    /* parse and check vertex number */
    /* skip whitespace, take substring to punct, check against vert */
    loc=iline;if((ret=strtol(iline,&loc,10)-1)!=vert) {
      printf("***** error in");
      printf("vertex number %d (found: %d) *****\n",vert,ret);return FALSE; }
/*    printf("saw vert %d\n",ret);
    getch();     */

    /* parse and alloc memory for vertex label */
    loc+=(len=strspn(loc,punct));loc[24]='\0';
/*    printf(">>%s<<\n",loc);            */
    pos=(ico->vlabel[vert])=malloc(len=strlen(strip(loc)));*pos='\0';
    strncpy(pos,loc,25);loc+=25;
/*    getch();     */

    /* parse lat degrees */
    deg=strtol(loc,&pos,10);if(tolower(*pos)!='d') {
      printf("***** vert %d lat deg err (%c) *****\n",vert,*pos);
      return(FALSE); } ++pos;
/*    getch();      */

    /* parse lat minutes */
    min=strtol(pos,&loc,10);if(tolower(*loc)!='m') {
      printf("***** vert %d lat min err (%c) *****\n",vert,*loc);
      return(FALSE); } ++loc;
/*    getch();       */

    /* parse lat seconds */
    sec=strtod(loc,&pos);if(tolower(*pos)!='s') {
      printf("***** vert %d lat sec err (%c) *****\n",vert,*pos);
      return(FALSE); } ++pos;
/*    getch();        */

    /* parse and accomodate lat quadrant id */
    lat=rad(deg+min/60.0+sec/3600.0);
    pos+=(len=strspn(pos,whspc));if((ch=tolower(*pos))=='s') lat=(-lat); else
    if(ch!='n') { printf("***** vert %d lat N/S err (%c) *****",vert,ch);
      return FALSE; }
/*    getch();         */

    /* read longitude record */
    if((ret=fgets(iline,1024,ifile))==NULL) { printf("***** error reading");
      printf(" vertex %d longitude line from file: %s *****\n",vert,fname);
      return FALSE; }
/*    getch();        */

    /* parse and accumulate lon degrees */
    deg=strtol(iline,&pos,10);if(tolower(*pos)!='d') {
      printf("***** vert %d lon deg err (%c) *****\n",vert,*pos);
      return(FALSE); } ++pos;
/*    getch();         */

    /* parse and accumulate lon minutes */
    min=strtol(pos,&loc,10);if(tolower(*loc)!='m') {
      printf("***** vert %d lon min err (%c) *****\n",vert,*loc);
      return(FALSE); } ++loc;
/*    getch();         */

    /* parse and accumulate lon seconds */
    sec=strtod(loc,&pos);if(tolower(*pos)!='s') {
      printf("***** vert %d lon sec err (%c) *****\n",vert,*pos);
      return(FALSE); } ++pos;
/*    getch();          */

    /* parse and accomodate lon quadrant id */
    lon=rad(deg+min/60.0+sec/3600.0);
    pos+=(len=strspn(pos,whspc));if((ch=tolower(*pos))=='w') lon=(-lon); else
    if(ch!='e') { printf("***** vert %d lon E/W err (%c) *****",vert,ch);
      return FALSE; }
/*    getch();          */

    /* put away results and read spacer line */
    (ico->vertex)[vert].lat=lat;(ico->vertex)[vert].lon=lon;
    if(((ret=fgets(iline,1024,ifile))==NULL)&&(vert<11)) {
      printf("***** error reading blank spacer line after");
      printf(" vertex %d from file: %s *****\n",vert,fname);return FALSE; }
/*    getch();           */ }
  return TRUE; }

int readparms(ico) ICOPARMS *ico; { /* read parameters */
  if(!readverts("vcoords.doc",ico)) {
    printf("***** readparms err *****\n");return FALSE; }
/*  read(1,102) (i,vcoord(i,1),vcoord(i,2),ii=1,12);
  read(1,102) (i,fcoord(i,1),fcoord(i,2),ii=1,22);
  read(1,102) (i,trm3(i),trm4(i),ii=1,22);
  read(2,102) (i,trm1(i),trm2(i),ii=1,22); */
  return TRUE; }

/* function to compute the angular great circle distance between two points */
float geogdist(p1,p2) GEOG *p1,*p2; { return acos(
  cos(p1->lat)*cos(p2->lat)*cos((p2->lon)-(p1->lon))+
  sin(p1->lat)*sin(p2->lat)); }

/* function to compute the angular great circle distance between two points */
float distll(lat1,lon1,lat2,lon2) float lat1,lon1,lat2,lon2; {
  return acos(cos(lat1)*cos(lat2)*cos(lon2-lon1)+sin(lat1)*sin(lat2)); }

/* function to take the radian measure of any angle expressed in degrees */
float rad(coord) float coord; { return coord*(PI/180.0); }

/* determine which icosahedral face a lat-lon point lies in */
FACE whichface(ico,geog) ICOPARMS *ico;GEOG *geog; {
  int face,prefac,ffff;float hold,coord,lat,lon,fa,fo;
  lat=(geog->lat);lon=(geog->lon);

  /* find triangle the point belongs in */
  hold=100.0;prefac=face;for(ffff=0;ffff<20;++ffff) {
/*  coord=distll(lat,lon,ico->fcoord][0],ico->fcoord[ffff][1]);   */
    if(hold>coord) { face=ffff;hold=coord; } }

  /* check whether belongs in 20, 21 (other halves of 4, 16) */
/*if((face==16)&&
     (distll(lat,lon,ico->vcoord[ 3][0],ico->vcoord[ 3][1])<
      distll(lat,lon,ico->vcoord[ 8][0],ico->vcoord[ 8][1]))) face=21; else
  if((face== 4)&&
     (distll(lat,lon,ico->vcoord[ 3][0],ico->vcoord[ 3][1])>
      distll(lat,lon,ico->vcoord[11][0],ico->vcoord[11][1]))&&
     (distll(lat,lon,ico->vcoord[ 3][0],ico->vcoord[ 3][1])>
      distll(lat,lon,ico->vcoord[ 1][0],ico->vcoord[ 1][1]))) face=20;   */
  return face; }

/* the icosahedral projection */
FACE icoproj0(ico,geog,mapp) ICOPARMS *ico;GEOG *geog;MAPP *mapp; {
  FACE face;float fa,fo,x0,y0,x1,y1,x2,y2,x3,y3,trm3,trm4,trm1,trm2,tx,ty;
  face=whichface(ico,geog);x0=(geog->lat);y0=(geog->lon);
/*  fa=(ico->fcoord[face][0]);fo=(ico->fcoord[face][1]);   */
  trm3=(ico->rotterm3[face]);trm4=(ico->rotterm4[face]);
  trm1=(ico->rotterm1[face]);trm2=(ico->rotterm2[face]);
  tx=(ico->ytranslate[face]);ty=(ico->ytranslate[face]);

  /* apply step 1, part 1 formula */
  /* project spherical coordinates to plane of triangle */
  x1=(-cos(x0)*sin(y0)-fo/(sin(x0)*sin(fa)))+(cos(x0)*cos(fa)*cos(y0-fo));
  y1=(sin(x0)*cos(fa)-cos(x0)*sin(fa)*cos(y0-fo))/
     (sin(x0)*sin(fa)+cos(x0)*cos(fa)*cos(y0-fo));

  /* apply step 1, part 2 formula */
  /* rotate to standard triangle orientation */
  x2=trm3*x1+trm4*y1;y2=(-trm4*x1)+trm3*y1;

  /* apply step 2, parts 1 and 2 formula */
  /* rotate and translate triangle to its map orientation and location */
  (mapp->x)=(trm1*x2+trm2*y2)+tx;(mapp->y)=((-trm2*x2)+trm1*y2)+ty; }

GEOG *carttogeog(destin,source) GEOG *destin;CART *source; {
  (destin->lat)=asin(source->z);
  (destin->lon)=atan((source->y)/(source->x)); }

CART *geogtocart(destin,source) CART *destin;GEOG *source; {
  (destin->x)=cos(source->lat)*cos(source->lon);
  (destin->y)=cos(source->lat)*sin(source->lon);
  (destin->z)=sin(source->lat); }

GEOG *segctr(p1,p2,ctr) GEOG *p1,*p2,*ctr; {
  CART cartp1,cartp2,cartctr;float len;
  geogtocart(&cartp1,p1);
  geogtocart(&cartp2,p2);
  (cartctr.x)=((cartp1.x)+(cartp2.x))/2.0;
  (cartctr.y)=((cartp1.y)+(cartp2.y))/2.0;
  (cartctr.z)=((cartp1.z)+(cartp2.z))/2.0;
  len=sqrt((cartctr.x)*(cartctr.x)+
           (cartctr.y)*(cartctr.y)+
           (cartctr.z)*(cartctr.z));
  (cartctr.x)/=len;(cartctr.y)/=len;(cartctr.z)/=len;
  return carttogeog(ctr,&cartctr);  }

GEOG *trictr(p1,p2,p3,ctr) GEOG *p1,*p2,*p3,*ctr; {
  CART cartp1,cartp2,cartp3,cartctr;float len;
  geogtocart(&cartp1,p1);geogtocart(&cartp2,p2);geogtocart(&cartp3,p3);
  (cartctr.x)=(cartp1.x)+(cartp2.x)+(cartp3.x);
  (cartctr.y)=(cartp1.y)+(cartp2.y)+(cartp3.y);
  (cartctr.z)=(cartp1.z)+(cartp2.z)+(cartp3.z);
  len=3.0*sqrt((cartctr.x)*(cartctr.x)+
               (cartctr.y)*(cartctr.y)+
               (cartctr.z)*(cartctr.z));
  (cartctr.x)/=len;(cartctr.y)/=len;(cartctr.z)/=len;
  return carttogeog(ctr,&cartctr);  }
