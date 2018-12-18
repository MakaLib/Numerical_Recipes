#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

constexpr double DELTA = 0.01;
constexpr double P = 1.0;
constexpr double U = 1.0;
constexpr int NX = 200;
constexpr int NY = 90;
constexpr int I1  = 50;
constexpr int J1 = 55;
constexpr int IT_MAX = 20000;

double QWY(double &Qwe)
{
	double yny = NY*DELTA;
	double yj1 = J1 * DELTA;
	return ((Qwe) * ((pow(yny,3) - pow(yj1,3) - (3.0 * yj1*pow(yny,2)) + (3.0*pow(yj1,2)*yny))/pow(yny,3)));
}

void Modyfikacja_WBWidl(double **&W, double &Qwe, double &Qwy)
{
	//WB
	//Brzeg A
	for(int j = J1; j<=NY; j++)
	{
		double y = j * DELTA;
		double yj1 = J1*DELTA;
		double yny = NY*DELTA;
		W[0][j] = ( (Qwe/(2.0*U)) * ( (pow(y,3)/3.0) - (pow(y,2)/2.0) * (yj1+yny) + (y*yj1*yny)) );
	}

	//brzeg C
	for(int j = 0; j <= NY; j++)
	{
		double y = j * DELTA;
		double yj1 = J1*DELTA;
		double yny = NY*DELTA;
		double fPart = (Qwy/(2.0*U)) * ((pow(y,3)/3.0) - (pow(y,2)/2.0) * yny );
		double sPart = ((Qwe * pow(yj1,2) * (-yj1 + 3.0*yny))/(12.0*U));
		W[NX][j] = fPart + sPart;
	}

	//Brzeg B
	for(int i = 1; i <= NX-1; i++)
	{
		W[i][NY] = W[0][NY];
	}

	//Brzeg D
	for(int i = I1; i <= NX-1; i++)
		W[i][0] = W[0][J1];

	//Brzeg E
	for(int j = 1; j <= J1; j++)
		W[I1][j] = W[0][J1];

	//Brzeg F
	for(int i = 1; i <= I1; i++)
		W[i][J1] = W[0][J1];
}

void Modyfikacja_WBWezyk(double **&S,double **&W, double &Qwe, double &Qwy)
{
	double yj1 = J1 * DELTA;
	double yny = NY*DELTA;

	//Brzeg A
	for(int j = J1; j <= NY; j++)
	{
		double y = j*DELTA;
		S[0][j] = ((Qwe/(2.0*U)) * (2.0*y - yj1 - yny));
	}
	
	//Brzeg C
	for(int j = 0; j <= NY; j++)
	{
		double y = j * DELTA;
		S[NX][j] = ((Qwy/(2.0*U)) * (2.0 * y - yny));
	}

	//Brzeg B
	for(int i = 1; i <= NX-1; i++)
		S[i][NY] = ((2.0/pow(DELTA,2)) * (W[i][NY-1] - W[i][NY]));

	//Brzeg D
	for(int i = I1+1; i <= NX-1; i++)
		S[i][0] = ((2.0/pow(DELTA,2)) * (W[i][1] - W[i][0]));

	//Brzeg E
	for(int j = 1; j <= J1-1; j++)
		S[I1][j] = ((2.0/pow(DELTA,2)) * (W[I1+1][j] - W[I1][j]));

	//Brzeg F
	for(int i = 1; i <= I1; i++)
		S[i][J1] = ((2.0/pow(DELTA,2)) * (W[i][J1+1] - W[i][J1]));

	//Wierzcholek E/F
	S[I1][J1] = 0.5 * (S[I1-1][J1] + S[I1][J1-1]);
}

double Blad(double **&W, double **&S)
{
	int j2 = J1 + 2;
	double r = 0.0;
	for(int i = 1; i <= NX-1; i++)
	{
		r += W[i+1][j2] + W[i-1][j2] + W[i][j2+1] + W[i][j2-1] - (4.0*W[i][j2]) - (pow(DELTA,2) * S[i][j2]);
	}

	return r;
}

void NavStokes(FILE *&fp, FILE *&fp2, double Qwe)
{

	double Qwy = QWY(Qwe);
	double **W = new double*[NX+1];
	double **S = new double*[NX+1];
	for(int i = 0; i <= NX; i++)
	{
		W[i] = new double[NY+1];
		S[i] = new double[NY+1];
	}
	for(int i = 0; i <= NX; i++)
	{
		for(int j = 0; j <= NY; j++)
		{
			S[i][j] = 0.0;
			W[i][j] = 0.0;
		}
	}

	double omega = 0.0;
	double r = 0.0;
	//WB
	Modyfikacja_WBWidl(W,Qwe,Qwy);
	//Modyfikacja_WBWezyk(S,W,Qwe,Qwy);

	for(int it = 1; it <= IT_MAX; it++)
	{
		if(it < 2000)
			omega = 0.0;
		else
			omega = 1.0;

		for(int i = 1; i <= NX-1; i++)
		{
			for(int j = 1; j <= NY-1; j++)
			{
				//if( !((j == J1 && i <= I1) || (i == I1 && j <= J1) ))
				if(!(j <= J1 && i <= I1))
				{
					W[i][j] = 0.25 * (W[i+1][j] + W[i-1][j] + W[i][j+1] + W[i][j-1] - (pow(DELTA,2) * S[i][j]));
					double fPart = 0.25 * (S[i+1][j] + S[i-1][j] + S[i][j+1] + S[i][j-1]);
					double sPart = (((W[i][j+1] - W[i][j-1]) * (S[i+1][j] - S[i-1][j])) - ((W[i+1][j] - W[i-1][j]) * (S[i][j+1] - S[i][j-1])));
					S[i][j] = fPart - (omega * (P /(16.0 * U)) * sPart);
				}
			}
		}


		Modyfikacja_WBWezyk(S,W,Qwe,Qwy);
		r = Blad(W,S);

	}

	for(int i = 0; i <= NX; i++)
	{
		for(int j = 0; j <= NY; j++)
		{
			fprintf(fp, "%g %g %g %g\n", i*DELTA, j*DELTA, W[i][j], S[i][j]);
			//cout << i*DELTA <<" " << j*DELTA << " " << W[i][j] << endl;
		}
		fprintf(fp, "\n");
	}
	//fprintf(fp, "\n\n" );

	/*for(int i = 0; i <= NX; i++)
	{
		for(int j = 0; j <= NY; j++)
		{
			fprintf(fp, "%g %g %g\n", i*DELTA, j*DELTA, S[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n\n" );*/



	for(int i = 0; i <= NX; i++)
	{
		delete[] W[i];
		delete[] S[i];
	}
	delete W;
	delete S;

}


int main()
{
	FILE *fp, *fp2;
	fp = fopen("kontury.dat","w");
	fp2 = fopen("predkosc.dat","w");
	NavStokes(fp,fp2,-1000);

	return 0;
}