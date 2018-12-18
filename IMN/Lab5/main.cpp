#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

//#define M_PI 3.14159265358979323846;
constexpr double DELTA = 0.2;
constexpr int NX = 128;
constexpr int NY = 128;
constexpr double XMAX = NX * DELTA;
constexpr double YMAX = NY * DELTA;
constexpr double TOL = pow(10,-8);


double error(double **&V, int k)
{
	double S = 0.0;
	for(int i = 0; i <= NX - k; i +=k)
	{
		for(int j = 0; j <= NY - k; j += k)
		{
			double first = pow(k*DELTA, 2) /2.0;
			double second = (V[i+k][j] - V[i][j])/(2.0*k*DELTA);
			double third = (V[i+k][j+k] - V[i][j+k])/(2.0*k*DELTA);
			double firstBracket = pow(second + third,2);
			double fourth = (V[i][j+k] - V[i][j])/(2.0*k*DELTA);
			double fifth = (V[i+k][j+k] - V[i+k][j])/(2.0*k*DELTA);
			double secondBracket = pow(fourth+fifth,2);
			S += first * (firstBracket+secondBracket); 
		}
	}
	return S;
}

void relax(int k, FILE *&fp, FILE *&fp2)
{
	double **V = new double*[NX+1];
	for(int i = 0; i <= NX; i++)
	{
		V[i] = new double[NY+1];
		for(int j = 0; j <= NY; j++)
			V[i][j] = 0.0;
	}

	//Warunki brzegowe
	for(int y = 0; y <= NY; y++)
		V[0][y] = sin(M_PI * (y*DELTA)/YMAX);
	for(int x = 0; x <= NX; x++)
		V[x][NY] = (-1.0) * sin(2.0 * M_PI * (x*DELTA)/XMAX);
	for(int y = 0; y <= NY; y++)
		V[NX][y] = sin(M_PI * (y*DELTA)/YMAX);
	for(int x = 0; x <= NX; x++)
		V[x][0] = sin(2 * M_PI * (x*DELTA)/XMAX);
	/////////
	double Sit = 1.0;
	double Sitm1 = 1.0;
	int it = 0;
	for(; k>=1; k = k/2)
	{
		Sit = error(V,k);
		Sitm1 = Sit;
			
		do
		{
			for(int i = k; i <= NX - k; i += k)
			{
				for(int j = k; j <= NY - k; j += k)
				{
					V[i][j] = (1.0/4.0) * (V[i+k][j] +V[i-k][j] + V[i][j+k] + V[i][j-k]);
				}
			}
	
			Sitm1 = Sit;
			Sit = error(V,k);
			fprintf(fp, "%d %g\n",it, Sit );
			it++;
		}while(fabs((Sit -Sitm1)/Sitm1) >= TOL);
		fprintf(fp, "\n\n");

		//Wypisanie potencjalu
		for(int i =0; i <= NX; i+=k)
		{
			for(int j = 0; j <= NY; j+=k)
			{
				fprintf(fp2, "%g %g %g\n", i*DELTA, j*DELTA, V[i][j] );
			}
			fprintf(fp2, "\n" );
		}

		//Zagescacznie siatki
		for(int i = 0; i <= NX - k; i+=k)
			{
				for(int j = 0; j <= NY-k; j+=k)
				{
					V[i + k/2][j+k/2] = (1.0/4.0) * (V[i][j] + V[i+k][j] + V[i][j+k] + V[i+k][j+k]);
					if(i+k != NX)
						V[i+k][j+ k/2] = (1.0/2.0) * (V[i+k][j] + V[i+k][j+k]);
					if(j+k != NY)
						V[i+k/2][j+k] = (1.0/2.0) * (V[i][j+k] + V[i+k][j+k]);
					if(j != 0)
						V[i+k/2][j] = (1.0/2.0) * (V[i][j] + V[i+k][j]);
					if(i!=0)
						V[i][j+k/2] = (1.0/2.0) * (V[i][j] + V[i][j+k]);
				}

			}


		
		

		fprintf(fp2, "\n\n" );
		
	
	}
	cout<<"Iteracje: " <<it<< endl;

	for(int i = 0; i <= NX; i++)
		delete[] V[i];
	delete[] V;
}


int main()
{
	FILE *fp;
	fp = fopen("blad.dat","w");
	FILE *fp2;
	fp2 = fopen("dane.dat","w");
	int k = 16;

	relax(k,fp, fp2);
	fprintf(fp, "\n\n");

	fclose(fp);
	fclose(fp2);

	return 0;
}