#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define PI 3.14159265358979323846 

double f1(double y3);
double f2(double y4);
double f3(double y1, double y2, double y3, double y4);
double f4(double y1, double y2, double y3, double y4);

int main()
{
    double t, tmax = 100, h = 0.007, H = 15.0, g = 9.8;
    double K1[4], K2[4], K3[4], K4[4];
    double X1, X2, Y1, Y2, y1, y2, y3, y4;

    FILE *fescribir = fopen("SalidaPendulo.txt", "w");

     srand(time(NULL));
    clock_t start = clock();  // Inicia el temporizador

    //Condiciones iniciales:
    y1=2;
    y2=2;
    y3=sqrt(H + 2.0*g*cos(y1) + g*cos(y2));   //y3, phipunto
    y4=0.0;

    // Ciclo de simulación
    t = 0.0;
    while (t < tmax)
    {
        // Cálculos con Runge-Kutta
        #pragma omp parallel sections
        {
            #pragma omp section
            K1[0] = h * f1(y3);
            #pragma omp section
            K1[1] = h * f2(y4);
            #pragma omp section
            K1[2] = h * f3(y1, y2, y3, y4);
            #pragma omp section
            K1[3] = h * f4(y1, y2, y3, y4);
        }

        // Paso 3
        #pragma omp parallel sections
        {
            #pragma omp section
            K2[0] = h * f1(y3 + K1[2] / 2.0);
            #pragma omp section
            K2[1] = h * f2(y4 + K1[3] / 2.0);
            #pragma omp section
            K2[2] = h * f3(y1 + K1[0] / 2.0, y2 + K1[1] / 2.0, y3 + K1[2] / 2.0, y4 + K1[3] / 2.0);
            #pragma omp section
            K2[3] = h * f4(y1 + K1[0] / 2.0, y2 + K1[1] / 2.0, y3 + K1[2] / 2.0, y4 + K1[3] / 2.0);
        }

        // Paso 4
        #pragma omp parallel sections
        {
            #pragma omp section
            K3[0] = h * f1(y3 + K2[2] / 2.0);
            #pragma omp section
            K3[1] = h * f2(y4 + K2[3] / 2.0);
            #pragma omp section
            K3[2] = h * f3(y1 + K2[0] / 2.0, y2 + K2[1] / 2.0, y3 + K2[2] / 2.0, y4 + K2[3] / 2.0);
            #pragma omp section
            K3[3] = h * f4(y1 + K2[0] / 2.0, y2 + K2[1] / 2.0, y3 + K2[2] / 2.0, y4 + K2[3] / 2.0);
        }

        // Paso 5
        #pragma omp parallel sections
        {
            #pragma omp section
            K4[0] = h * f1(y3 + K3[2]);
            #pragma omp section
            K4[1] = h * f2(y4 + K3[3]);
            #pragma omp section
            K4[2] = h * f3(y1 + K3[0], y2 + K3[1], y3 + K3[2], y4 + K3[3]);
            #pragma omp section
            K4[3] = h * f4(y1 + K3[0], y2 + K3[1], y3 + K3[2], y4 + K3[3]);
        }

        // Paso 6
        y1 += (1.0 / 6.0) * (K1[0] + 2.0 * K2[0] + 2.0 * K3[0] + K4[0]);
        y2 += (1.0 / 6.0) * (K1[1] + 2.0 * K2[1] + 2.0 * K3[1] + K4[1]);
        y3 += (1.0 / 6.0) * (K1[2] + 2.0 * K2[2] + 2.0 * K3[2] + K4[2]);
        y4 += (1.0 / 6.0) * (K1[3] + 2.0 * K2[3] + 2.0 * K3[3] + K4[3]);

        X1 = sin(y1);
        Y1 = -cos(y1);
        X2 = X1 + sin(y2);
        Y2 = Y1 - cos(y2);

        // Escritura en archivos
        #pragma omp critical
        {
            fprintf(fescribir, "%lf, %lf\n", X1, Y1);
            fprintf(fescribir, "%lf, %lf\n\n", X2, Y2);
           
        }

        t += h;
    }

    fclose(fescribir);


    clock_t end = clock();  // Finaliza el temporizador
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Calcula el tiempo en segundos
    printf("Tiempo de ejecucion: %lf segundos\n", time_spent);  // Imprime el tiempo de ejecución 
    
    return 0;
}

double f1(double y3)  // phipunto
{
    return y3;
}

double f2(double y4)  // psipunto
{
    return y4;
}

double f3(double y1, double y2, double y3, double y4)    // phidoblepunto
{ 
    double numerador, denominador;
    double g = 9.8;

    numerador = g * sin(y2) * cos(y1 - y2) - 2 * g * sin(y1) - pow(y3, 2) * cos(y1 - y2) * sin(y1 - y2) - pow(y4, 2) * sin(y1 - y2);
    denominador = 2 - pow(cos(y1 - y2), 2);
 
    return numerador / denominador;
}

double f4(double y1, double y2, double y3, double y4)    // psidoblepunto
{
    double numerador, denominador;
    double g = 9.8;

    numerador = g * sin(y1) * cos(y1 - y2) - g * sin(y2) + 0.5 * pow(y4, 2) * cos(y1 - y2) * sin(y1 - y2) + pow(y3, 2) * sin(y1 - y2);
    denominador = 1 - 0.5 * pow(cos(y1 - y2), 2);
  
    return numerador / denominador; 
}
