#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

double fx(double x)
{
	//return cos(2*x);
	return 1./(1+x*x);
}




double s(double x, double h, int n, double c[n+2],double *xw)
{
	double sx = 0.0; 
	int i;

	for(i = 0; i <= n+1; i++)
	{
		double y = 0.0;
		if(x >= xw[i-2] && x < xw[i-1]) y = pow(x - xw[i-2],3);
		else if(x >= xw[i-1] && x < xw[i]) y = pow(h,3) + 3*pow(h,2) * (x-xw[i-1]) + 3*h*pow(x - xw[i-1],2) - 3*pow(x-xw[i-1],3);
		else if(x >=xw[i] && x<xw[i+1]) y = pow(h,3) + 3*pow(h,2)*(xw[i+1]-x) + 3*h*pow(xw[i+1]-x,2) - 3*pow(xw[i+1] - x,3);
		else if(x>= xw[i+1] && x < xw[i+2]) y = pow(xw[i+2] - x,3);

		y = y/pow(h,3);
		sx = sx + c[i]*y;

	}
	return sx;
}


int main()
{

	double x_min = -5;
	double x_max = 5;
	double h;
	int n = 20;
	double xx[n+6];
	double *xw = (double*) malloc((n+6) * sizeof(double));
	xw = &xx[2];

	gsl_matrix *A = gsl_matrix_calloc(n,n);
	//gsl_vector *x = gsl_vector_calloc(n);
	gsl_vector *y = gsl_vector_calloc(n);
	gsl_vector *c = gsl_vector_calloc(n);
	gsl_permutation *p = gsl_permutation_calloc(n);

	double cc[n+2];

	h = (x_max - x_min)/(n-1);
	int i,j;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(i == j) gsl_matrix_set(A,i,j,4);
			else if(j+1 == i || j-1 == i) gsl_matrix_set(A,i,j,1);
			else gsl_matrix_set(A,i,j,0);
		}
	}

	gsl_matrix_set(A,0,1,2);
	gsl_matrix_set(A,n-1,n-2,2);

	for(i = -2; i <= (n+3); i++)
	{
		xw[i] = x_min + h * (i-1);
	}

	for(i = 0; i < n; i++)
	{
		gsl_vector_set(y,i,fx(xw[i+1]));
	}

	double dx = 0.01;
	double alfa = (fx(x_min + dx) - fx(x_min - dx)) / (2*dx);
	double beta= (fx(x_max + dx) - fx(x_max - dx)) / (2*dx);
	gsl_vector_set(y,0,fx(xw[1]) + h/3 * alfa);
	gsl_vector_set(y,n-1,fx(xw[n]) - h/3 * beta);

	int signum;
	gsl_linalg_LU_decomp(A,p,&signum);
	gsl_linalg_LU_solve(A,p,y,c);

	for(i = 0; i < n; i++)
	{
		cc[i+1] = gsl_vector_get(c,i);
		printf("%f\n", gsl_vector_get(c,i));
	}

	cc[0] = cc[2] - h/3 * alfa;
	cc[n+1] = h/3 * beta + cc[n-1];

	
	double ii;
	FILE *fp;
	fp = fopen("dane.dat", "w");
	for(ii = x_min ; ii <= x_max; ii+=0.1)
	{
		fprintf(fp,"%f %f %f %f\n", ii, fx(ii),ii,s(ii,h,n,cc,xw));
	}


	return 0;
}