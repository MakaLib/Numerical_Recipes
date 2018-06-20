#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define abs(X) ((X) > 0 ? (X) : -(X)) 

void MacXVec(int n, double A[][n], double V[], double result[])
{
	int i,j;
	
	for(i = 0; i < n; i++)
	{
		result[i] = 0;
		for(j = 0; j < n; j++)
		{
			result[i] += A[i][j] * V[j];
		}
	}
}

double VecXVec(int n, double V1[], double V2[])
{
	double result = 0;
	int i,j;

	for(i = 0; i < n; i++)
	{
		result += V1[i] * V2[i];
	}
	return result;
}

void MacXMac(int n, double A[][n], double B[][n], double R[][n], int trans)
{
	int i,j,k;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			R[i][j] = 0;
			for(k = 0; k < n; k++)
			{	if(!trans)
				{
					R[i][j] += A[i][k] * B[k][j];
				}
				else
				{
					R[i][j] += A[k][i] * B[k][j];
				}
				
			}
		}
	}

}




int main()
{
	int n = 7;
	int IT_MAX = 12;
	int i,j,k;

	double lambda = 0.0;

	double A[n][n];
	double W[n][n];
	double X[n][n];
	double Temp[n][n];
	double D[n][n];

	double x[n];
	double temp[n];

	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	fp1 = fopen("dane.dat", "w");
	fp2 = fopen("macierz.dat", "w");
	fp3 = fopen("lambda.dat", "w");

	for(i = 0; i < n; i++)
	{

		for(j = 0; j < n; j++)
		{
			A[i][j] = 1.0/sqrt(2. + abs(i-j));
			W[i][j] = A[i][j];
		}
	}
	

	for(k = 0; k < n; k++)
	{
		for(i = 0; i < n; i++)
		{
			x[i] = 1.0;
		}
		
		fprintf(fp3,"%d ", k);
		for(i = 0; i < IT_MAX; i++)
		{
			MacXVec(n,W,x,temp);
			lambda = VecXVec(n,temp,x)/VecXVec(n,x,x);
			double norma = sqrt(VecXVec(n,temp,temp));
			printf("%d %d %g %g\n", k, i, lambda,norma);
			fprintf(fp1,"%d %d %g\n", k, i, lambda);
			for(j = 0; j < n; j++)
			{
				x[j] = temp[j]/norma;
			}
		}
		fprintf(fp3,"%d %f\n",k, lambda);

		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				W[i][j] -= lambda *x[i] * x[j];
			}
		}

		for(i = 0; i < n; i++)
		{
			X[i][k] = x[i];
		}
	}

	MacXMac(n,A,X,Temp,0);
	MacXMac(n,X,Temp,D,1);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%g  ", D[i][j]);
			fprintf(fp2,"%g  ", D[i][j]);
		}
		printf("\n");
		fprintf(fp2,"\n");
	}







	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}