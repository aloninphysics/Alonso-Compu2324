#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define G 6.67e-11
#define MT 5.9736e24
#define ML 0.07349e24
#define dTL 3.8443e8
#define w 2.6617e-6
#define RT 6.378160e6
#define RL 1.7374e6
#define PI 3.14159265358979323846



double f1(double pr);
double f2(double r, double pphi);
double f3(double r,double phi,double pphi,double t, double Delta, double mu, double rprima);
double f4(double r,double phi,double t, double Delta, double mu, double rprima);
double H(double r, double phi, double pr, double pphi);

int main()
{
    double t, mcohete=750e3, tmax=10.0e6, h=45.0, mu, Delta, r, rprima, phi, pr, pphi, H, Ecinetica, Potencialgrav;
    double K1[4], K2[4], K3[4], K4[4];
    int contador;
    FILE *fescribir, *fenergia;

    fescribir=fopen("Salida.txt", "w");
    fenergia=fopen("Energia.txt", "w");


  //En el instante inicial:
      r=RT/dTL;
      phi=(30.0*PI)/(180.0);
      pr=11110.0/dTL;
     pphi=(RT*RT*2.0*PI)/(24.0*3600.0*dTL*dTL);

     Delta=(G*MT)/pow(dTL, 3);
    mu=ML/MT;


  //En t>0:
t=0;
  while(t<tmax)
  {

    rprima=sqrt(1 + pow(r,2) - 2*r*cos(phi-w*t));

      //Paso 2
      K1[0]= h*f1(pr);
      K1[1]= h*f2(r, pphi);
      K1[2]= h*f3(r, phi, pphi, t, Delta, mu, rprima);
      K1[3]= h*f4(r, phi, t, Delta, mu, rprima);

      //Paso 3
      K2[0]= h*f1(pr + K1[2]/2);
      K2[1]= h*f2(r + K1[0]/2, pphi + K1[3]/2);
      K2[2]=h*f3(r + K1[0]/2, phi + K1[1]/2, pphi + K1[3]/2, t + h/2, Delta, mu, rprima);
      K2[3]=h*f4(r + K1[0]/2, phi + K1[1]/2, t + h/2, Delta, mu, rprima);

      //Paso 4
      K3[0]= h*f1(pr + K2[2]/2);
      K3[1]= h*f2(r + K2[0]/2, pphi + K2[3]/2);
      K3[2]= h*f3(r + K2[0]/2, phi + K2[1]/2, pphi + K2[3]/2, t + h/2, Delta, mu, rprima);
      K3[3]= h*f4(r + K2[0]/2, phi + K2[1]/2, t + h/2, Delta, mu, rprima);

      //Paso 5
      K4[0]= h*f1(pr + K3[2]);
      K4[1]= h*f2(r + K3[0], pphi + K3[3]);
      K4[2]= h*f3(r + K3[0], phi + K3[1], pphi + K3[3], t + h, Delta, mu, rprima);
      K4[3]= h*f4(r + K3[0], phi + K3[1], t + h, Delta, mu, rprima);

      //Paso 6
      r = r + (1.0/6.0)*(K1[0] + 2*K2[0] + 2*K3[0] + K4[0]);
      phi = phi + (1.0/6.0)*(K1[1] + 2*K2[1] + 2*K3[1] + K4[1]);
      pr = pr + (1.0/6.0)*(K1[2] + 2*K2[2] + 2*K3[2] + K4[2]);
      pphi = pphi + (1.0/6.0)*(K1[3] + 2*K2[3] + 2*K3[3] + K4[3]);

    Ecinetica = (pr*pr*mcohete*mcohete*dTL*dTL)/(2*mcohete) + (pphi*pphi*mcohete*dTL*dTL)/(2*mcohete*r*dTL*r*dTL);
    Potencialgrav = - G*mcohete*((MT)/(r*dTL) - (ML)/(sqrt(r*r*dTL*dTL + dTL*dTL - 2*r*dTL*dTL*cos(phi-w*t))));
    H = Ecinetica + Potencialgrav + w*pphi*mcohete*dTL+2e12;

      fprintf(fescribir, "%lf, %lf", r*cos(phi), r*sin(phi));
      fprintf(fenergia, "%lf", H);   //Imprime en el fichero la energia del cohete

      fprintf(fenergia, "\n");
      fprintf(fenergia, "\n");

      fprintf(fescribir, "\n");
      fprintf(fescribir, "%lf, %lf", cos(w*t), sin(w*t));
      fprintf(fescribir, "\n");

      fprintf(fescribir, "\n");

    t=t+h;
  }

fclose(fescribir);
fclose(fenergia);

return 0;
}


double f1(double pr)
{
  return pr;
}

double f2(double r, double pphi)
{
  return (pphi/pow(r,2));
}

double f3(double r,double phi,double pphi,double t, double Delta, double mu, double rprima)
{
  return (pphi*pphi/pow(r, 3))-Delta*(1/(r*r) + (mu/pow(rprima, 3))*(r-cos(phi-w*t)));
}

double f4(double r,double phi,double t, double Delta, double mu, double rprima)
{
  return -sin(phi-w*t)*(Delta*mu*r)/(pow(rprima, 3)); 
}
