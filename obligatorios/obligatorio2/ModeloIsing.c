#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define N 400

int main()
{   
    int i, j, n, m, l, t, k, random;
    double aleatorio, T=2.2, p, VariacionEnergia, Exponencial;
    double s[N][N];

    FILE *fescribir;

//Inicializar la semilla de la función números aleatorios.
    srand(time(NULL));

    clock_t start = clock();  // Inicia el temporizador
//Paso 0

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {

            aleatorio=(1.0*rand()/RAND_MAX);

            if(aleatorio<0.5)
            {
                random=-1;
            }
            else
            {
                random=1;
            }

                s[i][j]=random;
        }
        
    }
    
    fescribir=fopen("Salida.txt", "w");



    /************************************************************************************************************
     ****************************************** COMIENZA EL FOR DEL ALGORITMO DE ISING ************************
     *************************************************************************************************************/

    l=0;
    t=0;

    while(l<100)
    {

    for(t=0; t<N*N; t++)    
    {

    m= rand()% N;
    n= rand() % N;      

    VariacionEnergia = 2.0*s[n][m]*(s[(n+1)%N][m] + s[(n-1)%N][m] + s[n][(m+1)%N] + s[n][(m-1)%N]);

    Exponencial=exp(-1.0*VariacionEnergia/T);
    

    if(Exponencial<1.0)
    {
        p=Exponencial;
    }
    else
    {
        p=1.0;
    }

    aleatorio=(1.0*rand()/RAND_MAX);

    if(aleatorio<p)
    {
        s[n][m] = -1.0*s[n][m];
    }

    }


     for(i=0; i<N; i++)
    {
        k=0;
        for(j=0; j<N; j++)
        {
            fprintf(fescribir,"%lf",s[i][j]);

            if(k<N-1)
            {
                fprintf(fescribir, ",");
                k=k+1;
            }
        }

        

        fprintf(fescribir, "\n");
    }
    fprintf(fescribir, "\n");

    l=l+1;

    }
    fclose(fescribir);
    

    
     clock_t end = clock();  // Finaliza el temporizador
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // Calcula el tiempo en segundos
    printf("Tiempo de ejecucion: %lf segundos\n", time_spent);  // Imprime el tiempo de ejecución 


    return 0;
}