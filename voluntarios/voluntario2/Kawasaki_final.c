<<<<<<< HEAD
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 32

double energia(int s[N][N]);
double magnetizacion(int ninicial, int nfinal, int minicial, int mfinal, int s[N][N]);
/*double DensidadParticulasMedia();
double EnergiaMediaPorParticula();
double DensidadParticulasPromedio();
double TemperaturaCritica();*/

int main() 
{
    int i, j, k, l, x1, y1, x2, y2, t, vecino, intercambio;
    double aleatorio, T = 0.1, p, VariacionEnergia = 0.0, Exponencial, Einicial = 0.0, Efinal = 0.0;
    double magnetizacion_dominio1=0.0, magnetizacion_dominio2=0.0;
    int s[N][N];

    FILE *fescribir, *fmagnetizacion1, *fmagnetizacion2;

    srand(time(NULL));

    clock_t start = clock();  // Inicia el temporizador

    // Inicializamos la red de espines
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            aleatorio = (1.0 * rand() / RAND_MAX);
            s[i][j] = (aleatorio < 0.5) ? -1 : 1;
        }
    }

    fescribir = fopen("SalidaKawasaki.txt", "w");
    fmagnetizacion1 = fopen("Magnetizacionessup.txt", "w");
    fmagnetizacion2 = fopen("Magnetizacionesinf.txt", "w");

fprintf(fmagnetizacion1, "T   ");
fprintf(fmagnetizacion1, "M");
fprintf(fmagnetizacion2, "T   ");
fprintf(fmagnetizacion2, "M");
    fprintf(fmagnetizacion1, "\n");
    fprintf(fmagnetizacion2, "\n");


     l = 0;

    while (l < 1000)         //Pasos Monte Carlo
    {
        for (t=0; t < N*N; t++)         //Pasos de Ising
        {
            x1 = rand() % N;
            y1 = rand() % N;

            // Eligimos un vecino al azar utilizando un switch
            vecino = rand() % 4;

            switch (vecino) 
            {
                case 0:
                    x2 = (x1 + 1) % N;
                    y2 = y1;
                    break;
                case 1:
                    x2 = (x1 - 1 + N) % N;
                    y2 = y1;
                    break;
                case 2:
                    x2 = x1;
                    y2 = (y1 + 1) % N;
                    break;
                case 3:
                    x2 = x1;
                    y2 = (y1 - 1 + N) % N;
                    break;
            }

            if (s[x1][y1] != s[x2][y2]) 
            {
                Einicial = energia(s);

                intercambio = s[x1][y1];
                s[x1][y1] = s[x2][y2];
                s[x2][y2] = intercambio;

                Efinal = energia(s);

                VariacionEnergia = Efinal - Einicial;

                Exponencial = exp(-VariacionEnergia/T);

                p = (Exponencial < 1.0) ? Exponencial : 1.0;

                aleatorio = (1.0*rand() / RAND_MAX);

                if (aleatorio >= p) {
                    // Revertir el intercambio si no se acepta
                    intercambio = s[x1][y1];
                    s[x1][y1] = s[x2][y2];
                    s[x2][y2] = intercambio;
                }
            }
        }

        // Escribimos la red en el fichero

        for (i=0; i<N; i++) 
        {
              int k=0;
              
            for (j=0; j<N; j++) 
            {
                fprintf(fescribir, "%d ", s[i][j]);

                if(k<N-1)
                {
                    fprintf(fescribir, ",");
                    k=k+1;
                }
            }
            fprintf(fescribir, "\n");
        }
        fprintf(fescribir, "\n");


        magnetizacion_dominio1=magnetizacion_dominio1 + magnetizacion(1, N/2, 1, N/2, s);
        magnetizacion_dominio2= magnetizacion_dominio2 + magnetizacion(N/2, N, N/2, N, s);

        l++;
        T=T+0.1; //Para cuando queramos calcular las magnetizaciones en función de la temperatura

         fprintf(fmagnetizacion1, "%lf %lf", T, magnetizacion_dominio1/l);
         fprintf(fmagnetizacion2, "%lf %lf", T, magnetizacion_dominio2/l);
       fprintf(fmagnetizacion1, "\n");
       fprintf(fmagnetizacion2, "\n");
    }

    fclose(fescribir);
    fclose(fmagnetizacion1);
    fclose(fmagnetizacion2);

    clock_t end = clock();  // Finaliza el temporizador
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Calcula el tiempo en segundos
    printf("Tiempo de ejecucion: %lf segundos\n", time_spent);  // Imprime el tiempo de ejecución 

    return 0;
}

double energia(int s[N][N]) 
{
    double energia=0.0;
    int i, j;

    for (i=0; i<N; i++) 
    {
        for (j=0; j<N; j++) 
        {
            energia = energia - 0.5*s[i][j]*(s[(i+1)%N][j] + s[(i-1+N)%N][j] + s[i][(j+1)%N] + s[i][(j-1+N)%N]);
        }
    }

    return energia;
}

double magnetizacion(int ninicial, int nfinal, int minicial, int mfinal, int s[N][N])
{
    int i, j;
    double magtotal=0.0;

    for(i=ninicial; i<nfinal; i++)
    {
        for(j=minicial; j<mfinal; j++)
        {
            magtotal=magtotal+s[i][j];
        }
    }

    return (magtotal)/((nfinal-ninicial)*(mfinal-minicial));        //Magnetizacion por unidad de particula calculada en el dominio indicado
}
=======
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 32

double energia(int s[N][N]);
double magnetizacion(int ninicial, int nfinal, int minicial, int mfinal, int s[N][N]);
/*double DensidadParticulasMedia();
double EnergiaMediaPorParticula();
double DensidadParticulasPromedio();
double TemperaturaCritica();*/

int main() 
{
    int i, j, k, l, x1, y1, x2, y2, t, vecino, intercambio;
    double aleatorio, T = 0.1, p, VariacionEnergia = 0.0, Exponencial, Einicial = 0.0, Efinal = 0.0;
    double magnetizacion_dominio1=0.0, magnetizacion_dominio2=0.0;
    int s[N][N];

    FILE *fescribir, *fmagnetizacion1, *fmagnetizacion2;

    srand(time(NULL));

    clock_t start = clock();  // Inicia el temporizador

    // Inicializamos la red de espines
    for (i = 0; i < N; i++) 
    {
        for (j = 0; j < N; j++) 
        {
            aleatorio = (1.0 * rand() / RAND_MAX);
            s[i][j] = (aleatorio < 0.5) ? -1 : 1;
        }
    }

    fescribir = fopen("SalidaKawasaki.txt", "w");
    fmagnetizacion1 = fopen("Magnetizacionessup.txt", "w");
    fmagnetizacion2 = fopen("Magnetizacionesinf.txt", "w");

fprintf(fmagnetizacion1, "T   ");
fprintf(fmagnetizacion1, "M");
fprintf(fmagnetizacion2, "T   ");
fprintf(fmagnetizacion2, "M");
    fprintf(fmagnetizacion1, "\n");
    fprintf(fmagnetizacion2, "\n");


     l = 0;

    while (l < 1000)         //Pasos Monte Carlo
    {
        for (t=0; t < N*N; t++)         //Pasos de Ising
        {
            x1 = rand() % N;
            y1 = rand() % N;

            // Eligimos un vecino al azar utilizando un switch
            vecino = rand() % 4;

            switch (vecino) 
            {
                case 0:
                    x2 = (x1 + 1) % N;
                    y2 = y1;
                    break;
                case 1:
                    x2 = (x1 - 1 + N) % N;
                    y2 = y1;
                    break;
                case 2:
                    x2 = x1;
                    y2 = (y1 + 1) % N;
                    break;
                case 3:
                    x2 = x1;
                    y2 = (y1 - 1 + N) % N;
                    break;
            }

            if (s[x1][y1] != s[x2][y2]) 
            {
                Einicial = energia(s);

                intercambio = s[x1][y1];
                s[x1][y1] = s[x2][y2];
                s[x2][y2] = intercambio;

                Efinal = energia(s);

                VariacionEnergia = Efinal - Einicial;

                Exponencial = exp(-VariacionEnergia/T);

                p = (Exponencial < 1.0) ? Exponencial : 1.0;

                aleatorio = (1.0*rand() / RAND_MAX);

                if (aleatorio >= p) {
                    // Revertir el intercambio si no se acepta
                    intercambio = s[x1][y1];
                    s[x1][y1] = s[x2][y2];
                    s[x2][y2] = intercambio;
                }
            }
        }

        // Escribimos la red en el fichero

        for (i=0; i<N; i++) 
        {
              int k=0;
              
            for (j=0; j<N; j++) 
            {
                fprintf(fescribir, "%d ", s[i][j]);

                if(k<N-1)
                {
                    fprintf(fescribir, ",");
                    k=k+1;
                }
            }
            fprintf(fescribir, "\n");
        }
        fprintf(fescribir, "\n");


        magnetizacion_dominio1=magnetizacion_dominio1 + magnetizacion(1, N/2, 1, N/2, s);
        magnetizacion_dominio2= magnetizacion_dominio2 + magnetizacion(N/2, N, N/2, N, s);

        l++;
        T=T+0.1; //Para cuando queramos calcular las magnetizaciones en función de la temperatura

         fprintf(fmagnetizacion1, "%lf %lf", T, magnetizacion_dominio1/l);
         fprintf(fmagnetizacion2, "%lf %lf", T, magnetizacion_dominio2/l);
       fprintf(fmagnetizacion1, "\n");
       fprintf(fmagnetizacion2, "\n");
    }

    fclose(fescribir);
    fclose(fmagnetizacion1);
    fclose(fmagnetizacion2);

    clock_t end = clock();  // Finaliza el temporizador
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Calcula el tiempo en segundos
    printf("Tiempo de ejecucion: %lf segundos\n", time_spent);  // Imprime el tiempo de ejecución 

    return 0;
}

double energia(int s[N][N]) 
{
    double energia=0.0;
    int i, j;

    for (i=0; i<N; i++) 
    {
        for (j=0; j<N; j++) 
        {
            energia = energia - 0.5*s[i][j]*(s[(i+1)%N][j] + s[(i-1+N)%N][j] + s[i][(j+1)%N] + s[i][(j-1+N)%N]);
        }
    }

    return energia;
}

double magnetizacion(int ninicial, int nfinal, int minicial, int mfinal, int s[N][N])
{
    int i, j;
    double magtotal=0.0;

    for(i=ninicial; i<nfinal; i++)
    {
        for(j=minicial; j<mfinal; j++)
        {
            magtotal=magtotal+s[i][j];
        }
    }

    return (magtotal)/((nfinal-ninicial)*(mfinal-minicial));        //Magnetizacion por unidad de particula calculada en el dominio indicado
}
>>>>>>> bb485f9dbf945243fbc8fdaf0a9ce0f978d90d4a
