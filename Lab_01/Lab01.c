#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>


int main ()
{
	int n,i,j,signum;
	double omega,h,okres,pi,A,v;
	h = 0.1;
	A = 1.0;
	v = 0;

	pi = 4 * atan(1.0);
	okres = 2 * pi;
	n = 3 * okres / h;
	omega = 1.0;

	gsl_matrix *B = gsl_matrix_calloc(n,n);
	gsl_vector *x = gsl_vector_calloc(n);
	gsl_vector *b = gsl_vector_calloc(n);
	gsl_permutation *p = gsl_permutation_calloc(n);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j< n; j++)
		{
			gsl_matrix_set(B,i,j,0.0);
			if(i == j) gsl_matrix_set(B,i,j,1.0);
			if(i == j+1) gsl_matrix_set(B,i,j,(omega*omega*h*h-2));
			if(i == j+2) gsl_matrix_set(B,i,j,1.0);
		}
	}
	gsl_matrix_set(B,1,0,-1.0);
	gsl_vector_set(b,0,A);
	gsl_vector_set(b,1, v*h);
	gsl_linalg_LU_decomp(B,p,&signum);
	gsl_linalg_LU_solve(B,p,b,x);

	FILE *fp;
	fp = fopen("dane.dat","w");
	for(i = 0; i < n; i++)
	{
		double t = h * i;
		double x_dok = A * cos(omega * t);
		fprintf(fp,"%f %f %f \n",t,gsl_vector_get(x,i),x_dok);
	}

	fclose(fp);

	gsl_matrix_free(B);

	return 0;
}