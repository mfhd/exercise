#include <stdio.h>
#define stp 1000000

float f(float x, int a, int b, int c, int d)
{
	return(a + b*x + c*x*x + d*x*x*x);
}

float calcNewton(float l,float r,int a,int b,int c,int d)
{
	if (l == r) 
		return(0.0);
	else if (l > r) 
	{
		float tmp = l;
		l = r;
		r = tmp;
	}
	float delta = ((r - l) / (float)stp);
	float A;
	float x = l + delta;
	int i = 2;

	while(i < (2 * stp) - 2)
	{
		i = i + 2;
		A += f(x,a,b,c,d);
		x += delta;
	}
	A *= 2.0;
	x = l + (0.5 * delta);
	i = 1;

	while(i < (2 * stp) - 1)
	{
		i += 2;
		A += f(x,a,b,c,d);
		x += delta;
	}
	A *= 2.0;
	A += f(l,a,b,c,d) + f(r,a,b,c,d);
	A *= (0.5 * delta / 3);

	return(A);
}
