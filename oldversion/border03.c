/* file: border03.c */

#include "icomap03.h"

int plotoutline(base,height,p1,p2,p3,p4,p5,p6,p7,p8)
float base,height,p1,p2,p3,p4,p5,p6,p7,p8; { /* draw outline */
  plot( 0            -p5, p2                  -p6,3);
  plot( base         -p5, p2                  -p6,2);
  plot( 1.5*base     -p5, p1                  -p6,2);
  plot( 2.0*base     -p5, p2                  -p6,2);
  plot( 2.5*base     -p5, p1                  -p6,2);
  plot( 3.0*base     -p5, p2                  -p6,2);
  plot( 3.0*base     -p5, p3                  -p6,2);
  plot( 1.5*base     -p5, p3                  -p6,2);
  plot( 2.0*base     -p5, p4                  -p6,2);
  plot( base         -p5, p4                  -p6,2);
  plot( 0.5*base     -p5, p3                  -p6,2);
  plot( 0            -p5, p4                  -p6,2);
  plot( -0.5*base    -p5, p8                  -p6,2);
  plot( -0.5*base    -p5, p3                  -p6,2);
  plot( -base        -p5, -p2                 -p6,2);
  plot( -base        -p5, p4                  -p6,2);
  plot( -2.0*base    -p5, p4                  -p6,2);
  plot( -1.75*base   -p5, p7                  -p6,2);
  plot( -2.5*base    -p5, p3                  -p6,2);
  plot( -1.5*base    -p5, p3                  -p6,2);
  plot( -2.0*base    -p5, p2                  -p6,2);
  plot( -base        -p5, p2                  -p6,2);
  plot( -1.5*base    -p5, p1                  -p6,2);
  plot( 0.5*base     -p5, p1                  -p6,2);
  plot( 0            -p5, p2                  -p6,2); }

int plotbounds(base,height,p1,p2,p3,p4,p5,p6,p7,p8)
float base,height,p1,p2,p3,p4,p5,p6,p7,p8; { /* draw bound's inside outline */
  plot( -1.75*base   -p5, p7                  -p6,3);
  plot( -0.5*base    -p5, p1                  -p6,2);
  plot( 0            -p5, p2                  -p6,2);
  plot( -base        -p5, p2                  -p6,2);
  plot( -0.5*base    -p5, p3                  -p6,2);
  plot( -1.5*base    -p5, p3                  -p6,2);
  plot( -base        -p5, p4                  -p6,2);
  plot( 0            -p5, p4                  -p6,3);
  plot( -0.5*base    -p5, p3                  -p6,2);
  plot( 0            -p5, p2                  -p6,2);
  plot( 0.5*base     -p5, p3                  -p6,2);
  plot( -0.5*base    -p5, p3                  -p6,2);
  plot( 0.5*base     -p5, p3                  -p6,3);
  plot( base         -p5, p2                  -p6,2);
  plot( 3.0*base     -p5, p2                  -p6,2);
  plot( 2.5*base     -p5, p3                  -p6,2);
  plot( 2.0*base     -p5, p2                  -p6,2);
  plot( base         -p5, p4                  -p6,2);
  plot( 0.5*base     -p5, p3                  -p6,3);
  plot( 1.5*base     -p5, p3                  -p6,2);
  plot( base         -p5, p2                  -p6,2); }
