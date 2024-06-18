#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <time.h>
#define PI 3.15916

int main()
{  
double nciclos, Norma, tmax=500;
int n, j, N=250;
double x, t, h, stilde, s, kotilde, landa, Vtilde[N], prob;

double complex Onda[N], chi[N], b[N-1], Acero[N-1], gamma[N-1], beta[N-1], alfa[N-1];

FILE *fschrodinger, *fnorma;

for(j=0; j<N; j++)
{
    gamma[j]=0;
    chi[j]=0;
    alfa[j]=0;
    beta[j]=0;
    Onda[j]=0;
    Vtilde[j]=0;
    Acero[j]=0;
    b[j]=0;

}

//Paso 1
nciclos=80;
landa=0.3;
kotilde=(2*PI*nciclos)/(N);
stilde= 1/(4*pow(kotilde,2));
s=0.25;
h=1;

fschrodinger=fopen("Salida.txt", "w");
fnorma=fopen("Norma.txt", "w");



//En t=0
for(j=0; j<N; j++)
{

    if(j<(0.6*N) && j>(0.4*N))
    {
        Vtilde[j]=pow(kotilde,2)*landa;
    }
    else
    {
        Vtilde[j]=0;
    }
}

for(j=0; j<N-1; j++)
{
    Acero[j] = -2 + (2*I)/(stilde) - Vtilde[j];
}

for(j=N-2; j>=0; j--)
{

    if(j==N-2)
    {
        alfa[j]=0;
    }
    else
    {
    alfa[j] = -1/(Acero[j+1] + alfa[j+1]);
    }
    
}


 for (j=0; j<N; j++)
    {
        if (j==0 || j==N-1)
        {
            Onda[j]=0;
        }
        else
        {
            Onda[j]= cexp((1*I*kotilde*j))*exp(-8*pow((4*j-N),2)/(N*N));
        }
    }

//Bucle temporal

x=0;
t=0;
n=0;

for(j=0; j<N-1; j++)
{
    gamma[j] = 1/(Acero[j] + alfa[j]);
}

while(t<tmax)
{
    for(j=0; j<N-1; j++)
    {
        b[j] = (4*I*Onda[j])/(stilde);
    }

    for(j=N-2; j>=0; j--)
    {

        if(j==N-2)
        {
            beta[j]=0;
        }
        else
        {
            beta[j] = (gamma[j+1])*(b[j+1] - beta[j+1]);
        }
          
    }

    for(j=0; j<N; j++)
    {

        if(j==0)
        {
            chi[j]=0;
        }
        else
        {
            chi[j]=(alfa[j-1]*chi[j-1]) + beta[j-1];
        }

    }

    for(j=0; j<N; j++)
    {
       Onda[j] = chi[j]-Onda[j];
    }

    Norma=0;

    for(j=0; j<N; j++)
    {
        prob=pow(cabs(Onda[j]), 2);
        Norma = Norma + prob;
        x=h*j;

     fprintf(fschrodinger,"%lf, %lf, %lf", x, prob, Vtilde[j]);
     fprintf(fschrodinger, "\n");
    }


    fprintf(fnorma, "%lf, %lf", n, Norma);
    fprintf(fnorma, "\n");

     
n=n+1;
t=n*s;
fprintf(fschrodinger, "\n");
}

fclose(fschrodinger);
fclose(fnorma);

return 0;
}
