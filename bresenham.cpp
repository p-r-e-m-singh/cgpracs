//Write a program to implement Bresenham’s line drawing algorithm.

#include<iostream>
#include<graphics.h>
using namespace std;


void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
     
    dx=x1-x0;
    dy=y1-y0;
     
    x=x0;
    y=y0;
     
    p=2*dy-dx;
     
    while(x<x1)
    {
    if(p>=0)
    {
    putpixel(x,y,7);
    y=y+1;
    p=p+2*dy-2*dx;
    }
    else
    {
    putpixel(x,y,7);
    p=p+2*dy;
    }
    x=x+1;
    }
}
int main()
{
    int gd = DETECT ,gm , error , x0 , y0 ,x1,y1;
    initgraph(&gd,&gm ,(char*)"");
    
    cout<<"ENter coordinates of first point : ";
    cin>>x0>>y0;
    
    cout<<"\nEnter coordinates of second number : ";
    cin>>x1>>y1;
    
    drawline(x0,y0,x1,y1);
    getch();
    closegraph();
    
    return 0;
}
