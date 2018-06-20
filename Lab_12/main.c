#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f1(double x)
{
	x = x + 0.0000001;
	double wynik = sin(x)/x;
	return wynik;
}

double f2(double x)
{	
	x += 0.0000001;
	double wynik = (cos(x) - exp(x))/sin(x);
	return wynik;
}

double f3(double x)
{
	x += 0.0000001;
	double wynik = 1.0/(x * exp(1.0/x));
	return wynik;
}

void licz(int n,double D[n][n])
{
	int i,k;
	for(int k = 1; k < n; k++)
	{
		for(i = k; i < n; i++)
		{
			D[i][k] = (pow(4,k) * D[i][k-1] - D[i-1][k-1])/(pow(4,k) - 1);
		}
	}
}

void uzupelnij(double a,double b, int n, double D[n][n], int tryb)
{
	int i,j;
	for(i = 1; i < n; i++)
	{
		double suma = 0;
		double hn = (b-a)/pow(2,i);
		for(j = 1; j <= pow(2,i-1);j++)
		{
			if(tryb == 1) suma += f1(a+(2.*j-1)*hn);
			if(tryb == 2) suma += f2(a+(2.*j-1)*hn);
			if(tryb == 3) suma += f3(a+(2.*j-1)*hn);
		}
		D[i][0] = 1./2 * D[i-1][0] +hn*suma;
	}
}

void wypisz(int n, double D[n][n])
{
	int i,j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%f ",D[i][j]);
		}
		printf("\n");
	}
}


int main()
{

	FILE *fp;
	fp = fopen("jeden.dat", "w");
	int n = 8;

	double D[n][n];

	int i,j,k;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			D[i][j] = 0;
	double a = 0., b = 1.;

	double hn = (double)(b-a)/pow(2,n);
	D[0][0] = (double)((f1(a) + f1(b))/2. * (b-a));
	uzupelnij(a,b,n,D,1);
	licz(n,D);
	wypisz(n,D);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(D[i][j] != 0.0) fprintf(fp,"%f ",D[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	fp = fopen("dwa.dat","w");
	
	printf("\n\n\n");
	n = 16;
	a = -1.;
	b = 1.;
	double D1[n][n];

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			D1[i][j] = 0.0;

	D1[0][0] = (double)((f2(a) + f2(b))/2. * (b-a));
	uzupelnij(a,b,n,D1,2);
	licz(n,D1);
	wypisz(n,D1);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(D1[i][j] != 0.0) fprintf(fp,"%f ",D1[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	fp = fopen("trzy.dat","w");

	printf("\n\n\n");
	n = 8;
	a = 0.;
	b = 1.;
	double D3[n][n];

	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			D3[i][j] = 0.0;

	D3[0][0] = ((f3(a) + f3(b))/2. * (b-a));
	uzupelnij(a,b,n,D3,3);
	licz(n,D3);
	wypisz(n,D3);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(D3[i][j] != 0.0) fprintf(fp,"%f ",D3[i][j]);
		}
		fprintf(fp,"\n");
	}



	return 0;
}