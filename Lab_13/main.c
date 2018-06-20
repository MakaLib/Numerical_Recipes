#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"
#include "gauher.c"
#include "gauleg.c"
#include "gammln.c"
#include "gaulag.c"
#include "nrutil.c"

double c1(double x)
{
	double wynik = 1./((double)(x * sqrt(pow(x,2)-1)));
	return wynik;
}

double c2(double x)
{
	return log(fabs(x));
}

double c22(double x)
{
	return log(x) * exp(-x*x);
}

double c3(double x)
{
	return sin(2*x) * exp(-2*x);
}

double g(double x)
{
	return (log(x) * exp(-pow(x,2)));
}


int main()
{
	int n;
	float dok1 = M_PI/3;
	FILE *fp1;
	fp1 = fopen("dane1.dat","w");
	printf("\n====1===\n");
	for(n = 2; n <=100; n++)
	{
		float *x = malloc((n+1) * sizeof(float));
		float *w = malloc((n+1) * sizeof(float));
		gauleg(1.,2.,x,w,n);
		int i;
		float c = 0;
		for(i = 1; i <= n; i++)
		{
			c += c1(x[i]) * w[i];
		}
		printf("%f %d\n",c,n);
		fprintf(fp1, "%d %f\n",n,fabs(c - dok1));
		free(x);
		free(w);
	}

	printf("\n\n====2===\n");
	fclose(fp1);
	printf("\n\n");
	float dok2a = -0.8700577;
	fp1 = fopen("dane2a.dat","w");
	for(n = 2; n <=100; n+=2)
	{
		float *x = malloc((n+1) * sizeof(float));
		float *w = malloc((n+1) * sizeof(float));
		gauher(x,w,n);
		int i;
		float c = 0;
		for(i = 1; i <= n; i++)
		{
			c += c2(x[i]) * w[i];
		}
		c = c/2.;
		printf("%f %d\n",c,n);
		fprintf(fp1, "%d %f\n",n,fabs(c - dok2a));
		free(x);
		free(w);
	}
	fclose(fp1);

	printf("\n\n====2b===\n");
	float dok2b = -0.8700577;
	fp1 = fopen("dane2b.dat","w");
	for(n = 2; n <=100; n++)
	{
		float *x = malloc((n+1) * sizeof(float));
		float *w = malloc((n+1) * sizeof(float));
		gauleg(0.0,5.0,x,w,n);
		int i;
		float c = 0;
		for(i = 1; i <= n; i++)
		{
			c += c22(x[i]) * w[i];
		}
		printf("%f %d\n",c,n);
		fprintf(fp1, "%d %f\n",n,fabs(c - dok2b));
		free(x);
		free(w);
	}
	fclose(fp1);

	fp1 = fopen("gx.dat","w");
	double k;
	for(k = 0.01;k<=2.5; k+=0.005)
	{
		fprintf(fp1, "%f %f\n",k,g(k));
	}
	fclose(fp1);

	printf("\n\n====3===\n");
	float dok3 = 2./13.;
	fp1 = fopen("dane3.dat","w");
	for(n = 2; n <=10; n++)
	{
		float *x = malloc((n+1) * sizeof(float));
		float *w = malloc((n+1) * sizeof(float));
		gaulag(x,w,n,0.0);
		int i;
		float c = 0;
		for(i = 1; i <= n; i++)
		{
			c += c3(x[i]) * w[i];
		}
		printf("%f %d\n",c,n);
		fprintf(fp1, "%d %f\n",n,fabs(c - dok3));
		free(x);
		free(w);
	}
	fclose(fp1);



	return 0;
}