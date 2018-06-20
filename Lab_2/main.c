#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
#include <math.h>


int main()
{
	FILE *fp;
	fp = fopen("dane.dat","w");
	int i, j, signum,n;
	n = 4;

	gsl_matrix *A = gsl_matrix_calloc(n,n);
	gsl_matrix *A_Copy = gsl_matrix_calloc(n,n);


	gsl_permutation *p = gsl_permutation_calloc(n);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			gsl_matrix_set(A,i,j,1.0/(i+j+2));
			gsl_matrix_set(A_Copy,i,j,gsl_matrix_get(A,i,j));
		}
		
	}

	gsl_linalg_LU_decomp(A,p,&signum);

	float det = 1.0;

	fprintf(fp,"\nElementy diagonalne:\n");
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(i == j)
			{
				fprintf(fp,"%f ", gsl_matrix_get(A,i,j));
				det *= gsl_matrix_get(A,i,j);
			}
		}
	}
	fprintf(fp,"\nWyznacznik macierzy: %g\n",det);
	fprintf(fp,"\nMacierz odwrotna:\n");

	gsl_matrix *odwr = gsl_matrix_calloc(n,n);
	for(i = 0; i < n; i++)
	{
		gsl_vector *b = gsl_vector_calloc(n);
		gsl_vector *x = gsl_vector_calloc(n);
		gsl_vector_set(b,i,1);
		gsl_linalg_LU_solve(A,p,b,x);
		for(j= 0; j < n; j++)
		{
			gsl_matrix_set(odwr,j,i,gsl_vector_get(x,j));
			
		}
		
		gsl_vector_free(x);
		gsl_vector_free(b);

	}
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			fprintf(fp,"%f ",gsl_matrix_get(odwr,i,j));
		}
		fprintf(fp,"\n");
	}

	gsl_matrix *C = gsl_matrix_calloc(n,n);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			int k;
			float z = gsl_matrix_get(C,i,j);
			for(k = 0; k < n; k++)
			{
				z = z + gsl_matrix_get(A_Copy,i,k) * gsl_matrix_get(odwr,k,j);
			}
			gsl_matrix_set(C,i,j,z);
		}
	}
	fprintf(fp,"\nIloczyn macierzy i macierzy odwrotnej\n");

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			fprintf(fp,"%g ",gsl_matrix_get(C,i,j));
		}
		fprintf(fp,"\n");
	}
	float cop = 0;
	float odwrotna = 0;

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(cop < fabs(gsl_matrix_get(A_Copy,i,j))) cop = fabs(gsl_matrix_get(A_Copy,i,j));
			if(odwrotna < fabs(gsl_matrix_get(odwr,i,j))) odwrotna = fabs(gsl_matrix_get(odwr,i,j));

		}
	}
	//fprintf(fp,"\nWskaznik normy: %f\n",wsk);
	printf("wks normy %f",cop*odwrotna);
		
	
	

	fclose(fp);
	return 0;
}