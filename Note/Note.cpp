
#include <stdio.h>
#include <math.h>


float M_PI = 3.14;

int inv(int m)
{
	int result = 0;
	for (int i = 0; i < 5; ++i)
	{
		result = result * 10 + m % 10;
		m /= 10;
	}
	return result;
}

float f(float x)
{
	return x * x + 2 * x + 1;
}

float gf(float x,float y)
{
	return (f(x) + f(y)) * (f(x) - f(y));
}

int main()
{
	int ia; 
	float a, b, c, d, e, f, g, o1, o2;
	scanf("%f %f %f %f", &a, &b, &c, &d);


	o1 = (gf(a, b) - gf(c, d)) / (gf(a, b) + gf(c, d));


	printf("%.2f", o1);
	//printf("%.2f%.2f", o1, o2);

	return 0;
}
