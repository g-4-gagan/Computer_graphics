#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;

int main()
{
	int n=0,i,j,k,dy,dx,x,y,temp;
	int a[20][2], xi[20];
	float slope[20];
	
	cout<<"\n\t Enter the number of edges of the polygon :: ";
	cin>>n;
	cout<<"\n\t Enter the coordinates of polygon :: ";
	for(i=0;i<n;i++)
	{
		cout<<"\n\t\t ";
		cin>>a[i][0]>>a[i][1];
	}
	a[n][0] = a[0][0];			// the first  & last cood. of ploygons are eq.
	a[n][1] = a[0][1];
	
	int gd=DETECT,gm;
	initgraph(&gd, &gm, "C:\YOGISOFT\TC\BGI");
	
	for(i=0;i<n;i++)
	{
		line(a[i][0],a[i][1],a[i+1][0],a[i+1][1]);
	}
	getch();
	
	for(i=0;i<n;i++)				// calc. lines slope
	{
		dy=a[i+1][1]-a[i][1];
		dx=a[i+1][0]-a[i][0];
		
		if(dy==0){
			slope[i]=1.0;
		}
		if(dx==0){
			slope[i]=0.0;
		}
		if((dy!=0) && (dx!=0))
		{
			slope[i] = (float)dx/dy;
		}
	}
	
	for(y=0; y<480; y++)			//calc. interscetions pt. of the lines
	{
		k=0;
		for(i=0; i<n; i++)
		{
			if(((a[i][1] <= y) && (a[i+1][1] > y)) || ((a[i][1] > y) && (a[i+1][1] <=y )))
			{
				//here we want to convert the slope in int thats why we use int and pixels are already in integer
				xi[k]=(int)(a[i][0] + slope[i]*(y-a[i][1]));
				k++;
			}
		}
		for(j=0;j<k-1;j++){
			for(i=0;i<k-1;i++)
			{
				if(xi[i] > xi[i+1])
				{
					temp=xi[i];
					xi[i] = xi[i+1];
					xi[i+1] = temp;
				}
			}
		}
		setcolor(RED);
		for(i=0; i<k; i+=2)
		{
			line(xi[i],y,xi[i+1]+1,y);
			getch();
		}
	}
	return 0; 
}
