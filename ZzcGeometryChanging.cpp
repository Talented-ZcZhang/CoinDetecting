#include "ZzcMath.h"
#include <windows.h>
#include <cstdio>
void Rotate(BYTE *pImg,int width,int height,double p,BYTE *pResImg)
{
	int x,y,xint,yint;
	double SinP=ZzcSin(-p,5),CosP=ZzcCos(-p,5),xt,yt,t1,t2,x_Center=width/2.0,y_Center=height/2.0,x0,y0;
	printf("%llf %llf\n",SinP,CosP);
	BYTE *pCur=pResImg;
	for(y=0;y<height;y++)
	{
		for(x=0;x<width;x++,pResImg++)
		{
			x0=x-x_Center,y0=y-y_Center;
			xt=x0*CosP-y0*SinP+x_Center;
			yt=x0*SinP+y0*CosP+y_Center;
			xint=(int)(xt),yint=(int)(yt);
			//if(x0<0||x0>=width-1||y0<0||y0>=height-1)continue;
			if(xint<0||xint>=width-1||yint<0||yint>=height-1)continue;
			//printf("%d %d %d %d\n",x,y,x0,y0);
			//t1=*(pImg+y0*width+x0)*(x0+1-xt)+*(pImg+y0*width+x0+1)*(xt-x0);
			//t2=*(pImg+(y0+1)*width+x0)*(x0+1-xt)+*(pImg+(y0+1)*width+x0+1)*(xt-x0);
			t1=*(pImg+yint*width+xint)*(xint+1-xt)+*(pImg+yint*width+xint+1)*(xt-xint);
			t2=*(pImg+(yint+1)*width+xint)*(xint+1-xt)+*(pImg+(yint+1)*width+xint+1)*(xt-xint);
			*(pResImg)=(BYTE)(t1*(yint+1-yt)+t2*(yt-yint));
			//printf("%d %d %llf %llf\n",x,y,xt,yt);
			//printf("%llf %llf %d\n",t1,t2,*(pResImg));
			//system("pause");
		}
	}
}