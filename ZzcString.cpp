#include <cstdio>
int ZzcStrLength(char *pStr)
{
	int i;
	for ( i = 0; *(pStr++); i++);
	return i;
}
int ZzcFind_Back(char *pStr,int length, char c)
{
	char*pCur = pStr + length;
	for (int i = length - 1; i >= 0; i--)
	{
		if (*(--pCur) == c)return i+1;
	}
	return -1;
}
void ZzcCutString(char* pStr, int length,char *pResStr, int begin,int end)
{
	if (begin <= 0 || end > length)return;
	char *pEnd = pStr + end,*pCur=pStr+begin-1;
	while (pCur < pEnd)
	{
		*(pResStr++) = *(pCur++);
	}
	*pResStr = '\0';
}
void ZzcMergeString(char *pStr1, int length1, char *pStr2, int length2,char *pResStr)
{
	char *pEnd = pStr1 + length1;
	while (pStr1<pEnd)
	{
		*(pResStr++) = *(pStr1++);
	}
	pEnd = pStr2 + length2;
	while (pStr2 < pEnd)
	{
		*(pResStr++) = *(pStr2++);
	}
	*(pResStr) = '\0';
}
void ZzcNum2char(long long num, char*Str)
{
	if (num == 0)
	{
		*Str = '0' + num;
		*(Str + 1) = '\0';
		return;
	}
	int t[100],*t1=t,c=0;
	while (num)
	{
		*(t1++) = num % 10;
		num /= 10;
		c++;
	}
	t1--;
	while (t1 >= t)
	{
		*(Str++) = *(t1--) + '0';
	}
	*Str = '\0';
}