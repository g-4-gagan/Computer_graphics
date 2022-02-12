//2. Write a program to implement mid-point circle drawing algorithm.
#include<graphics.h>
 #include<conio.h>
 #include<dos.h>
 void circlepoints(int x1,int y1,int x, int y,int val)
 {
putpixel(x1+x,y1+y,val);
putpixel(x1+y,y1+x,val);
putpixel(x1+y,y1-x,val);
putpixel(x1+x,y1-y,val);
putpixel(x1-x,y1-y,val);
putpixel(x1-y,y1-x,val);
putpixel(x1-x,y1+y,val);
putpixel(x1-y,y1+x,val);
 }
 void midpointcircle(int x1,int y1,int r,int value)
 {
int x=0,y=r,p;
p=1-r;
circlepoints(x1,y1,x,y,value);
while(x<y)
{
 if(p<0)
 {
p=p+2.0*x+3.0;
 }
 else
 {
p=p+2.0*(x-y)+5.0;
P a g e | 5
y=y-1;
 }
 x=x+1;
 circlepoints(x1,y1,x,y,value);
}
 }
 void main()
 {
int gd =DETECT,a,gm;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
printf("enter radius");
scanf("%d",&a);
midpointcircle(100,100,a,5);
getch();
closegraph();
 }
