#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bmpFile.h"
#include "SurfaceClassfiy.h"
#include "template.h"
#include "RmwEdgeDetect.h"
void main()
{
	//clock_t s, e;
	//int width, height, width2 = 0, height2 = 0,mag=2;
	//double pi = 3.1415926;
	//BYTE *pRGBImg = RmwRead24BitBmpFile2Img("..//OrgImage/013.bmp", &width, &height),
	//*pGryImg = new BYTE[width*height], *pEdgeImg = new BYTE[width*height],*ps=new BYTE[width*height/mag/mag];
	//printf("width: %d   height:   %d \n", width, height);
	////ZzcRGBShrink(pRGBImg, width, height, mag, ps);
	////RmwWrite24BitImg2BmpFile(ps, width / mag, height / mag, "..//ResImage/1/11.bmp");
	//ZzcRGB2GRAY(pRGBImg, width, height, pGryImg);
	//printf("RGB change finish\n");
	//system("pause");
	//RmwSobelGrayImage(pGryImg, width, height, pEdgeImg);
	//ZzcGRAYShrink(pEdgeImg, width, height, mag,ps);
	//RmwWriteByteImg2BmpFile(ps, width/mag, mag, "..//ResImage/1.bmp");
	SurfaceClassfiy surfaceClassfiy;
	printf("beginning Init\n");
	surfaceClassfiy.Init();
	system("pause");
	printf("beginning train\n");
	surfaceClassfiy.train();
	system("pause");
	surfaceClassfiy.Reconise();

}