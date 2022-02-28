//1. Write a program to implement Bresenhams line drawing algorithm.
#include<stdio.h>
#include<graphics.h>
void midpointline(int x0,int y0,int x1,int y1,int value)
{
	double dy=y1-y0;
	double dx=x1-x0;
	int d=2*dy-dx;
	int incrE=2*dy;
	int increNE=2*(dy-dx);
	int x=x0;
	int y=y0;
	putpixel(x,y,value);
	while(x<x1)
	{ //choose E
		if(d<0)
		{
			d+=incrE;
			x++;
		}
		else
		{
			d+=increNE;
			x++;
			y++;
		}
		putpixel(x,y,value);
	}
}
main()
{
	int gd=DETECT,gm;
	int i,j,k;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	midpointline(100,100,200,200,3);
	getch();
	closegraph();
	return 0;
}
