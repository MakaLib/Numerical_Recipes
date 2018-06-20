#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f(double x)
{
	return exp(-x*x);
}


double Wn(int n, double X[n+1], double x, int check)
{
	int j;
	double value = 1;

	for(j = 0; j <=n; j++)
	{
		if(j != check)
		{
			value *= x - X[j];
		}
	}

	return  value;

}

double Lagrange(int n, double X[n+1], double Y[n+1],double x)
{
	double value = 0;
	int i;
	for( i = 0; i <= n; i++)
	{
		value += Y[i] * Wn(n,X,x,i) / Wn(n,X,X[i],i);
	}

	return value;
}

double Czebyszew(int min, int max, int n, int m)
{
	return  1./2. * ((max - min) * cos(3.14 * (2. * (m) +1.)/(2.*n+2.)) + (min + max));
}




int main()
{
	double min = -5;
	double max = 5;

	int k = 200;

	FILE *fp[4];
	fp[0] = fopen("dane.dat", "w");
	fp[1] = fopen("dane1.dat", "w");
	fp[2] = fopen("dane2.dat", "w");
	fp[3] = fopen("dane3.dat", "w");

	int n,i;
	double x;
	int j = 0;


	for(n = 5; n <= 20; n += 5)
	{
		double X[n+1];
		double Y[n+1];

		for(i = 0; i <= n ; i++)
		{
			X[i] = 0;
			Y[i] = 0;
		}

		double step = (max-min)/n;
		double temp_value = min;
		for(i = 0; i <= n; i ++)
		{
			X[i] = temp_value;
			Y[i] = f(temp_value);
			temp_value += step;
		}

		temp_value = min;
		step = (max- min)/ k;
		for(i = 0; i <= k; i++)
		{
			fprintf(fp[j],"%d %f %f %f %f\n",n,temp_value,f(temp_value),temp_value, Lagrange(n,X,Y,temp_value));
			temp_value += step;
		}

		j++;


	}

	for(i = 0; i < 4; i++) fclose(fp[i]);



	fp[0] = fopen("danecz.dat", "w");
	fp[1] = fopen("dane1cz.dat", "w");
	fp[2] = fopen("dane2cz.dat", "w");
	fp[3] = fopen("dane3cz.dat", "w");

	
	j = 0;


	for(n = 5; n <= 20; n += 5)
	{
		double X[n+1];
		double Y[n+1];

		for(i = 0; i <= n ; i++)
		{
			X[i] = Czebyszew(min,max,n,i);
			Y[i] = f(X[i]);
		}

		double step = (max-min)/n;
		double temp_value = min;
		/*for(i = 0; i <= n; i ++)
		{
			X[i] = temp_value;
			Y[i] = f(temp_value);
			temp_value += step;
		}*/

		temp_value = min;
		step = (max- min)/ k;
		for(i = 0; i <= k; i++)
		{
			fprintf(fp[j],"%d %f %f %f %f\n",n,temp_value,f(temp_value),temp_value, Lagrange(n,X,Y,temp_value));
			temp_value += step;
		}

		j++;


	}

	for(i = 0; i < 4; i++) fclose(fp[i]);



	return 0;
}