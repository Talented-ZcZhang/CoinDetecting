#include <windows.h>
#include <cstdio>
#include <cmath>
const double ex=1;
void ZzcDrawRectangle(BYTE *pImg,int width,int height,int x,int y,int width2,int height2)
{
	if(x-width2<0||y-height2<0)return;
	BYTE *pCur,*pEnd;
	for(pCur=pImg+(y-height2)*width+x-width2,pEnd=pImg+(y-height2)*width+x;pCur<pEnd;)
	{
		*(pCur++)=255;
	}
	for(pCur=pImg+y*width+x-width2,pEnd=pImg+y*width+x;pCur<pEnd;)
	{
		*(pCur++)=255;
	}
	for(pCur=pImg+(y-height2)*width+x-width2,pEnd=pImg+y*width+x-width2;pCur<pEnd;pCur+=width)
	{
		*(pCur)=255;
	}
	for(pCur=pImg+(y-height2)*width+x,pEnd=pImg+y*width+x;pCur<pEnd;pCur+=width)
	{
		*(pCur)=255;
	}
}
void ZzcDrawLine_Radian_Radius(BYTE*pImg,int width,int height,double *radius,double *radian,int N)
{
	for(int n=0;n<N;n++)
	{
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				if((int)(*(radius+n)-j*cos(*(radian+n))-i*sin(*(radian+n)))==0)
				{
					*(pImg+i*width+j)=255;
				}
			}
		}
	}
}
void ZzcDrawCircle(BYTE*pImg, int width, int height, int x, int y, int r, double ex)
{
	printf("%d %d %d", x, y, r);
	int i, j;
	double tmp;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			tmp = sqrt((double)(x - j)*(x - j) + (y - i)*(y - i)) - r;
			if (tmp < ex&& tmp>-ex)
			{
				*(pImg + i*width + j) = 255;
			}
		}
	}
}