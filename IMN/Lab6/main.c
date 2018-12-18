#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mgmres.h"



double p1(double x, double xmax, double y, double ymax)
{
	double sigma = xmax/10.0;
	double fexp = pow(x - 0.25 * xmax,2)/pow(sigma,2);
	double sexp = pow(y - 0.5 * ymax,2) / pow(sigma,2);
	return exp(-fexp-sexp);
}

double p2(double x, double xmax, double y, double ymax)
{
	double sigma = xmax/10.0;
	double fexp = pow(x - 0.75 * xmax,2)/pow(sigma,2);
	double sexp = pow(y - 0.5 * ymax,2) / pow(sigma,2);
	return (-1.0) * exp(-fexp-sexp);
}

double EL(double e1, double e2, int i, int nx)
{
	return i <= nx/2 ? e1 : e2;
}


void Potencjal(int nx, int ny, FILE *fmacierz, FILE *fwektor, FILE *fdane, int flag, double eps1, double eps2)
{
	double DETLA = 0.1;
	double V1, V2, V3, V4;
	if(flag == 0)
	{
		V1 = 10.0;
		V2 = -10.0;
		V3 = 10.0;
		V4 = -10.0;
	}
	else
	{
		V1 = V2 = V3 = V4 = 0.0;
	}
	int N = (nx + 1) * (ny + 1);
	double p = 0.0;

	double a[5*N];
	int ja[5*N];
	int ia[N+1];
	for(int i = 0; i < N+1; i++)
		ia[i] = -1;


	double b[N];
	double V[N];
	int i,j;

	int k = -1;

	for(int l = 0; l < N; l++)
	{
		int brzeg = 0;
		double vb = 0.0;
		j = floor(l/(nx+1));
		i = l - j * (nx+1); 

		if(i == 0)
		{
			brzeg = 1;
			vb = V1;
		}

		if(j == ny)
		{
			brzeg = 1;
			vb = V2;
		}

		if(i == nx)
		{
			brzeg = 1;
			vb = V3;
		}

		if(j == 0)
		{
			brzeg = 1;
			vb = V4;
		}


		//wypelianmy od razu wektor wyrazow wolnych
		if(flag == 0)
			b[l] = -(p+p);
		else
		{
			double x = p1(i*DETLA, nx*DETLA, j * DETLA, ny * DETLA);
			double y = p2(i*DETLA, nx*DETLA, j * DETLA, ny * DETLA);
			b[l] = -(x+y);
		}

		//wymuszamy wartosc potencjalu na brzegu
		if(brzeg == 1)
		{
			b[l] = vb;
		}

		//wypelniamy elemetny macierzy A

		ia[l] = -1; // wkaznik do pierwszego el w wierszu

		//lewa skrajna przekatna
		if(l-nx-1 >= 0 && brzeg == 0)
		{
			k++;
			if(ia[l] < 0)
				ia[l] = k;
			a[k] = EL(eps1, eps2, i, nx)/pow(DETLA,2);
			ja[k] = l-nx-1;
		}

		//poddiagnalna
		if( l -1 >= 0 && brzeg == 0)
		{
			k++;
			if(ia[l] < 0)
				ia[l] = k;
			a[k] = EL(eps1,eps2,i,nx)/pow(DETLA,2);
			ja[k] = l-1;
		}

		//diagonala
		k++;
		if(ia[l] < 0)
			ia[l] = k;
		if(brzeg == 0)
		{
			int j1 = floor((l+1) / (nx+1));
			int j2 = floor((l+nx+1) / (nx+1));
			int i1 = (l+1) - j1 *(nx+1);
			int i2 = (l+nx+1) - j2 * (nx + 1);
			a[k] = - (2 * EL(eps1,eps2,i,nx) + EL(eps1,eps2,i1,nx) + EL(eps1,eps2,i2,nx))/pow(DETLA,2);

		}
		else 
			a[k] = 1;
		ja[k] = l;


		//naddiagonala
		if(l < N && brzeg == 0)
		{
			k++;
			int j1 = floor((l+1) / (nx+1));
			int i1 = (l+1) - j1 *(nx+1);
			a[k] = EL(eps1,eps2,i1,nx)/pow(DETLA,2);
			ja[k] = l+1;
		}

		//prawa skrajna przekatna
		if(l < N - nx - 1 && brzeg == 0)
		{
			k++;
			int j2 = floor((l+nx+1) / (nx+1));
			int i2 = (l+nx+1) - j2 * (nx + 1);
			a[k] = EL(eps1,eps2,i2,nx)/pow(DETLA,2);
			ja[k] = l+nx+1;
		}

		if(nx == 4)
		{
			fprintf(fmacierz, "%d %d %d %g\n",l, i, j, a[l] );
			fprintf(fwektor, "%d %d %d %g\n",l,i,j,b[l] );
		}


	}
	int nz_num = k+1;
	ia[N] = nz_num;
	if(nx == 4) 
	{
		fprintf(fmacierz, "\n\n");
		fprintf(fwektor, "\n\n");
	}

	pmgmres_ilu_cr(N, nz_num, ia, ja, a, V, b, 500, 500, pow(10,-8), pow(10,-8));

	if(nx != 4)
	{
		for( int i = 0; i <= nx; i++)
		{
			for( int j = 0; j <= ny; j++)
			{
				int l = i + j * (nx+1);
				fprintf(fdane, "%g %g %g\n",i*DETLA, j*DETLA, V[l]);
			}
			fprintf(fdane, "\n" );
		}

		fprintf(fdane, "\n\n");
	}


}

int main()
{


	
	FILE *fmacierz, *fwektor, *fdane;
	fmacierz = fopen("macierz.dat" , "w");
	fwektor = fopen("wektor.dat", "w");
	fdane = fopen("dane.dat", "w");
	

	//I
	Potencjal(4,4, fmacierz, fwektor, fdane,0,1.0,1.0);
	Potencjal(50,50, fmacierz, fwektor, fdane,0, 1.0, 1.0);
	Potencjal(100,100, fmacierz, fwektor, fdane,0, 1.0, 1.0);
	Potencjal(200,200, fmacierz, fwektor, fdane,0, 1.0, 1.0);

	//II
	Potencjal(100,100, fmacierz, fwektor, fdane,1, 1.0, 1.0);
	Potencjal(100,100, fmacierz, fwektor, fdane,1, 1.0, 2.0);
	Potencjal(100,100, fmacierz, fwektor, fdane,1, 1.0, 10.0);

	fclose(fmacierz);
	fclose(fwektor);
	fclose(fdane);

	


	return 0;
}