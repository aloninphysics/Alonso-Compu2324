#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846 

//DECLARAMOS LAS FUNCIONES PARA EL ALGORITMO
double f1(double y3);
double f2(double y4);
double f3(double y1, double y2, double y3, double y4);
double f4(double y1, double y2, double y3, double y4);


int main()
{
    double t, tmax=100, h=0.01, H, g=9.8;
    double K1[4], K2[4], K3[4], K4[4];
    double X1, X2, Y1, Y2, y1, y2, y3, y4;    //coordenadas de las masas de los pendulos y valores de las variables del sistema

    FILE *fescribir, *fdiagramas1, *fdiagramas3, *fdiagramas5, *fdiagramas10, *fdiagramas15, *flyapunov;
    fescribir=fopen("SalidaPendulo.txt", "w");
    flyapunov=fopen("Lyapunov.txt", "w");

         srand(time(NULL));
    clock_t start = clock();  // Inicia el temporizador

  //Condiciones iniciales (Paso 1): 
    H=10.0;  
    y1=0.1;
    y2=0.1;
    //y3=2;     //y3, phipunto impuesto su valor inicial
    y3=sqrt(H + 2.0*g*cos(y1) + g*cos(y2));   //y3, phipunto calculada en funcion de H inicial
    y4=0.0;
    
      
  //Abrimos el fichero correspondienta para escribir los datos del mapeado de Poincaré.
    if(H==1.0)
    {
      fdiagramas1=fopen("Diagrama_Poincare_E1.txt", "w");
    }
    else if(H==3.0)
    {
      fdiagramas3=fopen("Diagrama_Poincare_E3.txt", "w");
    }
    else if (H==5.0)
    {
       fdiagramas5=fopen("Diagrama_Poincare_E5.txt", "w");
    }
    else if(H==10.0)
    {
      fdiagramas10=fopen("Diagrama_Poincare_E10.txt", "w");
    }
    else if(H==15.0)
    {
      fdiagramas15=fopen("Diagrama_Poincare_E15", "w");
    }
      
   t=0.0;

  //En t>0:
  while(t<tmax)
  {
      //Paso 2
      K1[0]= h*f1(y3);
      K1[1]= h*f2(y4);
      K1[2]= h*f3(y1, y2, y3, y4);
      K1[3]= h*f4(y1, y2, y3, y4);
      //Paso 3
      K2[0]= h*f1(y3 + K1[2]/2.0);
      K2[1]= h*f2(y4 + K1[3]/2.0);
      K2[2]= h*f3(y1 + K1[0]/2.0, y2 + K1[1]/2.0, y3 + K1[2]/2.0, y4 + K1[3]/2.0);
      K2[3]= h*f4(y1 + K1[0]/2.0, y2 + K1[1]/2.0, y3 + K1[2]/2.0, y4 + K1[3]/2.0);
      //Paso 4
      K3[0]= h*f1(y3 + K2[2]/2.0);
      K3[1]= h*f2(y4 + K2[3]/2.0);
      K3[2]= h*f3(y1 + K2[0]/2.0, y2 + K2[1]/2.0, y3 + K2[2]/2.0, y4 + K2[3]/2.0);
      K3[3]= h*f4(y1 + K2[0]/2.0, y2 + K2[1]/2.0, y3 + K2[2]/2.0, y4 + K2[3]/2.0);
      //Paso 5
      K4[0]= h*f1(y3 + K3[2]);
      K4[1]= h*f2(y4 + K3[3]);
      K4[2]= h*f3(y1 + K3[0], y2 + K3[1], y3 + K3[2], y4 + K3[3]);
      K4[3]= h*f4(y1 + K3[0], y2 + K3[1], y3 + K3[2], y4 + K3[3]);
      //Paso 6
      y1 = y1 + (1.0/6.0)*(K1[0] + 2.0*K2[0] + 2.0*K3[0] + K4[0]);
      y2 = y2 + (1.0/6.0)*(K1[1] + 2.0*K2[1] + 2.0*K3[1] + K4[1]);
      y3 = y3 + (1.0/6.0)*(K1[2] + 2.0*K2[2] + 2.0*K3[2] + K4[2]);
      y4 = y4 + (1.0/6.0)*(K1[3] + 2.0*K2[3] + 2.0*K3[3] + K4[3]);

      X1=sin(y1);
      Y1=-cos(y1);
      X2=X1+sin(y2);
      Y2=Y1-cos(y2);

      fprintf(fescribir, "%lf, %lf", X1, Y1);
      fprintf(fescribir, "\n");
      fprintf(fescribir, "%lf, %lf", X2, Y2);
      fprintf(fescribir, "\n");

      fprintf(fescribir, "\n");

//Escribimos los datos de los diagramas de Poincare diferenciando ficheros segun energias

if(H==1.0)
{
       fprintf(fdiagramas1, "%lf, %lf", y1, y3);
       fprintf(fdiagramas1, "\n");
} 

if(H==3.0)
{
       fprintf(fdiagramas3, "%lf, %lf", y1, y3);
       fprintf(fdiagramas3, "\n");
} 

if(H==5.0)
{
       fprintf(fdiagramas5, "%lf, %lf", y1, y3);
       fprintf(fdiagramas5, "\n");
} 

if(H==10.0)
{
       fprintf(fdiagramas10, "%lf, %lf", y1, y3);
       fprintf(fdiagramas10, "\n");
}

 if(H==15.0)
{
       fprintf(fdiagramas15, "%lf, %lf", y1, y3);
       fprintf(fdiagramas15, "\n");
}


//Escribimos en un fichero los valores de las 4 variables en 2 lanzamientos para despues proceder con los calculos de ellos en excel.

fprintf(flyapunov, "%lf %lf %lf %lf", y1, y2, y3, y4);
fprintf(flyapunov, "\n");


    t=t+h;
  }

fclose(fescribir);


    clock_t end = clock();  // Finaliza el temporizador
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Calcula el tiempo en segundos
    printf("Tiempo de ejecucion: %lf segundos\n", time_spent);  // Imprime el tiempo de ejecución 

return 0;
}


//FUNCIONES PARA EL ALGORITMO DE RUNGE_KUTTA

double f1(double y3)  //phipunto
{

  return y3;
}

double f2(double y4)  //psipunto
{
 return y4;
}

double f3(double y1, double y2, double y3, double y4)    //phidoblepunto
{ 
  double numerador, denominador;
  double g=9.8;

  numerador= g*sin(y2)*cos(y1-y2) - 2*g*sin(y1) - pow(y3, 2)*cos(y1-y2)*sin(y1-y2) - pow(y4, 2)*sin(y1 - y2);
  denominador= 2 - pow(cos(y1-y2), 2);
 
  return numerador/denominador;
}

double f4(double y1, double y2, double y3, double y4)    //psidoblepunto
{
  double numerador, denominador;
  double g=9.8;

  numerador = g*sin(y1)*cos(y1-y2) - g*sin(y2) + 0.5*pow(y4, 2)*cos(y1-y2)*sin(y1-y2) + pow(y3, 2)*sin(y1-y2);
  denominador = 1 - 0.5*pow(cos(y1-y2), 2);
  
  return numerador/denominador; 

}


    
  
