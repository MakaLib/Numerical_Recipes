#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000000

double gen_1()
{
	static long int x = 10;
	int a = 17;
	int c = 0;
	long int m = pow(2,13) - 1;
	x = (a*x+c)%m;
	return x/(m + 1.0);
}

double gen_2()
{
	static long int x = 10;
	int a = 85;
	int c = 0;
	long int m = pow(2,13) - 1;
	x = (a*x+c)%m;
	return x/(m + 1.0);
}

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




int main()
{

	/*double tab1[N] = {0};
	double tab2[N] = {0};
	double tab3[N] = {0};
	int i;

	for(i  = 0;  i < N; i++)
	{
		tab1[i] = gen_1();
		tab2[i] = gen_2();
		tab3[i] = gen_3();
	}

	FILE *fp1, *fp2, *fp3;
	fp1 = fopen("dane1.dat","w");
	fp2 = fopen("dane2.dat","w");
	fp3 = fopen("dane3.dat","w");

	for(i  = 0; i < N-1; i++)
	{
		fprintf(fp1,"%f %f\n", tab1[i],tab1[i+1]);
		fprintf(fp2,"%f %f\n", tab2[i],tab2[i+1]);
		fprintf(fp3,"%f %f\n", tab3[i],tab2[i+1]);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	fp1 = fopen("dane1b.dat","w");
	fp2 = fopen("dane2b.dat","w");
	fp3 = fopen("dane3b.dat","w");

	for(i  = 0; i < N-2; i++)
	{
		fprintf(fp1,"%f %f\n", tab1[i],tab1[i+2]);
		fprintf(fp2,"%f %f\n", tab2[i],tab2[i+2]);
		fprintf(fp3,"%f %f\n", tab3[i],tab2[i+2]);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	fp1 = fopen("dane1c.dat","w");
	fp2 = fopen("dane2c.dat","w");
	fp3 = fopen("dane3c.dat","w");

	for(i  = 0; i < N-3; i++)
	{
		fprintf(fp1,"%f %f\n", tab1[i],tab1[i+3]);
		fprintf(fp2,"%f %f\n", tab2[i],tab2[i+3]);
		fprintf(fp3,"%f %f\n", tab3[i],tab2[i+3]);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);*/

	//double tab[N][4];

	int j,i;

	/*for(i = 0; i < N; i++)
	{
		for(j = 0; j < 4; j++)
		{
			tab[i][j] = gen_3();
		}
	}*/

	//double kula[N][3];
	//double wektory[N];


	double delta = 1/10.;
	double n[10]= {0};
	double R[10] = {0};
	double V[10];
	double g[10];
	int d = 3;

	FILE *fk,*fk1,*fk2;
	fk = fopen("sfera.dat","w");
	fk1 = fopen("kula.dat","w");
	fk2 = fopen("N_2000.dat","w");
	for(i = 0; i < 10000000; i++)
	{
		/*kula[i][0] = sqrt(-2*log(1-tab[i][0])) * cos(2 * M_PI * tab[i][1]);
		kula[i][1] = sqrt(-2*log(1-tab[i][0])) * sin(2 * M_PI * tab[i][1]);
		kula[i][2] = sqrt(-2*log(1-tab[i][2])) * cos(2 * M_PI * tab[i][3]);
		double norma = sqrt(kula[i][0]*kula[i][0] + kula[i][1]*kula[i][1] + kula[i][2]*kula[i][2]);
		kula[i][0] = kula[i][0]/norma;
		kula[i][1] = kula[i][1]/norma;
		kula[i][2] = kula[i][2]/norma;*/
		double l0 = gen_3();
		double l1 = gen_3();
		double l2 = gen_3();
		double l3 = gen_3();
		double x = sqrt(-2*log(1-l0)) * cos(2 * M_PI * l1);
		double y = sqrt(-2*log(1-l0)) * sin(2 * M_PI * l1);
		double z = sqrt(-2*log(1-l2)) * cos(2 * M_PI * l3);
		double norma = sqrt(x*x + y*y + z*z);
		fprintf(fk,"%f %f %f\n", x,y, z);
		double los = gen_3();
		double s = pow(los, 1/3.);
		x = x * s;
		y = y * s;
		z = z * s;
		fprintf(fk1,"%f %f %f\n", x,y, z);
		norma = sqrt(x*x + y*y + z*z);
		j = (int)(norma/delta);
		n[j]++;
		R[j] = delta * j;
		R[j-1] = delta *(j-1);
		V[j] = 4/3. * M_PI * pow(R[j],3);
		V[j-1] = 4/3. * M_PI * pow(R[j-1],3);
		g[j] = n[j]/(V[j] - V[j-1]);
	}

	
	fclose(fk);
	
	/*for(i = 0; i < N; i++)
	{
		
	}*/
	fclose(fk1);
	

/*	for(i = 0; i < N; i++)
	{
		double norma = sqrt(kula[i][0]*kula[i][0] + kula[i][1]*kula[i][1] + kula[i][2]*kula[i][2]);
		

		//fprintf(fk,"%f %f\n",n[j],g[j]);

	}*/

	for(j = 0; j < 10; j++)
	{
		fprintf(fk,"%f %f\n",n[j],g[j]);
	}

	
	fclose(fk2);

	return 0;
}