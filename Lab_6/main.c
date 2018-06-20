#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double complex oblicz(int n, double complex A[n], double complex B[n], double complex zj, int l)
{
	B[l] = 0;
	int k;
	for( k = l - 1; k >= 0; k--)
	{
		B[k] = A[k+1] + zj * B[k+1];
	}

	return A[0] + zj * B[0]; 

}

int main()
{
	int n = 4;
	int IT_MAX = 20;
	int l,k,j;

	double complex A[n+1];
	double complex B[n+1];
	double complex C[n+1];
	double complex z,R,R_prim,zj;

	FILE *fp1;
	fp1 = fopen("dane.dat", "w");

	A[0] = 16.0 + 8.I;
	A[1] = -20.0 + 14.I;
	A[2] = 4.0 - 8.I;
	A[3] = -4.0 + 1.I;
	A[4] = 1.0 + 0.I;
	z = 0.0 + 0.I;

	for(l = n; l >= 1; l--)
	{
		zj = z;

		for(j = 1; j <= IT_MAX; j++)
		{
			fprintf(fp1,"%.4f %.4f %d %d %.4f %.4f\n",creal(z), cimag(z), l,j,creal(zj), cimag(zj));
			R = oblicz(n,A,B,zj,l);
			R_prim = oblicz(n,B,C,zj,l-1);
			zj = zj - R/R_prim;
			printf("%d %d %f %f\n", l,j,creal(zj), cimag(zj));
		}
		fprintf(fp1,"\n");

		for(k = 0; k <= n ; k++)
		{
			A[k] = B[k];
		}
	}


	printf("\n\nDruga\n\n");
	fclose(fp1);
	fp1 = fopen("dane1.dat", "w");

	A[0] = 16.0 + 8.I;
	A[1] = -20.0 + 14.I;
	A[2] = 4.0 - 8.I;
	A[3] = -4.0 + 1.I;
	A[4] = 1.0 + 0.I;
	z = -10.0 - 10.I;

	for( k = 0; k<= n; k++)
	{
		B[k] = 0;
		C[k] = 0;
	}

	for(l = n; l >= 1; l--)
	{
		zj = z;

		for(j = 1; j <= IT_MAX; j++)
		{
			fprintf(fp1,"%.4f %.4f %d %d %.4f %.4f\n",creal(z), cimag(z), l,j,creal(zj), cimag(zj));
			R = oblicz(n,A,B,zj,l);
			R_prim = oblicz(n,B,C,zj,l-1);
			zj = zj - R/R_prim;
			printf("%d %d %f %f\n", l,j,creal(zj), cimag(zj));
			
		}
		fprintf(fp1,"\n");

		for(k = 0; k < n; k++)
		{
			A[k] = B[k];
		}
	}
	fclose(fp1);



	return 0;
}