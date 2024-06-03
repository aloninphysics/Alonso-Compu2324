#include <stdio.h>
#include <math.h>

  /***************************************PROGRAMA PLANETAS SISTEMA SOLAR POR EL ALGORITMO DE VERLET**********************************
   ***********************************************************************************************************************************
   ***********************************************************************************************************************************/

#define c 1.496e11
#define G 6.67e-11
#define Ms 1.99e30

double Energia(double x[], double y[], double vx[], double vy[], double m[], int nplanetas);

int main()
{
int i, j, k, l, nplanetas;     
double t, h, masa, xo, voy, Etotal, cte, tmax; 

cte=sqrt((G*Ms)/(pow(c,3)));
nplanetas=9;

double m[nplanetas], x[nplanetas], y[nplanetas], vx[nplanetas], vy[nplanetas], ax[nplanetas], ay[nplanetas], wx[nplanetas], wy[nplanetas], periodo[nplanetas]; 
double yanterior[nplanetas], ygeo[nplanetas], xgeo[nplanetas];  

FILE *fmasas, *fxo, *fvoy, *fescribir, *fenergias, *fperiodos, *fgeocentricas;

tmax=200;

tmax=tmax*3600*24*365*cte;

fmasas=fopen("masasnueveplanetas.txt", "r");        
fxo=fopen("xnueveplanetas.txt", "r");
fvoy=fopen("vynueveplanetas.txt", "r");
fescribir=fopen("Salida.txt", "w");
fenergias=fopen("energias.txt", "w");
fperiodos=fopen("periodos.txt", "w");
fgeocentricas=fopen("geocentricas.txt", "w");

//Inicialiazamos todos los vectores para que no cojan valores residuales
for(j=0; j<nplanetas; j++)     
{   
  yanterior[j]=0;
  periodo[j]=0;
    m[j]=0;
    x[j]=0;
    y[j]=0;
    vx[j]=0;
    vy[j]=0;
    ax[j]=0;
    ay[j]=0;
    wx[j]=0;
    wy[j]=0;  
}

//Comprobamos que los ficheros se abrieron bien
if(fmasas == NULL) 
{
    printf("No se pudo abrir el archivo original.\n");
    return 1;
}
if(fxo == NULL) 
{
    printf("No se pudo abrir el archivo original.\n");
    return 1;
}
if(fvoy == NULL) 
{
    printf("No se pudo abrir el archivo original.\n");
    return 1;
}

//Recogemos los valores de masas, posiciones y velocidades iniciales de los planetas
k=0;
while(fscanf(fmasas,"%lf\n", &masa) !=EOF) 
{
m[k]=masa;       
k=k+1;
}
k=0;

while(fscanf(fxo,"%lf\n", &xo) !=EOF) 
{
x[k]=xo;             
k=k+1;         
}
k=0;

while(fscanf(fvoy,"%lf\n", &voy) !=EOF) 
{
vy[k]=voy*pow(-1, k); 
k=k+1;        
} 
k=0;


//Paso 1, Calculo de las aceleraciones iniciales (Con las fuerzas), que solo habrá ax.
for(i=0; i<nplanetas; i++)     
{
        
    for (j=0; j<nplanetas; j++)
    {

        if (j!=i)       //Inicialmente solo tendremos componentes en ax, ya que la aceleracion en y se ira a cero pq todos estan en y=0.
        {
                ax[i]= ax[i] - (m[j]*(x[i]-x[j]))/(pow(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)),3)); 
                ay[i]= ay[i] - (m[j]*(y[i]-y[j]))/(pow(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)),3));

        }      
    }

} 

for(i=0; i<nplanetas; i++)
{
  fprintf(fescribir, "%lf,%lf", x[i], y[i]);
  fprintf(fescribir, "\n"); 
}
fprintf(fescribir, "\n");





        /*************************************************************************************************
        ***************************************  COMIENZA EL WHILE CHULO **************************************
        **************************************************************************************************/

h=0.1;
t=0;

while(t<tmax)
{

    for(i=0; i<nplanetas; i++)   //PASO 2
    {

      yanterior[i]=y[i];

      x[i] = x[i] + h*vx[i] + (ax[i]*pow(h,2)*0.5); 
      y[i] = y[i] + h*vy[i] + (ay[i]*pow(h,2)*0.5); 

      
      wx[i] = vx[i] + (h*ax[i]*0.5);
      wy[i] = vy[i] + (h*ay[i]*0.5);

    }

    for(i=0; i<nplanetas; i++)   //PASO 3  
      {
        ax[i]=0;
        ay[i]=0;

        for (j=0; j<nplanetas; j++)              
        {

        if (j!=i)
        {
          ax[i] = ax[i] - (m[j]*(x[i]-x[j]))/pow(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)),3);
          ay[i] = ay[i] - (m[j]*(y[i]-y[j]))/pow(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)),3);       
        }

        }

      }
    
    for(i=0; i<nplanetas; i++)   //PASO 4
    
      {
      vx[i]= wx[i] + (h*ax[i]*0.5);         
      vy[i]= wy[i] + (h*ay[i]*0.5);
      }

    for(i=0; i<nplanetas; i++)           //Escribimos en el fichero Salida.txt las nuevas coordenadas de los planetas
    {
      fprintf(fescribir,"%lf,%lf",x[i],y[i]);  
      fprintf(fescribir, "\n");

      Etotal = Energia(x, y, vx, vy, m, nplanetas);  
    }
    fprintf(fescribir, "\n");

  fprintf(fenergias,"%lf", Etotal);  //Escribimos la energía total del sistema en el fichero energias.txt
  fprintf(fenergias, "\n");

  for(i=1; i<nplanetas; i++)         //Calculo de periodos de cada planeta
    {
        if(yanterior[i]<0 && yanterior[i]*y[i]<0 && periodo[i]==0)       
        {
          periodo[i] = t;         
        }
    }

  for(i=0; i<nplanetas; i++)         //Calculo de orbitas geocentricas
  {
    xgeo[i] = x[i]-x[3];
    ygeo[i] = y[i]-y[3];

      fprintf(fgeocentricas,"%lf,%lf",xgeo[i], ygeo[i]);  
      fprintf(fgeocentricas, "\n");
  }
  fprintf(fgeocentricas, "\n");

    t=t+h;
}  


    /****************************************************************************************************
    ***************************************  TERMINA EL WHILE CHULO **************************************
      **************************************************************************************************/




  for(i=1; i<nplanetas; i++)      //Escribimos en el fichero los periodos de cada planeta
  {
    periodo[i] = periodo[i]/(cte*3600*24*365);
    fprintf(fperiodos,"%lf", periodo[i]);
    fprintf(fperiodos, "\n");
  }
        
fclose(fescribir);
fclose(fmasas);
fclose(fxo);
fclose(fvoy);
fclose(fenergias);
fclose(fperiodos);
fclose(fgeocentricas);

return 0;
}


//Funciones

double Energia(double x[], double y[], double vx[], double vy[], double m[], int nplanetas)   //Función para el cálculo de energía total del sistema
{
  double Ecinetica[nplanetas], Epotencial[nplanetas];
  int i, j;
  double EnergiaTotal;

  for (i=0; i<nplanetas; i++)
  {
    for (j=0; j<nplanetas; j++)
    {
      if(j!=i)
      {
        Epotencial[i] = -(m[i]*m[j])/(pow(sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2)), 3));
      }
    
    }

    Ecinetica[i] = 0.5*m[i]*(pow(vx[i],2) + pow(vy[i],2));

    EnergiaTotal = EnergiaTotal + Ecinetica[i] + Epotencial[i];
  }
  
  return EnergiaTotal;
}












