#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double F(double alpha, double un, double beta)
{
	return ((alpha*un) - (beta*un*un));
}

double F1(double U1, double U2, double un, double dt, double alpha, double beta)
{
	double a11 = 1./4.0;
	double a12 = a11 - sqrt(3)/6.0;
	return (U1 - un -dt*(a11*F(alpha,U1,beta) + a12*F(alpha,U2,beta)));
}

double F2(double U1, double U2, double un, double dt, double alpha, double beta)
{
	double a21 = 1./4. + sqrt(3)/6.0;
	double a22 = 1./4.0;
	return (U2 - un -dt*(a21*F(alpha,U1,beta) + a22*F(alpha,U2,beta)));
}

double M(double dt, double a, double alpha, double beta, double U)
{
	return dt*a*(alpha - 2 * beta * U);
}



void main()
{
	double beta = 0.001;
	double N = 500.0;
	double gamma = 0.1;
	double tMax = 100.0;
	double deltaT = 0.1;
	double un  = 1.0;
	double TOL = pow(10,-6);
	double alpha = beta*N - gamma;
	double unp = un;
	double t = 0.0;
	int u = 0;
	double un1 = un;
	double un2 = un;
	int umax = 0;


	//Metoda Picarda
	FILE *fp;
	fp = fopen("Wyniki.dat","w");
	fprintf(fp, "%f %f %f\n",t,un,N-un );

	while(t < tMax)
	{
		
		for(u = 1; u <=20; u++)
		{
			double unpup = un + (deltaT/2.0)*(F(alpha,un,beta) + F(alpha,unp, beta));
			if((fabs(unpup - unp) < TOL))
			{
				if(u > umax) umax= u;
				t += deltaT;
				un = unpup;
				fprintf(fp, "%f %f %f\n",t,un,N-un );
				break;
			}
			unp = unpup;
		}
	}
	printf("(Picard): %d\n", umax );


	fprintf(fp, "\n\n");

	//Metoda Newtona
	t= 0.0;
	u = 0;
	un = 1.0;
	unp = un;
	umax = 0;
	fprintf(fp, "%f %f %f\n",t,un,N-un );
	while(t < tMax )
	{
		for(u = 1; u <= 20; u++)
		{
			double dt = deltaT/2.0;
			double first = F(alpha,un,beta);
			double second = F(alpha, unp, beta);
			double sub = 1.0 - (dt * (alpha - 2*beta*unp));
			double unpup = unp - ((unp - un -dt*(first+second))/sub);
			
			if((fabs(unpup - unp) < TOL))
			{
				if(u > umax) umax= u;
				t += deltaT;
				un = unpup;
				fprintf(fp, "%f %f %f\n",t,un,N-un );
				break;
			}
			unp = unpup;
		}
	}
	printf("(PNewton): %d\n", u );

	

	//Niejawna metoda RK2
	u = 0;
	t = 0.0;
	un = 1.0;
	unp = un;
	umax = 0;
	
	fprintf(fp, "\n\n");

	//Wspolczynniki
	double a11 = 1./4.0;
	double a12 = a11 - sqrt(3)/6.0;
	double a21 = 1./4. + sqrt(3)/6.0;
	double a22 = 1./4.0;
	double b1 = 1./2.; double b2 = b1;
	double c1 = 1./2. - sqrt(3)/6.;
	double c2 = 1./2. - sqrt(3)/6.;
	fprintf(fp, "%f %f %f\n",t,un,N-un );

	while(t < tMax)
	{
		double U1 = un;
		double U2 = un;

		
		
		for(u = 1; u <= 20; u++)
		{
			double m11 = 1-M(deltaT,a11,alpha,beta,U1);
			double m12 = -M(deltaT,a12,alpha,beta,U2);
			double m21 = -M(deltaT,a21,alpha,beta,U1);
			double m22 = 1-M(deltaT,a22,alpha,beta,U2);
			double substract = (m11*m22) - (m12*m21);
			double f1 = F1(U1,U2,un,deltaT,alpha,beta);
			double f2 = F2(U1,U2,un,deltaT,alpha,beta);

			double deltaU1 = ((f2*m12) - (f1*m22))/substract;
			double deltaU2 = ((f1*m21) - (f2*m11))/substract;

			double tempU1 = U1;
			double tempU2 = U2;
			U1 = U1 + deltaU1;
			U2 = U2 + deltaU2;
			if((fabs(U1 - tempU1) < TOL) && (fabs(U2 -tempU2) < TOL))
			{
				double unp = un + deltaT * (b1 * F(alpha,U1,beta) + b2 * F(alpha,U2, beta));
				un = unp;
				t += deltaT;
				fprintf(fp, "%f %f %f\n",t,un,N-un );
				if(umax > u) umax = u;
				break;
			}
			
		}

	}

	printf("(RK): %d\n", u );


	fclose(fp);


}