/* file: border00.c */

#include "icomap01.h"

int plotoutline(base,height,p1,p2,p3,p4,p5,p6,p7,p8)
double base,height,p1,p2,p3,p4,p5,p6,p7,p8; { /* draw outline */
  plot( 0            , p2                  ,3);
  plot( base         , p2                  ,2);
  plot( 1.5*base     , p1                  ,2);
  plot( 2.0*base     , p2                  ,2);
  plot( 2.5*base     , p1                  ,2);
  plot( 3.0*base     , p2                  ,2);
  plot( 3.0*base     , p3                  ,2);
  plot( 1.5*base     , p3                  ,2);
  plot( 2.0*base     , p4                  ,2);
  plot( base         , p4                  ,2);
  plot( 0.5*base     , p3                  ,2);
  plot( 0            , p4                  ,2);
  plot( -0.5*base    , p8                  ,2);
  plot( -0.5*base    , p3                  ,2);
  plot( -base        , -p2                 ,2);
  plot( -base        , p4                  ,2);
  plot( -2.0*base    , p4                  ,2);
  plot( -1.75*base   , p7                  ,2);
  plot( -2.5*base    , p3                  ,2);
  plot( -1.5*base    , p3                  ,2);
  plot( -2.0*base    , p2                  ,2);
  plot( -base        , p2                  ,2);
  plot( -1.5*base    , p1                  ,2);
  plot( 0.5*base     , p1                  ,2);
  plot( 0            , p2                  ,2); }

int plotbounds(base,height,p1,p2,p3,p4,p5,p6,p7,p8)
float base,height,p1,p2,p3,p4,p5,p6,p7,p8; { /* draw bound's inside outline */
  plot( -1.75*base   , p7                  ,3);
  plot( -0.5*base    , p1                  ,2);
  plot( 0            , p2                  ,2);
  plot( -base        , p2                  ,2);
  plot( -0.5*base    , p3                  ,2);
  plot( -1.5*base    , p3                  ,2);
  plot( -base        , p4                  ,2);
  plot( 0            , p4                  ,3);
  plot( -0.5*base    , p3                  ,2);
  plot( 0            , p2                  ,2);
  plot( 0.5*base     , p3                  ,2);
  plot( -0.5*base    , p3                  ,2);
  plot( 0.5*base     , p3                  ,3);
  plot( base         , p2                  ,2);
  plot( 3.0*base     , p2                  ,2);
  plot( 2.5*base     , p3                  ,2);
  plot( 2.0*base     , p2                  ,2);
  plot( base         , p4                  ,2);
  plot( 0.5*base     , p3                  ,3);
  plot( 1.5*base     , p3                  ,2);
  plot( base         , p2                  ,2); }
