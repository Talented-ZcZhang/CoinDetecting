#include <windows.h>
#include <cstdio>
#include <cstring>
#include "bmpFile.h"
#include "RmwEdgeDetect.h"
#include "SurfaceClassfiy.h"
#include "zzc_bp_net.h"
#define SamAdress "..//OrgImage"
#define ShrinkAdress "..//ResImage"
#define Sample_Num 200
#define Class_Num 6
#define Target_Num 6
#define Feature_Len 1216
#define Width 64
#define Height 64
#define MAG 8
#define MAG2 4
char * Int2Str(int i,char *str)
{
	memset(str, 0, 256);
	str[2] = (i % 10) + '0'; i /= 10;
	str[1] = (i % 10) + '0'; i /= 10;
	str[0] = (i % 10) + '0';
	return str;
}
void Sample_Feature_Vec::Init()
{
	length = Feature_Len;
	Sam_Num = Sample_Num;
	Cla_Num = Class_Num;
	Tar_Num = Target_Num;
	pSample = new BYTE[Cla_Num*Sam_Num*length];
	pTarget = new double[Cla_Num*Sam_Num*Tar_Num];
	if (!pTarget)printf("null\n");
}
bool Sample_Feature_Vec::Read()
{
	printf("in read\n");
	int i,j,width=64,height=64;
	BYTE * pRGBImg, *pGryImg = new BYTE[width*height], *pEdgeImg = new BYTE[width*height], *pShrinkRGB = new BYTE[width / MAG*height / MAG * 3],
		*pShrinkGray = new BYTE[width / MAG2*height / MAG2];
	char*filename = new char[256],*str=new char[256];
	BYTE *pCur = pSample;
	double *pTarCur = pTarget;
	printf("tar 0\n");
	memset(pTarCur, 0, Cla_Num*Sam_Num*Tar_Num*sizeof(double));
	printf("begin read\n");
	//system("pause");
	for (j = 1; j <= Sample_Num; j++)
	{
		for (i = 1; i <= Class_Num; i++)
		{
			sprintf(filename, "%s/%d/%s.bmp", SamAdress, i, Int2Str(j,str));
			pRGBImg = RmwRead24BitBmpFile2Img(filename, &width, &height);
			printf("%s:  %d, %d  \n",filename, width, height);
			ZzcRGBShrink(pRGBImg, width, height, MAG,pShrinkRGB);

			//sprintf(filename, "%s/%d/%s.bmp", ShrinkAdress, i, Int2Str(j, str));
			//RmwWrite24BitImg2BmpFile(pShrinkRGB, width / MAG, height / MAG,filename);

			printf("shrink ok\n");
			ZzcRGB2GRAY(pRGBImg, width, height, pGryImg);
			printf("to gray ok\n");
			RmwSobelGrayImage(pGryImg, width, height, pEdgeImg);
			printf("sobel ok\n");
			ZzcGRAYShrink(pEdgeImg, width, height, MAG2, pShrinkGray);
			CreateFeatureVec(pShrinkRGB, width / MAG, height / MAG, pShrinkGray, width/MAG2, height/MAG2, pCur);
			printf("create feature ok\n");
			pCur += length;
			*(pTarCur + i - 1) = 1.0;
			pTarCur += Tar_Num;
		}
		//system("pause");
	}
	return true;
}
void CreateFeatureVec(BYTE*pColor, int color_width,int color_height, BYTE*pEdge, int edge_width, int edge_height, BYTE*Vec)
{
	BYTE *pEnd = Vec + color_width*color_height*3;
	while (Vec < pEnd)*(Vec++) = *(pColor++);
	pEnd = Vec + edge_width*edge_height;
	while (Vec < pEnd)*(Vec++) = *(pEdge++);
}
void SurfaceClassfiy::Init()
{
	sam.Init();
	printf("sample init ok\n");
	system("pause");
	sam.Read();
	printf("sample read ok\n");
	system("pause");
	core_params = new bp_alg_core_params;
	memset(core_params, 0, sizeof(core_params));
	if (init_bp_core_params(core_params) < 0)
	{
		exit(1);
	}

	if (init_bp_weight(core_params) < 0)
	{
		exit(1);
	}
}
void SurfaceClassfiy::train()
{
	if (!bp_train(core_params,&sam))
	{
		//exit(0);
	}
}
void SurfaceClassfiy::Reconise()
{
	int i, j, c = 0,l=1;
	double sample[Feature_Len];
	for (i = 0; i < Sample_Num*Class_Num; i++)
	{
		c++;
		TransformBYTE2Double(sam.pSample + i*Feature_Len, sample, Feature_Len);
		printf("%d :  %d  :  ", l, c);
		for (int j = 0; j < 10; j++)
		{
			printf("%lf  ", sample[j]);
		}
		printf("\n");
		recognise(core_params, sample);
		if (c == 50)
		{
			system("pause");
			c = 0;
		}
	}
}
void TransformBYTE2Double(BYTE *src, double*dst, int num)
{
	for (int i = 0; i < num; i++)
	{
		dst[i] = (double)src[i]/25600;
	}
}