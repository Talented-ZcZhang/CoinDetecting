#include <cstdio>
#include <windows.h>
#include "..//RmwCPP/bmpFile.h"
#include "ZzcEdgeDetect.h"
const long long inf=1e10;
void ZzcDiamondDetect1(BYTE *pImg,int width,int height,int width2,int height2,int *x0,int*y0)
{
	long long *Intergal=new long long[width*height];
	CalIntergal(pImg,width,height,Intergal);
	*x0=0,*y0=0;
	long long mx=-inf,temp=0,*pInte=Intergal;
	BYTE *pCur,*pEnd;long long *pleftup,*pleftdown,*prightup,*prightdown,*pr;
	int x=0,y=0;
	for(y=height2,
		pr=pInte+(height2+1)*width-1,
		prightdown=pInte+(height2)*width+width2,
		prightup=pInte+width2,
		pleftup=pInte,
		pleftdown=pInte+(height2)*width
		;y<height;
	    y++,
		pr+=width,
		prightdown+=width2,
		prightup+=width2,
		pleftdown+=width2,
		pleftup+=width2)
	{
		for(x=width2;x<width;x++)
		{
			temp=*(prightdown)+*(prightdown++)-*pr-*(prightup++)-*(pleftdown++)+*(pleftup++);
			if(temp>mx)
			{
				mx=temp;
				*x0=x;*y0=y;
			}
		}
	}
		delete Intergal;
}
void ZzcCoinLocation(BYTE * pImg, int width, int height, int width2, int height2, int*x0, int*y0)
{
	long long *Intergal = new long long[width*height];
	CalIntergal(pImg, width, height, Intergal);
	*x0 = 0, *y0 = 0;
	int i, j;
	long long mx = -1,tmp;
	for (i = height2; i < height; i++)
	{
		for (j = width2; j < width; j++)
		{
			tmp = *(Intergal + i*width + j) - *(Intergal + (i - height2)*width + j) - *(Intergal + i*width + j - width2) + *(Intergal + (i - height2)*width + j - width2);
			if (tmp > mx)
			{
				mx = tmp;
				*x0 = j;
				*y0 = i;
			}
		}
	}
}