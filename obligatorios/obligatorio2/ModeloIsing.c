#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{  
    int i, j, n, m, k=0, N=5;
    double aleatorio, T=2;
    int s[N][N];

//Inicializar la semilla de la función números aleatorios.
    srand(time(NULL));

//Paso 0
while (k<N*N)
{
    
    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            aleatorio = 2*(rand()/RAND_MAX)-1;
        
            if(aleatorio<0)
            {
                s[i][j] = -1;
            }
            else
            {
                s[i][j] = 1;
            }
        }
        
    }
    

k=k+1;
}

//Paso 1: Elegimos un punto al azar de la red.

    n=(rand()/RAND_MAX)*N;
    m=(rand()/RAND_MAX)*N;





    return 0;
}