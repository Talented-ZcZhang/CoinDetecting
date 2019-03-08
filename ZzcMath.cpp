const double pi=3.14159265358979;
const double _2_pi = 6.2831853072;
const double _pi_div_2 = 1.5707963268;
double ZzcCos(double x,int N)
{
	int f=1;
	if(x<0){
		x=-x;
	}
	if(x>_2_pi)
	{
		while(x>=_2_pi)
		{
			x-=_2_pi;
		}
	}
	if(x>pi)
	{
		x-=pi;
		f^=(-2);
	}
	if(x>_pi_div_2)
	{
		x=pi-x;
		f^=(-2);
	}
	double _1_div_factorial[]={
	0.500000000000000000000000000000,
	0.041666666666666664000000000000,
	0.001388888888888888900000000000,
	0.000024801587301587302000000000,
	0.000000275573192239858880000000,
	0.000000002087675698786810000000,
	0.000000000011470745597729725000,
	0.000000000000047794773323873853,
	0.000000000000000156192069685862,
	0.000000000000000000411031762331
	};
	double result=1, x_2 = x*x,x_n=x_2;
	bool flag=true;
	for(int i=0;i<N;i++)
	{
		if(flag)
		result-=(x_n*_1_div_factorial[i]);
		else 
		result+=(x_n*_1_div_factorial[i]);
		x_n*=x_2;
		flag^=1;
	}
	return (f*result);
}
double ZzcSin(double x,int N)
{
	int f=1;
	if(x<0){
		x=-x;
		f^=(-2);
	}
	if(x>_2_pi)
	{
		while(x>=_2_pi)
		{
			x-=_2_pi;
		}
	}
	if(x>pi)
	{
		x-=pi;
		f^=(-2);
	}
	if(x>_pi_div_2)
	{
		x=pi-x;
	}
	double _1_div_factorial[]={
	1.000000000000000000000000000000,
	0.166666666666666660000000000000,
	0.008333333333333333200000000000,
	0.000198412698412698410000000000,
	0.000002755731922398589300000000,
	0.000000025052108385441720000000,
	0.000000000160590438368216130000,
	0.000000000000764716373181981640,
	0.000000000000002811457254345521,
	0.000000000000000008220635246624,
	};
	double result=0, x_2 = x*x,x_n=x;
	bool flag=true;
	for(int i=0;i<N;i++)
	{
		if(flag)
		result+=(x_n*_1_div_factorial[i]);
		else 
		result-=(x_n*_1_div_factorial[i]);
		x_n*=x_2;
		flag^=1;
	}
	return (f*result);

}