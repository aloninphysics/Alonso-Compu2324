#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define G 6.67E-11
#define MT 5.9736E24
#define ML 0.07349E24
#define dTL 3.844E8
#define w 2.6617E-6
#define RT 6.378160E6
#define RL 1.7374E6
#define PI 3.14



double f1(double pr);
double f2(double r, double pphi);
double f3(double r,double phi,double pphi,double t);
double f4(double r,double phi,double t);
double H(double r, double phi, double pr, double pphi);

int main()
{
    double t, tmax=10E7, h=60, mu, Delta, r, rprima, phi, pr, pphi;
    double K1[4], K2[4], K3[4], K4[4];
    int contador;
    FILE *fescribir, *fenergia;

    fescribir=fopen("Salida.txt", "w");
    fenergia=fopen("Energia.txt", "w");


  //En el instante inicial:
      r=RT/dTL;
      phi=(45*2*PI)/(360);
      pr=11345.0/dTL;
      //pphi=(RT*2*PI)/(365*60*24)/(dTL*dTL);
     pphi=0;


  //En t>0:
t=0;
  while(t<tmax)
  {
      //Paso 2
      K1[0]= h*f1(pr);
      K1[1]= h*f2(r, pphi);
      K1[2]= h*f3(r, phi, pphi, t);
      K1[3]= h*f4(r, phi, t);

      //Paso 3
      K2[0]= h*f1(pr + K1[2]/2);
      K2[1]= h*f2(r + K1[0]/2, pphi + K1[3]/2);
      K2[2]=h*f3(r + K1[0]/2, phi + K1[1]/2, pphi + K1[3]/2, t + h/2);
      K2[3]=h*f4(r + K1[0]/2, phi + K1[1]/2, t + h/2);

      //Paso 4
      K3[0]= h*f1(pr + K2[2]/2);
      K3[1]= h*f2(r + K2[0]/2, pphi + K2[3]/2);
      K3[2]= h*f3(r + K2[0]/2, phi + K2[1]/2, pphi + K2[3]/2, t + h/2);
      K3[3]= h*f4(r + K2[0]/2, phi + K2[1]/2, t + h/2);

      //Paso 5
      K4[0]= h*f1(pr + K3[2]);
      K4[1]= h*f2(r + K3[0], pphi + K3[3]);
      K4[2]= h*f3(r + K3[0], phi + K3[1], pphi + K3[3], t + h);
      K4[3]= h*f4(r + K3[0], phi + K3[1], t + h);

      //Paso 6
      r = r + (1.0/6.0)*(K1[0] + 2*K2[0] + 2*K3[0] + K4[0]);
      phi = phi + (1.0/6.0)*(K1[1] + 2*K2[1] + 2*K3[1] + K4[1]);
      pr = pr + (1.0/6.0)*(K1[2] + 2*K2[2] + 2*K3[2] + K4[2]);
      pphi = pphi + (1.0/6.0)*(K1[3] + 2*K2[3] + 2*K3[3] + K4[3]);

    if(contador%5==0)
    {
      fprintf(fescribir, "%lf, %lf", r*cos(phi), r*sin(phi));
      fprintf(fenergia, "%lf", (pr*pr + pphi*pphi)/2);   //Imprime en el fichero la energia del cohete

      fprintf(fenergia, "\n");
      fprintf(fenergia, "\n");

      fprintf(fescribir, "\n");
      fprintf(fescribir, "%lf, %lf", 2*cos(w*t), 2*sin(w*t));
      fprintf(fescribir, "\n");


      fprintf(fescribir, "\n");
    }
      
  contador=contador+1;
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

double f3(double r,double phi,double pphi,double t)
{
  double rprima, Delta, mu;
  Delta=(G*MT)/(pow(dTL, 3));
  mu=ML/MT;
  
  rprima=pow(1 + pow(r,2) - 2*r*cos(phi-w*t), 0.5);

  return ((pow(pphi, 2)/pow(r, 3))-Delta*(1/(pow(r,2)) + (mu/pow(rprima, 3))*(r-cos(phi-w*t))));
}

double f4(double r,double phi,double t)
{
  double rprima, Delta, mu;

  mu=ML/MT;
  Delta=(G*MT)/(pow(dTL, 3));
  rprima=pow(1 + pow(r,2) - 2*r*cos(phi-w*t), 0.5);

  return -sin(phi-w*t)*(Delta*mu*r)/(pow(rprima, 3)); 
}
