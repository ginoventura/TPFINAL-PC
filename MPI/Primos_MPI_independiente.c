/*------------------------------------------------------*/
/*-----------COMANDOS PARA COMPILAR Y EJECUTAR:---------*/
/*  	 1- mpicc -o mpi Primos_MPI_independiente.c     */
/*         2- mpirun --oversubscribe -np 8 ./mpi        */
/*------------------------------------------------------*/

/*FUNCIONA*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>

bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }

    return true;
}

int main(int argc, char **argv) {
    int rank, size;

    int n, i;
    clock_t start, end;
    double start1, end1;
    double tiempo_total;

    // Inicializamos MPI
    MPI_Init(&argc, &argv);

    // Determinamos el rango del proceso
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Numeros de procesos 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0) {
        printf("Numero de procesos = %d\n", size);
        start1 = MPI_Wtime();
        start = clock();
    }

    // Bloqueamos los procesos hasta que todos esten listos
    MPI_Barrier(MPI_COMM_WORLD);

    // Arranca del rango del proceso + 1
    // Incrementa a partir del numero de procesos
    for (int i = rank + 1; i <= 1000000; i += size) {
        if (esPrimo(i)) {
            printf("Proceso %d encontró el número primo: %d\n", rank, i);
        }
    }

    // Barrera para que se tome el tiempo real
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0){
        end1 = MPI_Wtime();
        end = clock();
        tiempo_total = (end-start)/(double)CLOCKS_PER_SEC;
        printf("Tiempo de uso de CPU: %fs\n", tiempo_total);
        printf("Tiempo de ejecucion total: %fs\n", end1 - start1);
    }

    MPI_Finalize();

    return 0;
}
