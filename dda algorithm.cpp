//11. Write a program of DDA.
#include<stdio.h>
#include<graphics.h>
void DDA(int x0,int y0,int x1,int y1,int value)
{
int x;
double dy=y1-y0;
double dx=x1-x0;
double m=dy/dx;
double y=y0;
for(x=x0;x<=x1;x++)
{
putpixel(x,y,value);
y+=m;
}
}
main()
{
int gd=DETECT,gm;
int i,j,k;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
DDA(100,100,200,200,3);
getch();
closegraph();
}
