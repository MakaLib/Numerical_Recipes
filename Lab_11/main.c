#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include </usr/include/gsl/gsl_errno.h>
#include </usr/include/gsl/gsl_fft_complex.h>


double delta()
{
	return (2.* rand()/(RAND_MAX +1.0) - 1);
}

double fx(double w, int i)
{
	return (sin(w*i) + sin(2*w*i) + sin(3*w*i));
}

int main()
{
	
	int N,k;
	int i;
	double w;
	FILE *fp8, *fp8zo, *fp8no, *fp10zo, *fp10no, *fp12zo, *fp12no;

	fp8 = fopen("rze_ur_8.dat","w");
	fp8zo = fopen("zo8.dat", "w");
	fp8no = fopen("no8.dat", "w");
	fp10zo = fopen("zo10.dat", "w");
	fp10no = fopen("no10.dat", "w");
	fp12zo = fopen("zo12.dat", "w");
	fp12no = fopen("no12.dat", "w");

	for(k = 8; k <= 12; k +=2)
	{
		N = pow(2,k);
		w = 2.*2.*M_PI/N;
		double temp[2*N];
		double *y = malloc(2*N *sizeof(double));
		for(i = 0; i < 2*N; i++)
		{
			if(i%2) y[i] = 0.0;
			else y[i] = fx(w,i) + delta();
			temp[i] = y[i];
			if(i%2==0) printf("%f\n",temp[i]);
		}
	
		//exit(0);
		gsl_fft_complex_radix2_forward(y,1,N);
		if(k == 8)
		{
			for(i = 0; i < 2*N; i+=2)
			{
				fprintf(fp8, "%d %f %f %f\n",i, y[i],y[i+1],sqrt(y[i]*y[i] + y[i+1] * y[i+1]));
			}
		}



		double max = -1;
		for(i = 0; i < 2*N; i+=2)
		{
			double value = sqrt(y[i]*y[i] + y[i+1] * y[i+1]);
			if(value > max) max = value;
		}

		max = max/2;
		for(i = 0; i < 2*N; i+=2)
		{
			if(sqrt(y[i]*y[i] + y[i+1] * y[i+1]) < max)
			{
				y[i] = 0.0;
				y[i+1] = 0.0;
			} 
		}


		gsl_fft_complex_radix2_backward(y,1,N);
		for(i = 0; i < 2*N; i++)
		{
			y[i] = y[i]/((double)N);
		}

		if(k == 8)
		{
			for(i = 0; i< 2*N; i+=2) fprintf(fp8no,"%d %f %f\n",i,y[i],fx(w,i));
			for(i = 0; i< 2*N; i+=2) fprintf(fp8zo,"%d %f %f\n",i,y[i],temp[i]);
		}
		else if(k == 10)
		{
			for(i = 0; i< 2*N; i+=2) fprintf(fp10zo,"%d %f %f\n",i,y[i],temp[i]);
			for(i = 0; i< 2*N; i+=2) fprintf(fp10no,"%d %f %f\n",i,y[i],fx(w,i));
		}
		else
		{
			for(i = 0; i< 2*N; i+=2) fprintf(fp12zo,"%d %f %f\n",i,y[i],temp[i]);
			for(i = 0; i< 2*N; i+=2) fprintf(fp12no,"%d %f %f\n",i,y[i],fx(w,i));
		}

		free(y);
	}


	return 0;
}