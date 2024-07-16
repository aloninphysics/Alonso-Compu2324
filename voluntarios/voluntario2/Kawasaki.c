#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define N 5

double magnetizacion_promedio();
double energia_media();
double calor_especifico();
double calculo_energia(int s[N][N]);



int main()
{   
    int i, j, n, m, u, v, l, t, k, random, vecino, x1, x2, y1, y2, intercambio;
    double aleatorio, T=1, p, VariacionEnergia=0.0, Exponencial, Einicial=0.0, Efinal=0.0;
    int s[N][N], s2[N][N];

    FILE *fescribir;

//Inicializar la semilla de la función números aleatorios.
    srand(time(NULL));

    clock_t start = clock();  //Inicia el temporizador


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
                s2[i][j]=random;
        }
        
    }

    
    fescribir=fopen("SalidaKawasaki.txt", "w");
 
      
    /************************************************************************************************************
     ****************************************** COMIENZA EL FOR DEL ALGORITMO DE KAWASAKI ************************
     *************************************************************************************************************/

    l=0;
    t=0;

    while(l<100)    //100 pasos Monte Carlo (Cada paso Monte Carlo da lugar a N*N intentos de cambios de espin)
    {

    for(t=0; t<N*N; t++)    
    {

//Escogemos un elemento de la red s(x1,y1) con x1 entre 1 y N-2 e y1 el que queramos
    x1 = (rand() % N-2)+1; 
    y1 = (rand() % N-2)+1;

    if(x1==1)
    {
        vecino = (rand()%3)+1; //3 posibles direcciones de intercambio
         
         if(vecino==1)
         {
            y2=(y1-1)%N;      //Izq
            x2=x1;
         }    
         else if(vecino==2)
         {
            y2=(y1+1)%N;
            x2=x1;     //derecha

         }
         else if(vecino==3)
         {
            y2=y1;
            x2=x1+1;    //Abajo
         }   
                          
    }
    else if(x1==N-2)
    {
        vecino = (rand()%3)+1;      //3 posibles direcciones de intercambio
         
         if(vecino==1)
         {
            y2=(y1-1)%N;      //Izq
            x2=x1;
         }    
         else if(vecino==2)
         {
            y2=(y1+1)%N;
            x2=x1;     //derecha

         }
         else if(vecino==3)
         {
            y2=y1;
            x2=x1-1;    //Arriba
         }   

    }
    else
    {
        vecino = (rand()%4)+1;      //4 posibles direcciones para el intercambio
         
         if(vecino==1)
         {
            y2=(y1-1)%N;      //Izq
            x2=x1;
         }    
         else if(vecino==2)
         {
            y2=(y1+1)%N;
            x2=x1;     //derecha

         }
         else if(vecino==3)
         {
            y2=y1;
            x2=x1+1;    //Abajo
         }  
         else if(vecino==4)
         {
            y2=y1;      //Arriba
            x2=x1-1;

         }
    }

    if (s[x1][y1]!=s[x2][y2]) 
    {
        Einicial = calculo_energia(s);

        s2[x1][y1]=s[x2][y2];
        s2[x2][y2]=s[x1][y1];

        Efinal = calculo_energia(s2);       
        VariacionEnergia=Efinal-Einicial;
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

        if(aleatorio<p) //Si esto pasa entonces intercambiamos con el vecino
        {
            s[x1][y1] = s[x2][y2];
        }
        else if(aleatorio>=p)
        {
            intercambio = s[x1][y1];
                s[x1][y1] = s[x2][y2];
                s[x2][y2] = intercambio;
        }

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


double calculo_energia(int s[N][N])
{
    double energia=0.0;
    int i, j;
        FILE *fayuda;

       fayuda=fopen("fayuda.txt", "w");

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            energia = energia - 0.5*s[i][j]*(s[(i+1)%N][j] + s[(i-1)%N][j] + s[i][(j+1)%N] + s[i][(j-1)%N]);
        }
        fprintf(fayuda,"%lf",energia);
        fprintf(fayuda, "\n");

    }

    fclose(fayuda);
    
 return energia;
}