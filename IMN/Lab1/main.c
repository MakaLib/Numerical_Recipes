#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double EulerDok(double lambda, double t)
{
	return exp(lambda * t);
}

double Euler(double lambda, double y)
{
	return lambda*y;
}

double RK(double lambda, double y,double t,double k)
{
	return lambda * (y + (t*k)); 
}

double Vt(double wv, double t)
{
	return 10*sin(wv*t);
}

double QQ(double L, double C, double Q, double dt, double k)
{
	return (1.0/(L*C) * (Q + dt * k));
}

double II(double R, double L, double I, double dt, double k)
{
	return (R/L) * (I + dt*k);
}

double Qnpp(double k1Q, double k2Q, double k3Q, double k4Q)
{
	return (k1Q + k2Q + k3Q + k4Q);
}

double Inpp(double k1I, double k2I, double k3I, double k4I)
{
	return (k1I + k2I + k3I + k4I);
}



int main()
{

	double y = 1.0;
	double lambda = -1.0;
	//double t = 0.0;


	double dt[3] = {0.01, 0.1, 1.0};

	FILE *fp[4];
	fp[0] = fopen("EulerNum0.dat", "w");
	fp[1] = fopen("EulerNum1.dat", "w");
	fp[2] = fopen("EulerNum2.dat", "w");
	fp[3] = fopen("EulerAnal.dat", "w");

	FILE *fb[3];
	fb[0] = fopen("EulerBlad0.dat", "w");
	fb[1] = fopen("EulerBlad1.dat", "w");
	fb[2] = fopen("EulerBlad2.dat", "w");

	//1111111111111111111111111
	for(int i = 0; i < 3; i++)
	{
		y = 1.0;
		for(double t = 0.0; t <= 5.0; t+=dt[i])
		{
			double ydok = EulerDok(lambda,t);
			if(i == 0) 
			{
				fprintf(fp[3], "%f %f\n",t,ydok );
			}

			fprintf(fp[i], "%f %f\n", t, y);
			fprintf(fb[i], "%f %f\n",t, y - ydok);
			double yn = y + (dt[i] * Euler(lambda,y));
			y = yn;
		}
	}

	for(int i = 0; i < 3; i++)
	{
		fclose(fp[i]);
		fclose(fb[i]);
	}
	fclose(fp[3]);


	//22222222222222222222222222222
	fp[0] = fopen("RK2Num0.dat", "w");
	fp[1] = fopen("RK2Num1.dat", "w");
	fp[2] = fopen("RK2Num2.dat", "w");

	fb[0] = fopen("RK2Blad0.dat", "w");
	fb[1] = fopen("RK2Blad1.dat", "w");
	fb[2] = fopen("RK2Blad2.dat", "w");


	for(int i = 0; i < 3; i++)
	{
		y = 1.0;
		for(double t = 0.0; t <= 5.0; t+=dt[i])
		{

			double ydok = EulerDok(lambda,t);
			fprintf(fp[i], "%f %f\n", t, y);
			fprintf(fb[i], "%f %f\n",t, y - ydok);
			double k1 = Euler(lambda,y);
			double k2 = RK(lambda,y,dt[i],k1);
			double yn = y + (dt[i]/2.0) * (k1+k2);
			y = yn;
		}
	}

	for(int i = 0; i < 3; i++)
	{
		fclose(fp[i]);
		fclose(fb[i]);
	}

	//33333333333333333333333
	fp[0] = fopen("RK4Num0.dat", "w");
	fp[1] = fopen("RK4Num1.dat", "w");
	fp[2] = fopen("RK4Num2.dat", "w");

	fb[0] = fopen("RK4Blad0.dat", "w");
	fb[1] = fopen("RK4Blad1.dat", "w");
	fb[2] = fopen("RK4Blad2.dat", "w");

	for(int i = 0; i < 3; i++)
	{
		y = 1.0;
		for(double t = 0.0; t <= 5.0; t+=dt[i])
		{

			double ydok = EulerDok(lambda,t);
			fprintf(fp[i], "%f %f\n", t, y);
			fprintf(fb[i], "%f %f\n",t, y - ydok);
			double k1 = Euler(lambda,y);
			double k2 = RK(lambda,y,dt[i]/2.0,k1);
			double k3 = RK(lambda,y,dt[i]/2.0,k2);
			double k4 = RK(lambda,y,dt[i],k3);
			double yn = y + (dt[i]/6.0)*(k1 + 2*k2 + 2*k3 + k4);
			y = yn;
		}
	}

	for(int i = 0; i < 3; i++)
	{
		fclose(fp[i]);
		fclose(fb[i]);
	}

	//4444444444444444444444444
	double R = 100.0;
	double L = 0.1;
	double C = 0.001;
	double w0 = 1.0/(sqrt(L*C));
	double T0 = (2*M_PI)/w0;
	double wV[4] = {0.5*w0, 0.8*w0, 1.0*w0, 1.2*w0};
	double dtt = pow(10,-4);

	fp[0] = fopen("QtNum0.dat", "w");
	fp[1] = fopen("QtNum1.dat", "w");
	fp[2] = fopen("QtNum2.dat", "w");
	fp[3] = fopen("QtNum3.dat", "w");

	for(int i = 0; i < 4; i++)
	{
		double I = 0.0;
		double Q = 0.0;
		for(double t = 0.0; t <= 4*T0; t+=dtt)
		{
			fprintf(fp[i], "%f %f\n",t,Q);
			double k1Q = I;
			double k1I = (Vt(wV[i],t)/L) - QQ(L,C,Q,0.0,0.0) - II(R,L,I,0.0,0.0);
			double k2Q = II(1,1,I,dtt/2.0,k1I);
			double k2I = (Vt(wV[i],t+(dtt/2.0))/L) - QQ(L,C,Q,dtt/2.0,k1Q) - II(R,L,I,dtt/2.0,k1I);
			double k3Q = II(1,1,I,dtt/2.0,k2I);
			double k3I = (Vt(wV[i],t+(dtt/2.0))/L) - QQ(L,C,Q,dtt/2.0,k3Q) - II(R,L,I,dtt/2.0,k2I);
			double k4Q = II(1,1,I,dtt,k3I);
			double k4I = (Vt(wV[i],t+dtt)/L) - QQ(L,C,Q,dtt,k3Q) - II(R,L,I,dtt,k3I);


			double Qn = Q + (dtt/6.0) * Qnpp(k1Q,2*k2Q,2*k3Q,k4Q);
			double In = I + (dtt/6.0) * Inpp(k1I,2*k2I,2*k3I,k4I);
			I = In;
			Q = Qn;

		}
	}

	for(int i = 0; i < 4; i++)
	{
		fclose(fp[i]);
	}



	return 0;
}