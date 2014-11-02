#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define TRUE 1
#define FALSE 0

int main(argc,argv) int argc;char **argv; {
  int g_driver,g_mode,g_error,mx,my;
/*  detectgraph(&g_driver,&g_mode);
  if(g_driver<0) { printf("no graphics hardware detected\n");return FALSE; }
  printf("detected graphics driver #%d, mode #%d\n",g_driver,g_mode);
  getch();
*/  g_driver=0;initgraph(&g_driver,&g_mode,"c:\\borland\\turboc\\lib");
  g_error=graphresult();
  if(g_error<0) { printf("initgraph error: #%s.\n",grapherrormsg(g_error));
    return FALSE; }
  bar(0,0,(mx=getmaxx())/2,(my=getmaxy()));
  getch();
  closegraph();
  printf("e: %d, d: %d, m: %d, x: %d, y: %d\n",
        g_error,g_driver,g_mode,mx,my);
  getch();
  }
