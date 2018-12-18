#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double max(double x, double y)
{
	if(x > y) return x;
	return y;
}

double K1V(double alpha, double xn, double vn)
{
	return alpha * (1.0 - pow(xn,2)) * vn - xn;
}

double K2X(double vn, double dt, double k1v)
{
	return vn + dt * k1v;
}

double K2V(double alpha, double xn, double dt, double k1x, double vn, double k1v)
{
	double first = alpha * (1.0 - pow((xn +dt * k1x),2));
	double second = vn + dt * k1v;
	double third = xn + dt * k1x;
	return first * second - third;
}

double XNP1(double xn, double dt, double k1x, double k2x)
{
	return xn + (dt/2.0) * (k1x + k2x);
}

double VNP1(double vn, double dt, double k1v, double k2v)
{
	return vn + (dt/2.0) * (k1v + k2v);
}

void RK2(double *xn, double *vn, double dt, double alpha)
{
	double k1x = *vn;
	double k1v  = K1V(alpha, *xn, *vn);

	double k2x = K2X(*vn, dt, k1v);
	double k2v = K2V(alpha,*xn,dt,k1x,*vn,k1v);

	double xnp = XNP1(*xn,dt,k1x,k2x);
	double vnp = VNP1(*vn,dt,k1v,k2v);
	*xn = xnp;
	*vn = vnp;
}

double EX(double x2n, double x1n, int p)
{
	return (x2n - x1n)/(pow(2.0,p) - 1.0);
}

double EV(double v2n, double v1n, int p)
{
	return (v2n - v1n)/(pow(2.0,p) - 1.0);
}

double f(double xn, double vn)
{
	return vn;
}

double g(double xn, double vn, double alpha)
{
	return alpha * (1.0 - pow(xn,2)) * vn - xn;
}

double F(double xn, double vn, double dt, double xnp, double vnp)
{
	return xnp - xn - (dt/2.0) * (f(xn,vn) + f(xnp,vnp));
}

double G(double xn, double vn, double dt, double xnp, double vnp,double alpha)
{
 	return vnp - vn - (dt/2.0)* (g(xn,vn,alpha) + g(xnp,vnp,alpha));
}

void Trapez(double *xnp, double *vnp, double dt, double alpha)
{
	double delta = pow(10,-10);
	double xn = *xnp;
	double vn = *vnp;
	double xnpp = xn;
	double vnpp = vn;


	while(1)
	{
		//xn = xnpp;
		//vn = vnpp;
		double a11 = 1.0;
		double a12 = -dt/2.0;
		double a21 = a12 * (-2.0 * alpha * xnpp * vnpp - 1.0);
		double a22 = 1.0 - (dt/2.0) * alpha * (1.0 - pow(xnpp,2));

		double sub = (a11*a22) - (a12*a21);
		double ff = -F(xn,vn,dt,xnpp,vnpp);
		double gg = -G(xn,vn,dt,xnpp,vnpp,alpha);

		double dx = (ff*a22 - gg*a12)/sub;
		double dv = (a11*gg - a21*ff)/sub;
		xnpp = xnpp + dx;
		vnpp = vnpp + dv;

		if((dx < delta) && (dv < delta))
		{
			*xnp = xnpp;
			*vnp = vnpp;
			break;
		}

	}
}


int main()
{

	double tStart = 0.0;
	double dtStart = 1.0;
	double x0 = 0.01;
	double v0 = 0.0;
	double S = 0.75;
	int p = 2;
	double tMax = 40.00;
	double alpha = 5.0;
	double TOL[] = {pow(10,-2), pow(10,-5)};
	double Ex = 0;
	double Ev = 0;

	FILE *fp;
	fp = fopen("wyniki.dat", "w");

	//Metoda RK2
	for(int i = 0; i < 2; i++)
	{
		double xn = x0;
		double vn = v0;
		double dt = dtStart;
		double t = tStart;
		do
		{
			double x2n = xn;
			double v2n = vn;
			RK2(&x2n, &v2n, dt, alpha);
			RK2(&x2n, &v2n, dt, alpha);

			double x1n = xn;
			double v1n = vn;
			RK2(&x1n, &v1n, 2*dt, alpha);

			Ex = EX(x2n, x1n, p);
			Ev = EV(v2n,v1n, p);
			double maximum = max(fabs(Ex), fabs(Ev));
			if(maximum < TOL[i])
			{
				t = t + 2* dt;
				xn = x2n;
				vn = v2n;
				fprintf(fp, "%f %f %f %f\n",t,dt, xn, vn);
			}
			dt = pow((S * TOL[i] / maximum),(1.0/(p+1.0))) * dt;


		}while(t < tMax);

		fprintf(fp, "\n\n");
	}


	//Metoda trapezow

	for(int i = 0; i < 2; i++)
	{
		double xn = x0;
		double vn = v0;
		double dt = dtStart;
		double t = tStart;
		do
		{
			double x2np = xn;
			double v2np = vn;
			Trapez(&x2np,&v2np,dt,alpha);
			Trapez(&x2np,&v2np,dt,alpha);


			double x1np = xn;
			double v1np = vn; 
			Trapez(&x1np,&v1np,2.0*dt,alpha); 
			


			Ex = EX(x2np, x1np, p);
			Ev = EV(v2np,v1np, p);
			printf("%f %f %f\n",Ex,Ev,dt );

			double maximum = max(fabs(Ex), fabs(Ev));
			if( maximum < TOL[i])
			{
				t = t + 2* dt; 
				xn = x2np;
				vn = v2np;
				fprintf(fp, "%f %f %f %f\n",t,dt, xn, vn);
			}
			dt = pow((S * TOL[i] / maximum),(1.0/(p+1.0))) * dt;


		}while(t < tMax);

		fprintf(fp, "\n\n");
	}
	fclose(fp);



	return 0;
}