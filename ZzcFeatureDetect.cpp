#include <windows.h>
#include <cstdio>
#include <cmath>
#include <cstring>
const double pi = 3.1415926;
const double ex = 1;
int ZzcHough(BYTE*pImg,int width,int height,int N,double *radius,double RadiusStep, double *radian,double RadianStep)
{
	int Radian_num=pi/RadianStep,Radius_num=sqrt((double)width*width+height*height)/RadiusStep,r,x,y,i,j,Cost,Sint,tmp;
	printf("Radius num : %d  Radian num :  %d \n",Radius_num,Radian_num);
	double cur_radian, tmp2;
	int *count=new int[2*Radius_num*Radian_num];
	memset(count,0,2*Radius_num*Radian_num*4);
	for(r=0;r<Radian_num;r++)
	{
		cur_radian = r*RadianStep;
		Cost = (int)(cos(cur_radian)*2048), Sint = (int)(sin(cur_radian)*2048);
		for(y=0;y<height;y++)
		{
			for(x=0;x<width;x++)
			{
				//cur_radian=r*RadianStep;
				//tmp=x*cos(cur_radian)+y*sin(cur_radian);
				if(*(pImg+y*width+x)==255)
				{
					tmp = ((int)((x*Cost + y*Sint) / RadiusStep) >> 11);
					tmp += Radius_num;
					//*(count + ((int)(tmp / RadiusStep))*Radian_num + r) += 1;
					*(count+tmp*Radian_num+r)+=1;
				}
				//printf("%d %d %d %.6lf %.6lf %d\n",r,y,x,cur_radian,tmp,(int)tmp/RadiusStep);
				//system("pause");
			}
		}
	}
	system("pause");
	memset(radian, 0, N * 8);
	memset(radius, 0, N * 8);
	int *pCur=count,*pEnd=count+Radius_num*Radian_num,pc=0;
	int *TmpCount = new int[N],tint,k,tmp_count;
	double tmp_radian, tmp_radius , tdouble;
	memset(TmpCount, -1, N*4);
	//选取过白点最多的前N条直线
	for(i=-Radius_num;i<Radius_num;i++)
	{
		for(j=0;j<Radian_num;j++)
		{
			tmp_count = *(pCur++);
			//printf("%d ", tmp_count);
			tmp_radian = j*RadianStep;
			tmp_radius = i*RadiusStep;
			for (k = 0; k < N; k++)
			{
				if (tmp_count > *(TmpCount + k))
				{
					tint = *(TmpCount + k);
					*(TmpCount + k) = tmp_count;
					tmp_count = tint;

					tdouble = *(radian + k);
					*(radian + k) = tmp_radian;
					tmp_radian = tdouble;

					tdouble = *(radius + k);
					*(radius + k) = tmp_radius;
					tmp_radius = tdouble;

				}
			}
			//if(*(pCur++)>=threshold)
			//{
			//	*(radius++)=i*RadiusStep;
			//	*(radian++)=j*RadianStep;
			//	pc++;
			//}
			//printf("%d  ",count[i*Radian_num+j]);
			//system("pause");
		}
		//printf("\n");
	}
	return N;
}
void ZzcCircleDetect(BYTE *pImg, int width, int height, int R, int error, int RStep, int &x, int &y, int &r)
{
	int *RowMidpoint = new int[width], *ColMidpoint = new int[height], i, j, left, right, up, down,mx;
	memset(RowMidpoint, 0, 4 * width);
	memset(ColMidpoint, 0, 4 * height);
	BYTE *pCur;
	//找圆心横坐标
	for (i = 0; i < height; i++)
	{
		pCur = pImg + i*width;
		for (j = 0; *(pCur) == 0&&j<width; j++, pCur++);
		if (j == width)continue;
		left = j;
		pCur = pImg + (i + 1)*width - 1;
		for (j = width - 1; *(pCur) == 0&&j>=0; j--, pCur--);
		*(RowMidpoint + ((left + j) >> 1))+=1;
	}
	mx = -1;
	for (i = 0; i < width; i++)
	{
		if (*(RowMidpoint + i)>mx)
		{
			mx = *(RowMidpoint+i);
			x = i;
		}
	}
	//找圆心纵坐标
	for (j = 0; j < width; j++)
	{
		pCur = pImg + j;
		for (i = 0; *(pCur) == 0&&i<height; i++, pCur += width);
		if (i == height)continue;
		up = i;
		pCur = pImg + (height - 1)*width + j;
		for (i = height - 1; *(pCur) == 0&&i>=0; i--, pCur -= width);
		*(ColMidpoint + ((up + i) >> 1))+=1;
	}
	mx = -1;
	for (j = 0; j < height; j++)
	{
		if (*(ColMidpoint + j)>mx)
		{
			mx = *(ColMidpoint+j);
			y = j;
		}
	}
	printf("%d %d\n", y, x);
	int R_num = 2 * error / RStep,k;
	int *count = new int[R_num + 1];
	memset(count, 0, (R_num + 1) * 4);
	int tmp_r;
	double t;
	//统计各个半径圆过白点数量
	for (k = 0; k <= R_num; k++)
	{
		tmp_r = R - error + k*RStep;
		//printf("%d ", tmp_r);
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (*(pImg + i*width + j) == 255)
				{
					t = sqrt((double)(i - y)*(i - y) + (j - x)*(j - x)) - tmp_r;
					if (t < ex&&t>-ex)
					{
					//	printf("%d %d %d %d ;", k, i, j, *(count + k));
					//	system("pause");
						*(count + k) += 1;
					}
				}
			}
		}
	}
	mx = -1;
	printf("\n");
	//选取过白点最多的圆半径
	for (k = 0; k <= R_num; k++)
	{
		if (*(count + k)>mx)
		{
			mx = *(count + k);
			i = k;
		}
	}
	r = R - error + i*RStep;
	printf("%d\n", r);
}