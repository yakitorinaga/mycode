#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n=2;

double func_f(double *x,double t){
    return x[1];
}

double func_g(double *x,double t){
    return (1.0-pow(x[0],2.0))*x[1]-x[0];
}

void rk4(double *x,double t,double dt,double *k0,double *k1,double *k2,double *k3,int n,double (*pf[])(double*,double)){
    double tmp_k1[n];
    double tmp_k2[n];
    double tmp_k3[n];
    for(int i=0;i<=n-1;i++){
        k0[i]=pf[i](x,t);
    }
    for(int i=0;i<=n-1;i++){
        tmp_k1[i]=x[i]+0.5*dt*k0[i];
    }
    for(int i=0;i<=n-1;i++){
        k1[i]=pf[i](tmp_k1,t+0.5*dt);
    }
    for(int i=0;i<=n-1;i++){
        tmp_k2[i]=x[i]+0.5*dt*k1[i];
    }
    for(int i=0;i<=n-1;i++){
        k2[i]=pf[i](tmp_k2,t+0.5*dt);
    }
    for(int i=0;i<=n-1;i++){
        tmp_k3[i]=x[i]+dt*k2[i];
    }
    for(int i=0;i<=n-1;i++){
        k3[i]=pf[i](tmp_k3,t+dt);
    }
    for(int i=0;i<=n-1;i++){
        x[i]=x[i]+dt*(1.0/6.0)*(k0[i]+2.0*k1[i]+2.0*k2[i]+k3[i]);
    }
}

int main(){
    double t;
    double *x;
    x=(double*)malloc(sizeof(double)*n);
    double *k0,*k1,*k2,*k3;
    k0=(double*)malloc(sizeof(double)*n);
    k1=(double*)malloc(sizeof(double)*n);
    k2=(double*)malloc(sizeof(double)*n);
    k3=(double*)malloc(sizeof(double)*n);

    x[0]=0.1;
    x[1]=0.0;
    double t_max=50.0;
    double dt=0.01;
    double l=(t_max)/dt;
    double (*pf[n])(double*,double);
    pf[0]=func_f;
    pf[1]=func_g;

    for(int i=0;i<=l;i++){
        t=i*dt;
        rk4(x,t,dt,k0,k1,k2,k3,n,pf);
        printf("%f %.9e %.9e\n",t,x[0],x[1]);
    }
    free(x);
    free(k0);
    free(k1);
    free(k2);
    free(k3);
    return 0;
}