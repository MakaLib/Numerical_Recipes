#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double logarytm(double x)
{
	//return log(pow(x,5) + 3*pow(x,2) + x + 9);
	return pow(x,6);
}

double F2_log(double x1, double x2)
{
	return (logarytm(x2) - logarytm(x1))/(x2-x1);
}

double F3_log(double x1, double x2, double x3)
{
	return (F2_log(x2,x3) - F2_log(x1,x2))/(x3-x1);
}

int main()
{
	//printf("\nLOGARYTM\n");
	double h = 0.01;
	double x1 = 1.5;
	double x2 = x1 + h;
	double x3 = x2 + h;
	double xm;
	int i,j,k;
	double tab[3];
	tab[0] = x1;
	tab[1] = x2;
	tab[2] = x3;

	FILE *fp;
	/*fp = fopen("dane_log_dok.dat","w");
	double v;
	for(v = -1.5; v < 1; v+=0.05)
	{
		fprintf(fp,"%f %f\n",v,logarytm(v));
	}
	fclose(fp);*/
	fp = fopen("dane_pow_f2.dat", "w");
	FILE *fp2;
	FILE *fp3;
	fp2 = fopen("dane_1_pow.dat","w");
	fp3 = fopen("dane_2_pow.dat","w");
	
	for(i = 0; i < 100; i++)
	{
		xm = (tab[0]+tab[1])/2. - F2_log(tab[0],tab[1])/(2* F3_log(tab[0],tab[1],tab[2]));
	//	printf("%g %g %g %g %g %g \n", tab[0],tab[1],tab[2],xm,F2_log(tab[0],tab[1]),F3_log(tab[0],tab[1],tab[2]));
		fprintf(fp,"%d %g %g %g %g %g %g \n",i, tab[0],tab[1],tab[2],xm,F2_log(tab[0],tab[1]),F3_log(tab[0],tab[1],tab[2]));
		fprintf(fp2,"%d %g\n",i,F2_log(tab[0],tab[1]));
		fprintf(fp3,"%d %g\n",i,F3_log(tab[0],tab[1],tab[2]));
		double max = fabs(xm - tab[0]);
		int index = 0;
		for(j = 1; j< 3; j++)
		{
			if(fabs(xm - tab[j]) > max)
			{
				max = fabs(xm - tab[j]);
				index = j;
			}
		}
		tab[index] = xm;

		for(j = 0; j < 2; j++)
		{
    		for(k = 0; k < 2; k++)
    		{
     		 	if(tab[k] > tab[k + 1])
     			{
     		 		double temp = tab[k];
     		 		tab[k] = tab[k+1];
     		 		tab[k+1] = temp;
     		 	}
     		}
		}

		//printf("\nPosortowana: %g %g %g \n\n",tab[0],tab[1],tab[2]);

	}
 

	return 0;
}