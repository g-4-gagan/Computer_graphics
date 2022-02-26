//11. Write a program of DDA with six different cases.
/*
cases to be take care off dX and dY, the one which will be 
greater will be iterated through. then compare (x0,y0) and (x1,y1)
as per the iterative variable choose we will compare both and swap 
in case of greater and smaller disimalarity.
*/

#include<stdio.h>
#include<graphics.h>
void DDA(int x0,int y0,int x1,int y1,int value)
{
	double x, y;
	double dy=y1-y0;
	double dx=x1-x0;
	double m=dy/dx;
	if(dx>dy)
	{
		if(x0>x1)
		{
			swap(x0,x1);
			swap(y0,y1);
		}
		x=x0;
		y=y0;
		for(;x<=x1;x++)
		{
			putpixel(x,y,value);
			y+=m;
		}	
	}
	else
	{
		m=1/m;
		if(y0>y1)
		{
			swap(x0,x1);
			swap(y0,y1);
		}
		x=x0;
		y=y0;
		for(;y<=y1;y++)
		{
			putpixel(x,y,value);
			x+=m;
		}
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
