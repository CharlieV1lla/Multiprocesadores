#include<stdio.h>
#include<omp.h>
#include<math.h>
#define MPI 3.14159265358979323846
#define MEULER 2.71828182846
FILE *fptr;
double r1,r2,r3,r4;
long N=50000;

void main()
{
    const double startTime = omp_get_wtime();

    //Primera ecuacion
    fptr=fopen("Rugen_n_20000.txt","w");
    fprintf(fptr, "Datos que encuentra el metodo de Runge-Kutta(variable ind.\t variable dep.\t numero de thread)\n");
    double h,t,w,ab;
    double w0=MPI/4,a=0,b=MPI, k1,k2,k3,k4;
    int i;
    w=w0;
    h=(b-a)/N;
    fprintf(fptr, "%f\t %f\n", a, w);
    for(i=0;i<N;i++){
        t=a+(h*i);
        k1=h*(t*pow(MEULER,3.0*t)-2.0*w);
        k2=h*((t+h/2.0)*pow(MEULER,3.0*(t+h/2.0))-2.0*(w+k1/2.0));
        k3=h*((t+h/2.0)*pow(MEULER,3.0*(t+h/2.0))-2.0*(w+k2/2.0));
        k4=h*((t+h)*pow(MEULER,3.0*(t+h))-2.0*(w+k3));
        w=w+(k1+2.0*k2+2.0*k3+k4)/6.0;
        fprintf(fptr, "%f\t %f\n", a, w);
    }
    fclose(fptr);

    //Segunda ecuacion
    fptr=fopen("Rugen_n_10000.txt","w");
    fprintf(fptr, "Datos que encuentra el metodo de Runge-Kutta(variable ind.\t variable dep.\t numero de thread)\n");
    
    w0=MPI/4;
    a=0;
    b=MPI;
    w=w0;
    h=(b-a)/N;
    fprintf(fptr, "%f\t %f\n", a, w);
    for(i=0;i<N;i++){
        t=a+(h*i);
        k1=h*(1+pow(t-w,2));
        k2=h*(1+pow(t+h/2.0-w-k1/2.0,2));
        k3=h*(1+pow(t+h/2.0-w-k2/2.0,2));
        k4=h*(1+pow(t+h-w-k3,2));
        w=w+(k1+2.0*k2+2.0*k3+k4)/6.0;
        fprintf(fptr, "%f\t %f\n", a, w);
    }
    fclose(fptr);

    //Tercera ecuacion
    fptr=fopen("Rugen_n_10000.txt","w");
    fprintf(fptr, "Datos que encuentra el metodo de Runge-Kutta(variable ind.\t variable dep.\t numero de thread)\n");
    
    w0=MPI/4;
    a=0;
    b=MPI;
    w=w0;
    h=(b-a)/N;
    fprintf(fptr, "%f\t %f\n", a, w);
    for(i=0;i<N;i++){
        t=a+(h*i);
        k1=h*(1+w/t);
        k2=h*(1+(w+k1/2.0)/(t+h/2.0));
        k3=h*(1+(w+k2/2.0)/(t+h/2.0));
        k4=h*(1+(w+k3)/(t+h));
        w=w+(k1+2.0*k2+2.0*k3+k4)/6.0;
        fprintf(fptr, "%f\t %f\n", a, w);
    }
    fclose(fptr);


    //Cuarta ecuacion
    fptr=fopen("Rugen_n_200.txt","w");
    fprintf(fptr, "Datos que encuentra el metodo de Runge-Kutta(variable ind.\t variable dep.\t numero de thread)\n");
    
    w0=MPI/4;
    a=0;
    b=MPI;
    w=w0;
    h=(b-a)/N;
    fprintf(fptr, "%f\t %f\n", a, w);
    for(i=0;i<N;i++){
        t=a+(h*i);
        k1=h*(cos(2*t*w)+sin(3*t*w));
        k2=h*(cos(2*(t+h/2.0)*(w+k1/2.0))+sin(3*(t+h/2.0)*(w+k1/2.0)));
        k3=h*(cos(2*(t+h/2.0)*(w+k2/2.0))+sin(3*(t+h/2.0)*(w+k2/2.0)));
        k4=h*(cos(2*(t+h)*(w+k3))+sin(3*(t+h)*(w+k3)));
        w=w+(k1+2.0*k2+2.0*k3+k4)/6.0;
        fprintf(fptr, "%f\t %f\n", a, w);
    }
    fclose(fptr);

    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n", (endTime - startTime));
}
