/*------------------------------------------------------*/
/*-----------COMANDOS PARA COMPILAR Y EJECUTAR:---------*/
/*  	   1- gcc -fopenmp Primos_OMP_barrera.c    	    */
/*                     2- ./a.out                       */
/*------------------------------------------------------*/

#include <omp.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

int main() {
    int nthreads = 8, tid;

    int n, i, j=1;
    clock_t start, end;
    double start1, end1;
    double tiempo_total;

    start1 = omp_get_wtime();
    start = clock();

    #pragma omp parallel private(nthreads, tid) shared(j)
    {
        tid = omp_get_thread_num();
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Numero de hilos = %d\n", nthreads);
        }

        while(j <= 1000000) {
            // El primer hilo que ingresa a la seccion critica, verifica si es primo
            // Luego incrementa el valor de J
            #pragma omp critical
            {
                if(j <= 1000000 && esPrimo(j)) {
                    printf("Hilo %d encontró el número primo: %d\n", tid, j);
                }
                j++;
            }
        }
    }

    end = clock();

    printf("\n");

    tiempo_total = (end-start)/(double)CLOCKS_PER_SEC;
    end1 = omp_get_wtime();

    printf("Tiempo de uso de CPU: %fs\n", tiempo_total);
    printf("Tiempo de ejecucion total: %fs\n", end1 - start1);

    return 0;
}