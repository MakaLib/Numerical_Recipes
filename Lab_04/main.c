#include</usr/include/gsl/gsl_eigen.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

double delta(int i, int j)
{
	if(i == j) return 1.0;
	return 0.0;
}

int main()
{
	double L = 10.0;
	int n = 200;
	int N = 1;
	double dx = L/(n+1);

	gsl_matrix *A = gsl_matrix_calloc(n,n);
	gsl_matrix *B = gsl_matrix_calloc(n,n);

	gsl_vector *eval = gsl_vector_calloc(n);
	gsl_matrix *evec = gsl_matrix_calloc(n,n);
	gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);
	gsl_vector *x = gsl_vector_calloc(n);

	int i,j,alfa;

	FILE *fp1;
	FILE *fp2;
	FILE* fp3;
	fp1 = fopen("dane1.dat","w");
	fp2 = fopen("dane2.dat", "w");
	fp3 = fopen("dane3.dat", "w");

	for(i = 0; i < n; i++)
	{
		gsl_vector_set(x,i, -L/2 + dx * (i+1));
	}

	
	for(alfa = 0; alfa <=100; alfa+=2)
	{
		for( i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				gsl_matrix_set(A,i,j, (-delta(i,j+1) + 2 * delta(i,j) - delta(i,j-1))/(dx*dx));
				gsl_matrix_set(B,i,j, ((1 + 4 * alfa * gsl_vector_get(x,i) * gsl_vector_get(x,i))*delta(i,j))/N);
			}
		}

		gsl_eigen_gensymmv(A,B,eval,evec,w);
		gsl_eigen_gensymmv_sort(eval,evec,GSL_EIGEN_SORT_ABS_ASC);
		fprintf(fp1,"%d ",alfa);
		for(i = 0; i < 6; i++) fprintf(fp1,"%g ",sqrt(gsl_vector_get(eval,i)));
		fprintf(fp1,"\n");
		if(alfa == 0)
		{
			for(i = 0; i < n; i++)
			{
				fprintf(fp2,"%d",i);
				for(j = 0; j < 6; j++) 
					fprintf(fp2," %g ",gsl_matrix_get(evec,i,j));
				fprintf(fp2,"\n");
			}
			
		}

		if(alfa == 100)
		{
			for(i = 0; i < n; i++)
			{
				fprintf(fp3,"%d",i);
				for(j = 0; j < 6; j++) 
					fprintf(fp3," %g ",gsl_matrix_get(evec,i,j));
				fprintf(fp3,"\n");
			}
			

		}
	}


	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}