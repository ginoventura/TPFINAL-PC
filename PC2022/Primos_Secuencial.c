/*------------------------------------------------------*/
/*----------COMANDOS PARA COMPILAR Y EJECUTAR:----------*/
/*  	        1- gcc Primos_Secuencial.c       	    */
/*                     2- ./a.out                       */
/*------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

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

    int n, i;
    clock_t start, end;
    struct timeval start1, end1;
    double tiempo_total;

    gettimeofday(&start1, 0);
    start = clock();

    for (int i = 1; i <= 1000000; i++) {
            if (esPrimo(i)) {
                printf("Numero primo: %d\n", i);
            }
        }

    end = clock();
    gettimeofday(&end1, 0);
    long seconds = end1.tv_sec - start1.tv_sec;
    long microseconds = end1.tv_usec - start1.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("\n");

    tiempo_total = (end-start)/(double)CLOCKS_PER_SEC;

    printf("Tiempo de uso de CPU: %fs\n", tiempo_total);
    printf("Tiempo de ejecucion  total: %fs\n", elapsed);

    return 0;
}
