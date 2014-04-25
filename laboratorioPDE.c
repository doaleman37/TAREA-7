#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
  int i,j;  
  int n_x=1000;
  int n_t=atoi(argv[1]);
  float *x;
  x=malloc(n_x*sizeof(float));
  float dx=1.0/1000.0;
  
   for(i=0;i<n_x;i++){
    x[i]=(i*1.0)/(n_x);  
}
  float *u_inicial;
  u_inicial=malloc(n_x*sizeof(float));
  for(i=0;i<n_x;i++){
   u_inicial[i]=u_inicial[i]=exp(-((x[i]-0.3)*(x[i]-0.3))/0.01);
 }
  
  float dt=0.0005;
  float c = 1.0;
  float r = c*dt/dx;
  
  float *u_pasado;
  float *u_presente;
  float *u_futuro;
  u_pasado=malloc(n_x*sizeof(float));
  u_presente=malloc(n_x*sizeof(float));
  u_futuro=malloc(n_x*sizeof(float));
  
  /*condiciones iniciales*/
  u_inicial[0]=0.0;
  u_inicial[n_x-1]=0.0;
  u_pasado[0]=0.0;
  u_pasado[n_x-1]=0.0;
  u_presente[0]=0.0;
  u_presente[n_x-1]=0.0;
  u_futuro[0]=0.0;
  u_futuro[n_x-1]=0.0;
  

  /*primer paso*/
  for(i=1;i<n_x-1;i++){
   u_futuro[i]=u_inicial[i]+((pow(r,2)/2.0)*(u_inicial[i+1]-(2.0*u_inicial[i])+u_inicial[i-1]));  
}

for(i=0;i<n_x;i++)
     {
       u_pasado[i]=u_inicial[i];
     }
for(i=0;i<n_x;i++)
     {
       u_presente[i]=u_futuro[i];
     }
 FILE *IN;
 IN=fopen("datos.dat","w");

 /*se repite el proceso n_t veces y se evalua la funcion en distintos tiempos*/
 for(j=0;j<n_t;j++) {
      for(i=1;i<n_x-1;i++){
u_futuro[i]=(2.0*(1.0-pow(r,2.0)))*u_presente[i]-u_pasado[i]+(pow(r,2.0))*(u_presente[i+1]+u_presente[i-1]);
}
     
for(i=0;i<n_x;i++)
     {
       u_pasado[i]=u_presente[i];
     }
for(i=0;i<n_x;i++)
     {
       u_presente[i]=u_futuro[i];
     }

 }
 /*Guardo el estado final de la funciòn despuès de n_t iteraciones en un archivo .dat*/

for(i=0;i<n_x;i++){
fprintf(IN,"%f %f\n",x[i],u_presente[i]);
}
 
 fclose(IN);

}
