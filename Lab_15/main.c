#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gen_3()
{
	static long int x0 = 10;
	static long int x1 = 10;
	static long int x2 = 10;
	long int x;
	long int m = pow(2,32);
	x = (1176 * x0 + 1476 * x1 + 1776*x2)%(m - 5);
	x2=x1;
	x1=x0;
	x0=x;
	return x/(m+1.0);
}

double f(double V, double m, double k, double T)
{
	double fv =  sqrt(2./M_PI) * pow(m/(k*T), 3./2.) * V * V * exp(-m*V*V/(2.*k*T));
	return fv;
}



int main()
{

	double T = 100.0;
	double u = 1.66 * pow(10,-27);
	double k = 1.38 * pow(10,-23);
	double m = 40 * u;

	double sigma = sqrt(k*T/m);
	printf("%f",sigma);

	double Vsredniet = sqrt(8.*k*T/(M_PI * m));
	double Vkwsredniet = 3. * k * T/m;

	FILE *fp1[4];
	FILE *ff[4];
	FILE *ft[4];
	fp1[0] = fopen("dane0.dat", "w");
	fp1[1] = fopen("dane1.dat", "w");
	fp1[2] = fopen("dane2.dat", "w");
	fp1[3] = fopen("dane3.dat", "w");

	ff[0] = fopen("dane0f.dat", "w");
	ff[1] = fopen("dane1f.dat", "w");
	ff[2] = fopen("dane2f.dat", "w");
	ff[3] = fopen("dane3f.dat", "w");

	ft[0] = fopen("dane0t.dat", "w");
	ft[1] = fopen("dane1t.dat", "w");
	ft[2] = fopen("dane2t.dat", "w");
	ft[3] = fopen("dane3t.dat", "w");

	int L;
	for(L = 3; L <= 6; L++)
	{
		int NL = pow(10,L);
		int n,i;
		double V;
		int przedzial[31] = {0};
		double delta = 5*sigma/30.;

		double Vsr = 0.0;
		double sVsr = 0;
		double Vsrkw = 0.0;
		double sVsrkw = 0.0;
		double Vsrcz = 0.0;

		double *vv=malloc(1E6*sizeof(double));


		for(n = 0; n < NL; n++)
		{
			double x1 = gen_3();
			double x2 = gen_3();
			double x3 = gen_3();
			double x4 = gen_3();

			double V1 = sigma * sqrt(-2*log(x1)) * cos(2*M_PI*x2);
			double V2 = sigma * sqrt(-2*log(x1)) * sin(2*M_PI*x2);
			double V3 = sigma * sqrt(-2*log(x3)) * cos(2*M_PI*x4);

			V = sqrt(V1*V1 + V2*V2 + V3*V3);
			int j = (int) (V/delta) + 1;
			if (j <= 30) przedzial[j]++;

			vv[n]=V;

			Vsr +=  V;
			Vsrkw += V * V;
			Vsrcz = V * V * V* V;
		}


		double var=0.;
		for(n = 0; n < NL; n++)
		{
			var=var+pow(Vsr/NL-vv[n],2)/NL;
		}

		double sig2=sqrt(var/(NL-1));
	printf("%f\n\n\n",sig2);

	
		sVsr = sqrt(1/((double)(NL*(NL-1.))) * (Vsrkw - Vsr * Vsr/(double) NL));

		double a=sqrt(1./NL/(NL-1.) * (Vsrkw - Vsr * Vsr/ NL));
		printf("%d  %f  %f\n",NL,a,Vsrkw);

        printf("%d %f %f %f %f\n",NL, 1/(double)NL * Vsr, sVsr, 1/(double)NL * Vsrkw,sVsrkw );

		//sVsrkw = sqrt(1/((double)(NL*(NL-1))) * (Vsrcz - Vsrkw * Vsrkw/(double) NL));
        sVsrkw = sqrt(1./NL/(NL-1.) * (Vsrcz - Vsrkw * Vsrkw/NL));

		fprintf(ft[L-3], "%d %f %f %f %f\n",NL, 1/(double)NL * Vsr, sVsr, 1/(double)NL * Vsrkw,sig2);
		fprintf(ft[L-3], "\t\t%f \t\t%f\n", Vsredniet, Vkwsredniet );



		double dv = 5*sigma/30.;
		double g[31]= {0.0};
		for(i = 1; i < 31; i++)
		{
			g[i] = przedzial[i]/(double)NL * 1./dv;
			double v = (double)(i-1/2.)*dv;
			fprintf(fp1[L-3], "%f %f\n", v, g[i]);
			fprintf(ff[L-3], "%f %f\n",v,f(v,m,k,T));
		}






		
	}

	return 0;
}