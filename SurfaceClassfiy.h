#ifndef _SurfaceClassfiy_H
#define _SurfaceClassfiy_H
//#pragma once
#include "zzc_bp_net.h"
class Sample_Feature_Vec{
public:
	BYTE *pSample;
	double *pTarget;
	int length;
	int Sam_Num;
	int Cla_Num;
	int Tar_Num;
	void Init();
	bool Read();
};

class SurfaceClassfiy
{
public:
	Sample_Feature_Vec sam;
	bp_alg_core_params* core_params;
	void Init();
	void train();
	void Reconise();
};
void CreateFeatureVec(BYTE*pColor, int color_width, int color_height, BYTE*pEdge, int edge_width, int edge_height, BYTE*Vec);
void TransformBYTE2Double(BYTE *src, double*dst, int num);
#endif