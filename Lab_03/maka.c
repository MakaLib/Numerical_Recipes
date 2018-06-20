#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

#define max(X,Y) ((X)>(Y)?(X):(Y))
#define min(X,Y) ((X)<(Y)?(X):(Y))
#define abs(X) ((X)>0?(X):-(X))

void MatrixXVector( int n, int m, double A[n][n],  double *x, double *result)
{
	int i,j;
	for(i = 0; i < n; i++)
	{
		result[i] = 0.0;
		int jmin = max(0,i-m);
		int jmax= min(i+m,n-1);
		for(j = jmin; j <= jmax; j++)
		{
			result[i] += (A[i][j] * x[j]);
		}
	}
}

void Substract( int n,  double *b,  double *A, double *r)
{
	int i;
	for(i = 0; i < n; i++)
	{
		r[i] = (b[i] - A[i]);
	}
}

double VecXVec( int n,  double *r1,  double *r2)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < n; i++)
	{
		sum += (r1[i] * r2[i]);
	}
	return sum;
}

void NumberXVec(int n, double alfa, double *r, double *temp)
{
	int i;
	for(i = 0; i < n; i++)
	{
		temp[i] = (alfa	* r[i]);
	}
}

void SumVecotr(int n, double *x1, double *x2, double *result)
{
	int i;
	for(i = 0; i < n; i++)
	{
		result[i] = (x1[i] + x2[i]);
	}
}
void gauss(double** A, double* b, double* x) {
	int i, j, k;
	double wsp = 0;
	for (i = 0; i < N; i++) {
		wsp = A[i][i];
		for (j = i; j < N; j++) {
			A[i][j] /= wsp;
		}
		b[i] /= wsp;
		for (k = i + 1; k < N ; k++) {
			wsp = A[k][i];
			for (j = i; j < N; j++) {
				if (A[i][j] != 0) {
					A[k][j] -= A[i][j] * wsp;
				}
			}
			b[k] -= b[i] * wsp;
		}
	}
	for (i = N-1; i >= 0; i--) {
		for (k = i - 1; k >= 0; k--) {
			wsp = A[k][i];
			for (j = i; j < N; j++) {
				if (A[i][j] != 0) {
					A[k][j] -= A[i][j] * wsp;
				}
			}
			b[k] -= b[i] * wsp;
		}
	}
	for(i = 0; i < N-1; i++)
		for(j = 0; j < N-1; j++) A[i][j] = A[i+1][j+1];
	for (i = 0; i < N; i++) {
		x[i] = b[i];
	}
	}


int main()
{

	int n = 1000;
	int m = 5;
	int i = 0,j= 0;
	int k = 0;
	double alfa;
	//double A[n][n];
	double **A = malloc(n*sizeof(double*));
	for(i = 0; i < n; i++) A[i] = malloc(n*sizeof(double));
	double b[n];
	double x[n];
	double r[n];

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			
			if(abs(i-j) <= m)
			{
				A[i][j] = 1.0/(1+abs(i-j));
			}
			else A[i][j] = 0;
		}
		b[i] = i;
		x[i] = 1;

	}

	//petla do...while
	double temp[n];

	FILE *fp;
	fp = fopen("wynik.dat", "w");
	time_t t1,t2;
	double t21;
	time(&t1);


/*	do
	{ 
		fprintf(fp, "%d", k);
		printf(" %d ", k);
		
		printf("norm: %f\n", sqrt(VecXVec(n, r, r)));

		MatrixXVector(n,m,A,x,temp);
		Substract(n,b,temp,r);

		MatrixXVector(n,m,A,r,temp);
		alfa = VecXVec(n,r,r)/VecXVec(n,r,temp);
		printf("%f ", alfa);

		NumberXVec(n,alfa,r,temp);
		SumVecotr(n,x,temp,x);
		fprintf(fp, " %f", sqrt(VecXVec(n, x, x)));
		fprintf(fp,"\n");



		k++;
	}while(sqrt(VecXVec(n,r,r)) > pow(10, -6));*/
	
	gauss(A,b,x);

	time(&t2);
	t21 = difftime(t2,t1);
	printf("\n\nCzas: %f\n\n",t21);


	return 0;
}