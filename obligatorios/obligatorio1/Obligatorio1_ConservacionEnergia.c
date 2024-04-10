#include <stdio.h>
#include <math.h>

#define time_max 100


//void segundopaso(double x[], double y[], double vx[], double vy[], double ax[], double ay[], double wx[], double wy[], int nplanetas,  double h);
//void tercerpaso(double m[], double x[], double y[], double ax[], double ay[], int nplanetas);
//void cuartopaso(double vx[], double vy[], double ax[], double ay[], double wx[], double wy[], int nplanetas,  double h);
//void periodos(double y[], double yanterior[],double t, int nplanetas);
double Energia(double x[], double y[], double vx[], double vy[], double m[], int nplanetas);

int main()
{
int i, j, k, l, nplanetas;     
double t, h, masa, xo, voy, Etotal, EnergiaTotal;   
double m[9], x[9], y[9], vx[9], vy[9], ax[9], ay[9], wx[9], wy[9], yanterior[9];    

h=0.1;

FILE *fmasas, *fxo, *fvoy, *fescribir, *fenergias;

//printf("Dime un numero de planetas para la simulacion: ");
//scanf("%i", &nplanetas);

nplanetas=9;

fmasas=fopen("masasnueveplanetas.txt", "r");         //Abre el fichero donde se van a leer los datos iniciales
fxo=fopen("xnueveplanetas.txt", "r");
fvoy=fopen("vynueveplanetas.txt", "r");

for(j=0; j<nplanetas; j++)     //Inicializamos todos los valores de los vectores a cero para que no hayan residuos.
{   
  yanterior[j]=0;
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

fescribir=fopen("Salida.txt", "w"); //Abre un fichero donde se van a escribir los datos (Destruye el fichero si ya existe)
fenergias=fopen("energias.txt", "w");

k=0;
l=0; 
i=0;

while(fscanf(fmasas,"%lf\n", &masa) !=EOF) 
{
m[k]=masa;       
k=k+1;
}
k=0;

while(fscanf(fxo,"%lf\n", &xo) !=EOF) 
{
x[i]=xo;             
i=i+1;         
}
i=0;

while(fscanf(fvoy,"%lf\n", &voy) !=EOF) 
{
vy[l]=voy; 
l=l+1;        
} 
l=0;


for(i=0; i<nplanetas; i++)     //Paso 1, Calculo de las aceleraciones iniciales (Con las fuerzas), que solo habrá ax.
{
        
    for (j=0; j<nplanetas; j++)
    {
        if (j!=i)       //Inicialmente solo tendremos componentes en ax, ya que la aceleracion en y se ira a cero pq todos estan en y=0.
        {
                ax[i]-=(m[j]*(x[i]-x[j]))/pow(sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)), 3); 

        }
               
    }

} 

for(i=0; i<nplanetas; i++)
{
  fprintf(fescribir, "%lf,%lf", x[i], y[i]);
  fprintf(fescribir, "\n"); 
}
fprintf(fescribir, "\n");



t=0;

while(t<time_max)
{

    for (i=0; i<nplanetas; i++)       
    {  
      ax[i]=0;
      ay[i]=0;
    }

      //yanterior[i]=y[i];

    for(i=0; i<nplanetas; i++)   //Ejecutamos el paso 2
    {
      x[i] = x[i] + h*vx[i] + (ax[i]*pow(h,2)*0.5); 
      y[i] = y[i] + h*vy[i] + (ay[i]*pow(h,2)*0.5); 

    }

    for(i=0; i<nplanetas; i++)
    {
      wx[i] = vx[i] + (h*ax[i]*0.5);
      wy[i] = vy[i] + (h*ay[i]*0.5);
    }

    for(i=0; i<nplanetas; i++)
    {
      wx[i] = vx[i] + (h*ax[i]*0.5);
      wy[i] = vy[i] + (h*ay[i]*0.5);

      
      for (j=0; j<nplanetas; j++)             //Ejecutamos el paso 3    
      {
        if (j!=i)
        {
          ax[i]-=(m[j]*(x[i]-x[j]))/pow( sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2)), 3);
          ay[i]-=(m[j]*(y[i]-y[j]))/pow( sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2)), 3);       
        }
      }
    } 

    for (i=0; i<nplanetas; i++)
    {
      vx[i]= vx[i] + wx[i] + (h*ax[i]*0.5);             //Ejecutamos el paso 4
      vy[i]= vy[i] + wy[i] + (h*ay[i]*0.5);
    }


    for (i=0; i<nplanetas; i++)
    {
      fprintf(fescribir,"%lf,%lf",x[i],y[i]);
      fprintf(fescribir, "\n");
    }

 

  fprintf(fenergias,"%lf", Etotal);
  fprintf(fenergias, "\n");
  fprintf(fescribir, "\n");

  Etotal = Energia(x, y, vx, vy, m, nplanetas);

 //  periodos(y[], yanterior[], t, nplanetas);

 t=t+h;  
}
        
fclose(fescribir);
fclose(fmasas);
fclose(fxo);
fclose(fvoy);
fclose(fenergias);


return 0;
}

 

//Funciones

double Energia(double x[], double y[], double vx[], double vy[], double m[], int nplanetas)
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


/*void periodos(double y[], double yanterior[],double t, int nplanetas)
{
  int i;
  double nvueltas[nplanetas];

  for(i=0; i<nplanetas; i++)
  {
    if(yanterior[i]<0)
    {
      if(yanterior[i]*y[i]<0)
      {
        nvueltas[i]=nvueltas[i]+1;
        periodo[i] = periodo[i] + (nvueltas[i])/t;

        printf("%lf", periodo[i]);
      }
      
    }

    

  }

  return;
}*/







//void segundopaso(double x[], double y[], double vx[], double vy[], double ax[], double ay[], double wx[], double wy[], int nplanetas,  double h)      //Paso 2
//{
  //  int i;

    //for (i=1; i<nplanetas; i++)
    //{
        
      //  x[i] = x[i] + h*vx[i] + (ax[i]*h*h)/2; 
        //y[i] = y[i] + h*vy[i] + (ay[i]*h*h)/2; 

 //       wx[i] = vx[i] + (h/2)*ax[i];
   //     wy[i] = vy[i] + (h/2)*ay[i];

 //   }

 //   return;
//}





//void tercerpaso(double m[], double x[], double y[], double ax[], double ay[], int nplanetas)     //Paso 3
//{
  //  int i, j;
    //double modulo, diferenciax, diferenciay, modulox, moduloy;

    //for(i=1; i<nplanetas; i++)      
    //{
        
      //  for (j=0; j<nplanetas; j++)
        //{
          //  if (j!=i)
           // {
             //   diferenciax=x[i]-x[j];
               // diferenciay=y[i]-y[j];

                //  modulox= pow(diferenciax, 2);
              //  moduloy= pow(diferenciay, 2);
               // modulo = modulox + moduloy;

                //ax[i]=(-m[j]*(diferenciax))/(pow(modulo, 3/2));  
                //ay[i]=(-m[j]*(diferenciay))/(pow(modulo, 3/2));         
            //}
            //else
            //{ 
            //break; 
            //}
               
        //}

    //} 

   // return;

//}





//void cuartopaso(double vx[], double vy[], double ax[], double ay[], double wx[], double wy[], int nplanetas,  double h)     //Paso 4
//{
  //  int i;

    //for (i=0; i<nplanetas; i++)
    //{
        
      //  vx[i]= wx[i] + (h/2)*ax[i];
        //vy[i]= wy[i] + (h/2)*ay[i];

    //}

    //return;
//}










