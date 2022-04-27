#include <graphics.h>
#include <iostream>
using namespace std;

void mid_pt_circle(int a, int b , int rad)
{
	int x = 0, y=rad, p;
	putpixel(a,b+rad, GREEN);
	
	if(rad>0)			// if radius=0 then only single pt. is printed
	{
		putpixel(a,b-rad,GREEN);
		putpixel(a-rad,b,GREEN);
		putpixel(a+rad,b,GREEN);	
	}	
	p=1-rad;
	while(x<=y)
	{
		if(p<=0)
		{
			p+=(2*x)+1;
		}
		else{
			p+=(2*(x-y))+1;
			y--;
		}
		x++;
		putpixel(a+x, b+y, GREEN);
		putpixel(a-x, b+y, GREEN);
		putpixel(a+x, b-y, GREEN);
		putpixel(a-x, b-y, GREEN);
		putpixel(a+y, b+x, GREEN);
		putpixel(a-y, b+x, GREEN);
		putpixel(a+y, b-x, GREEN);
		putpixel(a-y, b-x, GREEN);
	}
} 
int main()
{
	cout<<"\n\n\t ---------------------- MID POINT CICLE DRAW ALGORITHM --------------------- ";
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode,"C:\YOGISOFT\TC\BGI");

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
	int x_center,y_center,radius;
	char choice='y';
	do
	{
		cout<<"\n\n\n\t Enter the Coordinates of circle (x and y) :: ";
		cin>>x_center>>y_center;
		cout<<"\n\t Enter the radius of the circle :: ";
		cin>>radius;
		if(radius < 0)
		{
			cout<<"\n\t Radius can't be negative !!";
			exit(1);
		}
	 	/* clean up */
		mid_pt_circle(x_center,y_center,radius);
		cout<<"\n\t\t do you want to continue ?? (y/n) :: ";
		cin>>choice;
	}while(choice =='y');
 	getch();
    //closegraph();
    return 0;
}

