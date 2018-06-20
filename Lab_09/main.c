#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

double dcos(int x)
{
	if(x%2) return 0;
	else return pow(-1,x/2);

}

double silnia(double x)
{
	if(x == 1 || x == 0) return 1.;
	else return x * silnia(x-1);
}





int main()
{
	int N = 2;
	int M = N;
	int n = N + M;

	gsl_vector *c = gsl_vector_calloc(n+1);
	gsl_vector *a = gsl_vector_calloc(N+1);
	gsl_vector *b = gsl_vector_calloc(M + 1);
	gsl_vector *x = gsl_vector_calloc(M);
	gsl_vector *y = gsl_vector_calloc(M);
	gsl_matrix *A = gsl_matrix_calloc(M,M);
	gsl_permutation *p = gsl_permutation_calloc(M);

	FILE *fp;
	fp = fopen("dane.dat", "w");
	int i,j;
	for(i = 0; i <=n; i++)
	{
		
		gsl_vector_set(c,i,dcos(i)/silnia(i));
		printf("%f ",gsl_vector_get(c,i));
	}

	printf("\n\n");

	for(i = 0; i < M; i++)
	{
		for(j = 0; j < M; j++)
		{
			gsl_matrix_set(A,i,j,gsl_vector_get(c,N-M+i+j+1));
			printf("%f ",gsl_matrix_get(A,i,j));
		}
		printf("\n");
	}
	printf("\n");

	for(i = 0; i < M; i++)
	{
		gsl_vector_set(y,i,-gsl_vector_get(c,N+1+i));
		printf("%f ",gsl_vector_get(y,i));
	}

	int signum;
	gsl_linalg_LU_decomp(A,p,&signum);
	gsl_linalg_LU_solve(A,p,y,x);

	
	printf("\n Wektor B\n");
	for(i = 0; i < M; i++)
	{
		gsl_vector_set(b,M-i,gsl_vector_get(x,i));
	}
	gsl_vector_set(b,0,1);

	for(i = 0; i <= M; i++)
	{
		
		printf("%f ",gsl_vector_get(b,i));
	}
	//gsl_vector_set(b,M,gsl_vector_get(x,i));
	printf("\n Wektor A\n");
	for(i = 0; i <= N; i++)
	{
		double sum = 0.0;
		for(j = 0; j <= i; j++)
		{
			sum += gsl_vector_get(c,i-j) * gsl_vector_get(b,j);
		}
		gsl_vector_set(a,i,sum);
		printf("%f ",gsl_vector_get(a,i));
	}
	printf("\n");

	double ii;
	double x_min = -5;
	double x_max = 5;
	for(ii = x_min ; ii <= x_max; ii+=0.1)
	{
		double sum_a = 0.0;
		double sum_b = 0.0;
		for(i = 0; i <=N; i++) sum_a += gsl_vector_get(a,i) * pow(ii,i);
		for(i = 0; i <= M; i++) sum_b += gsl_vector_get(b,i) * pow(ii,i);
		fprintf(fp,"%f %f %f %f\n", ii, cos(ii),ii,sum_a/sum_b);
	}

	gsl_matrix_free(A);
	gsl_vector_free(c);
	gsl_vector_free(a);
	gsl_vector_free(b);
	gsl_vector_free(x);
	gsl_vector_free(y);
	gsl_permutation_free(p);

	fclose(fp);

	return 0;
}