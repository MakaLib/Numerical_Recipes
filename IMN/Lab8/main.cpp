#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

constexpr int NX = 400;
constexpr int NY = 90;
constexpr int I1 = 200;
constexpr int I2 = 210;
constexpr int J1 = 50;
constexpr double DELTA = 0.01;
constexpr double SIGMA = 10 * DELTA;
constexpr double XA = 0.45;
constexpr double YA = 0.45;
constexpr double eps = pow(10,-6);

double VX(double **&psi, const int &i, const int &j)
{
	return (psi[i][j+1] - psi[i][j-1])/(2.0*DELTA);
}

double VY(double **&psi, const int &i, const int &j)
{
	return -(psi[i+1][j] - psi[i-1][j])/(2.0*DELTA);
}

void initializeDensity(double **&u)
{
	for(int i = 0; i <= NX; i++)
	{
		for(int j = 0; j <= NY; j++)
		{
			double x = i *DELTA;
			double y = j * DELTA;
			double fPart = (1.0)/(2.0*M_PI*pow(SIGMA,2));
			double sPart = exp(- (pow(x-XA,2) + pow(y - YA,2)) / (2.0 * pow(SIGMA,2)));
			u[i][j] = fPart * sPart;
		}
	}
}

void initializeNextStep(double **&u0, double **&u1)
{
	for(int i = 0; i <= NX; i++)
		for(int j = 0; j <= NY; j++)
			u1[i][j] = u0[i][j];
}

void initializePreviousStep(double **&u0, double **&u1)
{
	for(int i = 0; i <= NX; i++)
		for(int j = 0; j <= NY; j++)
			u0[i][j] = u1[i][j];
}

double countForZero(double **&un, double **&un1,double **&vx,double **&vy, double D, int i, int j, double deltaT)
{
	double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
	double firstPart = un[i][j];
	double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (un[i+1][j] - un[NX][j])/(2.0*DELTA) ) + (  ( un1[i+1][j] - un1[NX][j] )/(2.0*DELTA)  ) );
	double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (un[i][j+1] - un[i][j-1])/(2.0*DELTA) ) + (  ( un1[i][j+1] - un1[i][j-1] )/(2.0*DELTA)  ) );
	double fourthPart1 = ( (un[i+1][j] + un[NX][j] + un[i][j+1] - 4.0 * un[i][j]) / pow(DELTA,2));
	double fourthPart2 = ( ( un1[i+1][j] + un1[NX][j] + un1[i][j+1] + un1[i][j-1]) / pow(DELTA,2));
	double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

	return firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
}

double countForNX(double **&un, double **&un1,double **&vx,double **&vy, double D, int i, int j, double deltaT)
{
	double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
	double firstPart = un[i][j];
	double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (un[0][j] - un[NX][j])/(2.0*DELTA) ) + (  ( un1[0][j] - un1[NX][j] )/(2.0*DELTA)  ) );
	double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (un[i][j+1] - un[i][j-1])/(2.0*DELTA) ) + (  ( un1[i][j+1] - un1[i][j-1] )/(2.0*DELTA)  ) );
	double fourthPart1 = ( (un[0][j] + un[NX][j] + un[i][j+1] - 4.0 * un[i][j]) / pow(DELTA,2));
	double fourthPart2 = ( ( un1[0][j] + un1[NX][j] + un1[i][j+1] + un1[i][j-1]) / pow(DELTA,2));
	double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

	return firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
}

double count(double **&un, double **&un1,double **&vx,double **&vy, double D, int i, int j, double deltaT)
{
	double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
	double firstPart = un[i][j];
	double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (un[i+1][j] - un[i][j])/(2.0*DELTA) ) + (  ( un1[i+1][j] - un1[i][j] )/(2.0*DELTA)  ) );
	double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (un[i][j+1] - un[i][j-1])/(2.0*DELTA) ) + (  ( un1[i][j+1] - un1[i][j-1] )/(2.0*DELTA)  ) );
	double fourthPart1 = ( (un[i+1][j] + un[i][j] + un[i][j+1] - 4.0 * un[i][j]) / pow(DELTA,2));
	double fourthPart2 = ( ( un1[i+1][j] + un1[i][j] + un1[i][j+1] + un1[i][j-1]) / pow(DELTA,2));
	double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

	return firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
}

double calculateC(double **&u)
{
	double result = 0.0;
	for(int i = 0; i <= NX; i++)
		for(int j = 0; j <= NY; j++)
			result += u[i][j] * pow(DELTA,2);

	return result;
}

double calculateX(double **&u)
{
	double result = 0.0;
	for(int i = 0; i <= NX; i++)
	{
		double x = i * DELTA;
		for(int j = 0; j <= NY; j++)
		{
			result += x * u[i][j] * pow(DELTA,2);
		}
	}
	return result;
}

void Dyfuzja(int IT_MAX, double D, double deltaT, fstream &filecix, fstream &filemap, double **&psi, double **&vx, double **&vy)
{
	
	double **u0 = new double*[NX+1];
	double **u1 = new double*[NX+1];


	for(int i = 0; i <= NX; i++)
	{
		u0[i] = new double[NY+1];
		u1[i] = new double[NY+1];
		for(int j = 0; j <= NY; j++)
		{
			u0[i][j] = 0.0;
			u1[i][j] = 0.0;
		}
	}

	double stepT = 0.0;
	int test = IT_MAX/5;
	int k = 1;
	initializeDensity(u0);
	for(int it = 1; it <= IT_MAX; it++)
	{
		//cout<<it<<endl;
		initializeNextStep(u0,u1);
		for(int k = 1; k <= 20; k++)
		{
			for(int i = 0; i <= NX; i++)
			{
				for(int j = 1; j <= NY-1; j++)
				{
					if(i>=I1 && i <= I2 && j<=J1)
						continue;
					else if(i==0)
					{
						double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
						double firstPart = u0[i][j];
						double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (u0[i+1][j] - u0[NX][j])/(2.0*DELTA) ) + (  ( u1[i+1][j] - u1[NX][j] )/(2.0*DELTA)  ) );
						double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (u0[i][j+1] - u0[i][j-1])/(2.0*DELTA) ) + (  ( u1[i][j+1] - u1[i][j-1] )/(2.0*DELTA)  ) );
						double fourthPart1 = ( (u0[i+1][j] + u0[NX][j] + u0[i][j+1] + u0[i][j-1] - 4.0 * u0[i][j]) / pow(DELTA,2));
						double fourthPart2 = ( ( u1[i+1][j] + u1[NX][j] + u1[i][j+1] + u1[i][j-1]) / pow(DELTA,2));
						double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

						u1[i][j] =  firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
					}
					else if(i == NX)
					{
						double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
						double firstPart = u0[i][j];
						double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (u0[0][j] - u0[i-1][j])/(2.0*DELTA) ) + (  ( u1[0][j] - u1[i-1][j] )/(2.0*DELTA)  ) );
						double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (u0[i][j+1] - u0[i][j-1])/(2.0*DELTA) ) + (  ( u1[i][j+1] - u1[i][j-1] )/(2.0*DELTA)  ) );
						double fourthPart1 = ( (u0[0][j] + u0[i-1][j] + u0[i][j+1] + u0[i][j-1] - 4.0 * u0[i][j]) / pow(DELTA,2));	
						double fourthPart2 = ( ( u1[0][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]) / pow(DELTA,2));
						double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

						u1[i][j] =  firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
					}
					else
					{
						double firstBracket = (1.0)/(1.0+ (2.0 * D *deltaT)/pow(DELTA,2));
						double firstPart = u0[i][j];
						double secondPart = (deltaT/2.0) * vx[i][j] * (  ( (u0[i+1][j] - u0[i-1][j])/(2.0*DELTA) ) + (  ( u1[i+1][j] - u1[i-1][j] )/(2.0*DELTA)  ) );
						double thirdPart = (deltaT/2.0) * vy[i][j] * (  ( (u0[i][j+1] - u0[i][j-1])/(2.0*DELTA) ) + (  ( u1[i][j+1] - u1[i][j-1] )/(2.0*DELTA)  ) );
						double fourthPart1 = ( (u0[i+1][j] + u0[i-1][j] + u0[i][j+1] + u0[i][j-1] - 4.0 * u0[i][j]) / pow(DELTA,2));
						double fourthPart2 = ( ( u1[i+1][j] + u1[i-1][j] + u1[i][j+1] + u1[i][j-1]) / pow(DELTA,2));
						double fourthPart = (deltaT/2.0) * D * (fourthPart1 + fourthPart2);

						u1[i][j] =  firstBracket * ( firstPart - secondPart - thirdPart + fourthPart);
					}
				}
			}
		}

		initializePreviousStep(u0,u1);

		double c = calculateC(u1);
		double xsr = calculateX(u1);
		filecix << c << " " << xsr << " " << stepT << "\n";
		stepT += deltaT;
		if(it == test)
		{	
			double tit = k  * IT_MAX * DELTA;
			std::cout << k << " " << D << " " << tit << " it: "<<it <<endl;
			for(int i = 0; i <= NX; i++)
			{
				for(int j = 0; j <=NY; j++)
				{
					filemap << i << " " << j << " " << u1[i][j] << tit <<endl;
				}
				filemap << endl;
			}
			test += IT_MAX/5;
			k++;
			filemap << endl;
		}
	}

	for(int i = 0; i <= NX; i++)
	{
		delete[] u0[i];
		delete[] u1[i];
	}

	delete[] u0;
	delete[] u1;
}


int main()
{

	fstream file;
	fstream file2;
	fstream file3;
	double **psi = new double*[NX+1];
	double **vx = new double*[NX+1];
	double **vy = new double*[NX+1];

	for(int i = 0; i <= NX; i++)
	{	
		psi[i] = new double[NY+1];
		vx[i] = new double[NY+1];
		vy[i] = new double[NY+1];
	}


	file.open("psi.dat", ios::in);
	while(!file.eof())
	{
		int x,y;
		double data;
		file >> x >> y >> data;
		psi[x][y] = data;
	}
	file.close();

	file.open("V.dat", ios::out);


	for(int i = 1; i <= NX-1; i++)
	{
		for(int j = 1; j <= NY-1; j++)
		{
			vx[i][j] = VX(psi,i,j);
			vy[i][j] = VY(psi,i,j);
		}
	}

	//Zakladka
	for(int i = I1; i <=I2; i++)
		for(int j = 0; j <= J1; j++)
			vx[i][j] = vy[i][j] = 0.0;

	//Dolny i gorny brzeg
	for(int i = 1; i <= NX-1; i++)
		vx[i][0] = vy[i][NY] = 0.0;

	//Lewy i prawy brzeg
	for(int j = 0; j <= NY; j++)
	{
		vx[0][j] = vx[1][j];
		vx[NX][j] = vx[NX-1][j];
	}

	double vMax = 0.0;
	for(int i = 0; i <= NX; i++)
	{
		for(int j = 0; j <= NY; j++)
		{
			file << i << " " << j << " " << vx[i][j] << " " << vy[i][j] << "\n";
			double module = sqrt(pow(vx[i][j],2) + pow(vy[i][j],2));
			if(vMax < module)
				vMax = module;
		}
		file << "\n";
	}

	double deltaT = DELTA/(4.0 * vMax);
	cout<<deltaT << endl;

	file.close();
	file.open("V0.dat", ios::out);
	file2.open("CiX0.dat", ios::out);
	file3.open("mapy.dat", ios::out);
	//void Dyfuzja(double D,fstream &filecix, double **&psi)
	Dyfuzja(10000,0.0,deltaT, file2,file3,psi,vx,vy);
	std::cout << "0.0" <<endl;
	file2 << endl << endl;
	Dyfuzja(10000, 0.1,deltaT, file2,file3, psi,vx,vy);
	std::cout << "0.1" <<endl;

	file.close();
	file2.close();
	file3.close();



	for(int i = 0; i <= NX; i++)
	{
		delete[] psi[i];
		delete[] vx[i];
		delete[] vy[i];
	}
	delete[] psi;
	delete[] vx;
	delete[] vy;

	
	return 0;
}