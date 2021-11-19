#include<stdio.h>
#include<omp.h>
#include <stdlib.h>
static long num_pasos = 100000000;   //1 215 752 192
double paso;
//#define NUM_THREADS 900
void main(int argc, char *argv[])
{
    int NUM_THREADS;
    NUM_THREADS=atoi(argv[1]);
    int i, nthreads;
    double resul, sum[NUM_THREADS];
    double a = 1.0;
    double b = 2.0;
    paso = (b-a)/num_pasos;
    omp_set_num_threads(NUM_THREADS);
    const double startTime = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id, nthrds; double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0)
            nthreads=nthrds;
            for (i=id, sum[id]=0.0; i<num_pasos; i=i+nthrds)
            {
                x=(i+0.5)*paso+a;
                sum[id]+=1.0/(x);
                
            }
            
    }

    for (i=0,resul=0.0;i<nthreads;i++){
        resul+=sum[i]*paso;
    }
    const double endTime = omp_get_wtime();
    printf("threads = %d\n", NUM_THREADS);
    printf("la integral definida da como resultado = (%lf)\n", resul);
    printf("tomo (%lf) segundos\n", (endTime - startTime));
}
