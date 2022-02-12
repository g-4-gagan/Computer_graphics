#include<iostream>
using namespace std;

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main()
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int xmax, ymax;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode,(char*)"");

   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

    setcolor(getmaxcolor());
    xmax = getmaxx();
    ymax = getmaxy();
	float x1,y1,x2,y2;
	cout<<"\nEnter the x1,y1,x2,y2 coordinates value :: ";
	scanf("%f%f%f%f", &x1, &y1, &x2, &y2);
//	cin>>x1>>y1>>x2>>y2;
//	cout<<"\n\t Enter the x2,y2 coordinates value :: ";
//	cin>>x2,y2;
	
//	cleardevice();
	
	float m,y;
	m=(y2-y1)/(x2-x1);
	cout<<x1<<y1<<x2<<y2;
//	cout<<"M is \t"<<m;
	for(int i=x1; i<x2; i++)
	{
		cout<<i;
		y=i*m;
		putpixel(i,y,RED);
//		cout<<y;
	}

   /* draw a diagonal line */
   
//  line(0, 0, xmax, ymax);

   /* clean up */
   getch();
   closegraph();
   return 0;
}
