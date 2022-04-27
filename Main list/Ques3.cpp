#include<graphics.h>
#include<conio.h>
#include<iostream>
using namespace std;

static int Left=1,rt=2,btm=4,top=8, xmin,ymin,xmax,ymax;
int getcode(int x, int y)
{
	int code=0;
	if(y > ymax) code = top;
	if(y < ymin) code = btm;
	if(x < xmin) code = Left;
	if(x > xmax) code = rt;
	return code;
}
int main()
{
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "C:\YOGISOFT\TC\BGI");
	setcolor(WHITE);
	cout<<"\n\t Enter Window Minimum & Maximum Vlaues :: ";
	cin>>xmin>>ymin>>xmax>>ymax;
	rectangle(xmin,ymin,xmax,ymax);
	
	int x1,y1,x2,y2;
	cout<<"\n\t Enter The Endpoints of the Line :: ";
	cin>>x1>>y1>>x2>>y2;
	line(x1,y1,x2,y2);
	getch();
	
	int outcode1 = getcode(x1,y1), outcode2 = getcode(x2,y2);
	int accept = 0;
	while(1)
	{
		float m=(float)(y2-y1)/(x2-x1);
		if(outcode1==0 && outcode2 == 0){
			accept=1;
			break;
		}else if((outcode1 & outcode2 )!=0){
			break;
		}else{
			int x,y,temp;
			if(outcode1 ==0){
				temp=outcode2;
			}else{
				temp = outcode1;
			}
			if(temp & top){
				x=x1+(ymax-y1)/m;
				y=ymax;
			}else if(temp & btm){
				x=x1+(ymin-y1)/m;
				y=ymin;
			}else if (temp & Left){
				x=xmin;
				y=y1+m*(xmin-x1);	
			}else if(temp & rt){
				x=xmax;
				y=y1+m*(xmax-x1);
			}
			if(temp == outcode1){
				x1=x;
				y1=y;
				outcode1=getcode(x1,y1);
			}else{
				x2=x;
				y2=y;
				outcode2=getcode(x2,y2);
			}
		}
	}
	cout<<"\n\t AFTER CLIPPING :: - ";
	if(accept){
		cleardevice();
		rectangle(xmin,ymin,xmax,ymax);
		setcolor(RED);
		line(x1,y1,x2,y2);
	}
	getch();
	closegraph();
}
