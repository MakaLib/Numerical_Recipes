#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

constexpr double EPS = 1.0;
constexpr double DELTA = 0.1;
constexpr int NX = 150;
constexpr int NY = 100;
constexpr double V1 = 10.0;
constexpr double V2 = 0.0;
constexpr double XMAX = DELTA * NX;
constexpr double YMAX = DELTA * NY;
constexpr double SIGMAX = 0.1 * XMAX;
constexpr double SIGMAY = 0.1 * YMAX;
constexpr double TOL = pow(10,-8);

double p1(double x, double y)
{
	double firstExp = pow((x - 0.35 * XMAX),2) / pow(SIGMAX,2);
	double secondExp = pow((y - 0.5 * YMAX),2)/ pow(SIGMAY,2);
	return exp(-firstExp - secondExp);
}

double p2(double x, double y)
{
	double firstExp = pow((x - 0.65 * XMAX),2) / pow(SIGMAX,2);
	double secondExp = pow((y - 0.5 * YMAX),2)/ pow(SIGMAY,2);
	return (-1.0) * exp(-firstExp - secondExp);
}

double liczGlobalna(double Vi1j, double Vim1j, double Vij1, double Vijm1, double pij)
{
	return (1.0/4.0) * (Vi1j + Vim1j + Vij1 + Vijm1 + (pow(DELTA,2)/EPS) * pij);
}



void relaksacjaGlobalna(double wg, FILE *&fp)
{
	double Vs[NX+1][NY+1] = {{0}};
	double Vn[NX+1][NY+1] = {{0}};

	//Dolny brzeg
	for(int j = 0; j <= NX; j++)
	{
		Vs[j][0] = V1;
		Vn[j][0] = V1;
		Vs[j][NY] = V2;
		Vn[j][NY] = V2;
	}

	//Blad obecny
	double Sit = 1.0;
	//Blad poprzedni
	double Sitm1 = 1.0;
	//Numer iteracji
	int it = 0;

	double p = 0.0;


	do
	{
		//Wyznaczamy elementy poza brzegowymi
		for(int i = 1; i < NX; i++)
		{
			for(int j = 1; j < NY; j++)
			{
				p = p1((double)i * DELTA, (double)j * DELTA) + p2((double) i * DELTA, (double) j * DELTA);
				Vn[i][j] = liczGlobalna(Vs[i+1][j], Vs[i-1][j], Vs[i][j+1],Vs[i][j-1],p);
			}
		}

		//Uwzgledniamy warunki WB Neumanna
		for(int j = 1; j <= NY-1; j++)
		{
			Vn[0][j] = Vn[1][j];
			Vn[NX][j] = Vn[NX-1][j];
		}

		//Mieszamy wyniki
		for(int i = 0; i <=NX; i++)
		{
			for (int j = 0; j <= NY; j++)
			{
				Vs[i][j] = (1.0 - wg) * Vs[i][j] + wg * Vn[i][j];
			}
		}

		//Bledy
		Sitm1 = Sit;
		//cout<<"\nSit " << Sit <<" Sitm1 " << Sitm1 <<" fabs "<< fabs((Sit - Sitm1)/ Sitm1) << endl;

		double S = 0.0;
		double p = 0.0;
		//cout<<V[10][10] << " ";
		for(int i = 0; i <=NX-1; i++)
		{
			for(int j = 0; j <= NY-1; j++)
			{
				p = p1((double)i * DELTA, (double)j * DELTA) + p2((double) i * DELTA, (double) j * DELTA);
				double Vi1j = Vs[i+1][j] ;
				double Vij = Vs[i][j] ;
				double Vij1 = Vs[i][j+1] ;
				double firstExp = 0.5 * pow((Vi1j - Vij)/DELTA, 2);
				double secondExp = 0.5 * pow((Vij1 - Vij)/DELTA,2);
				S += pow(DELTA,2) * (firstExp + secondExp - p*Vij);
			}
		}

		Sit = S;
		it++;
		fprintf(fp, "%g %d\n",Sit, it );

	}while(fabs((Sit - Sitm1)/ Sitm1) > TOL );

	fprintf(fp, "\n\n" );

	//Mapa zrelaksowanego potencjalu
	for(int i = 1; i <= NX; i++)
	{
		for (int j = 1; j <= NY; j++)
		{
			double x = i * DELTA;
			double y = j * DELTA;
			double p = p1(x,y) + p2(x,y);
			double v1 = (Vn[i+1][j] - 2*Vn[i][j] + Vn[i-1][j])/pow(DELTA,2);
			double v2 = (Vn[i][j+1] - 2*Vn[i][j] + Vn[i][j-1])/pow(DELTA,2);
			double blad = v1 + v2 + p;
			fprintf(fp, "%f %f %g %g\n",x,y,Vn[i][j],blad );
		}
		fprintf(fp, "\n" );
	}
	std::cout << it<<"  ";
	
}

void relaksacjaLokalna(double wl, FILE *&fp)
{
	double V[NX+1][NY+1] = {{0}};
	//Ustawiamy brzegi
	for(int j = 0; j <= NX; j++)
	{
		V[j][0] = V1;
		V[j][NY] = V2;
	}


	double Sit = 1.0;
	//Blad poprzedni
	double Sitm1 = 1.0;
	//Numer iteracji
	int it = 0;

	double p = 0.0;


	do
	{
		for(int i = 1; i <= NX-1; i++)
		{
			for(int j = 1; j <= NY-1; j++)
			{
				p = p1((double)i * DELTA, (double)j * DELTA) + p2((double) i * DELTA, (double) j * DELTA);
				double expre = liczGlobalna(V[i+1][j], V[i-1][j], V[i][j+1],V[i][j-1],p);
				V[i][j] = (1.0 - wl) * V[i][j] + wl * expre;
			}
		}

		//Warunku von Neumanna
		for(int j = 0; j <= NY-1; j++)
		{
			V[0][j] = V[1][j];
			V[NX][j] = V[NX-1][j];
		}


		Sitm1 = Sit;
		//cout<<"\nSit " << Sit <<" Sitm1 " << Sitm1 <<" fabs "<< fabs((Sit - Sitm1)/ Sitm1) << endl;

		double S = 0.0;
		//cout<<V[10][10] << " ";
		for(int i = 0; i <=NX-1; i++)
		{
			for(int j = 0; j <= NY-1; j++)
			{
				p = p1((double)i * DELTA, (double)j * DELTA) + p2((double) i * DELTA, (double) j * DELTA);
				double Vi1j = V[i+1][j] ;
				double Vij = V[i][j] ;
				double Vij1 = V[i][j+1] ;
				double firstExp = 0.5 * pow((Vi1j - Vij)/DELTA, 2);
				double secondExp = 0.5 * pow((Vij1 - Vij)/DELTA,2);
				S += pow(DELTA,2) * (firstExp + secondExp - p*Vij);
			}
		}

		Sit = S;
		it++;
		fprintf(fp, "%g %d\n",Sit, it );
	}while(fabs((Sit - Sitm1)/ Sitm1) > TOL );
	cout<<"Itreacja: "<<it<<"\n";
}



int main()
{
	double wg[] = {0.6,1.0};
	double wl[] = {1.0, 1.4, 1.8, 1.9};
	FILE *fp;
	fp = fopen("globalna.dat", "w");

	for(int i = 0; i < 2; i++)
	{
		clock_t begin = clock();
		relaksacjaGlobalna(wg[i], fp);
		fprintf(fp, "\n\n" );
		clock_t end = clock();
		cout<<"\nTIme globalna: " << double(end - begin)/CLOCKS_PER_SEC << endl;
	}
	fclose(fp);

	fp = fopen("lokalna.dat", "w");
	for(int i = 0; i < 4; i++)
	{
		clock_t begin = clock();
		relaksacjaLokalna(wl[i], fp);
		fprintf(fp, "\n\n" );
		clock_t end = clock();
		cout<<"\nTIme lokalna: " << double(end - begin)/CLOCKS_PER_SEC << endl;
	}
	fclose(fp);


	return 0;
}