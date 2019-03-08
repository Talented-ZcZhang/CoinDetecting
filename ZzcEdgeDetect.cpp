#include <cstdio>
#include <cmath>
#include <windows.h>
#include "bmpFile.h"
void ZzcFilter_Sobel(BYTE* pImg, int width, int height, BYTE* pResImg)
{
	memset(pResImg, 0, sizeof(width*height));
	int x, y,tmp1,tmp2,temp;
	pImg += width + 1;
	BYTE*pEnd=pResImg+width*height-width-1, *pCur=pResImg+width+1;
	for (y = 1; y < height-1; y++,pCur+=2,pImg+=2)
	{
		for (x = 1; x < width-1; x++,pImg++)
		{
			tmp1 = (*(pImg - width + 1) + *(pImg + 1) + *(pImg + 1) + *(pImg + width + 1));
			tmp1 -= (*(pImg - width - 1) + *(pImg - 1) + *(pImg - 1 )+ *(pImg + width - 1));
			tmp2 = (*(pImg - width - 1) + *(pImg - width) + *(pImg - width) + *(pImg - width + 1));
			tmp2 -= (*(pImg + width - 1) + *(pImg + width) + *(pImg + width) + *(pImg + width + 1));

			temp = tmp1 >> 31;   //tmp1=abs(tmp1)
			tmp1 ^= temp;
			tmp1 -= temp;
			temp = tmp2 >> 31;     //tmp2=abs(tmp2)
			tmp2 ^= temp;
			tmp2 -= temp;

			*(pCur++) = min(255, tmp1 + tmp2);
			//if(tmp1+tmp2>255)*(pCur++)=255 else *(pCur++)=tmp1+tmp2;
		}
	}
}
void ZzcExtractFrame(BYTE*pImg, int width, int height, int size, int threshold, BYTE*pResImg)
{
	int i, j;
	memset(pResImg, 0, width*height);
	long long *Intergal = new long long[width*height];
	CalIntergal(pImg, width, height, Intergal);
	for (i = size + 1; i<height ; i++)               //左边界
	{
		for (j = size + 1; j<width ; j++)
		{
			if ((int)*(Intergal + i*width + j) - *(Intergal + (i - size - 1)*width + j) - *(Intergal + i*width + j - size - 1) + *(Intergal + (i - size - 1)*width + j - size - 1) >= threshold)
			{
				*(pResImg + i*width + j) = 255;
				break;
			}
		}
	}
	for (i = size + 1; i<height; i++)               //右边界
	{
		for (j = width - 1; j>size; j--)
		{
			if ((int)*(Intergal + i*width + j) - *(Intergal + (i - size - 1)*width + j) - *(Intergal + i*width + j - size - 1) + *(Intergal + (i - size - 1)*width + j - size - 1) >= threshold)
			{
				*(pResImg + i*width + j) = 255;
				break;
			}
		}
	}
	for (j = size + 1; j<width; j++)               //上边界
	{
		for (i = size + 1; i<height; i++)
		{
			if (*(Intergal + i*width + j) - *(Intergal + (i - size - 1)*width + j) - *(Intergal + i*width + j - size - 1) + *(Intergal + (i - size - 1)*width + j - size - 1) >= threshold)
			{
				*(pResImg + i*width + j) = 255;
				break;
			}
		}
	}
	for (j = size + 1; j<width; j++)               //下边界
	{
		for (i = height - 1; i>size; i--)
		{
			if (*(Intergal + i*width + j) - *(Intergal + (i - size - 1)*width + j) - *(Intergal + i*width + j - size - 1) + *(Intergal + (i - size - 1)*width + j - size - 1) >= threshold)
			{
				*(pResImg + i*width + j) = 255;
				break;
			}
		}
	}
}
void ZzcEdgeSharpen(BYTE*pImg, int width, int height,int size)
{
	
}