#ifndef BMP_FILE_H
#define BMP_FILE_H

BYTE *RmwRead8BitBmpFile2Img(const char * filename,int *width,int *height);
bool RmwWriteByteImg2BmpFile(BYTE *pImg,int width,int height,const char * filename);

BYTE *RmwRead24BitBmpFile2Img(const char * filename,int *width,int *height);
bool RmwWrite24BitImg2BmpFile(BYTE *pImg,int width,int height,const char * filename);

void ZzcBinaryzation(BYTE*pImg,int width,int height,int threshold);

void CalIntergal(BYTE* pImg,int width,int height,long long*Intergal);
void ZzcCutImg(BYTE *pImg, int width, int height, int x1, int y1, int x2, int y2, BYTE *pResImg);
void ZzcRGB2GRAY(BYTE *pImg, int width, int height, BYTE* pResImg);

void ZzcRGBShrink(BYTE *pImg, int width, int height,int mag, BYTE*pResImg);
void ZzcGRAYShrink(BYTE *pImg, int width, int height, int mag, BYTE *pResImg);
#endif
