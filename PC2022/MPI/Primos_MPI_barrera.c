/*------------------------------------------------------*/
/*-----------COMANDOS PARA COMPILAR Y EJECUTAR:---------*/
/*  	   1- mpicc -o mpi Primos_MPI_barrera.c	        */
/*         2- mpirun --oversubscribe -np 8 ./mpi       */
/*------------------------------------------------------*/

/* NO FUNCIONA */

#include <mpi.h>
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

int main(int argc, char **argv) {
    
    clock_t start, end;
    double start1, end1;
    double tiempo_total;

    int size, rank;
    
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        printf("Numero de procesos = %d\n", size);
        start1 = MPI_Wtime();
        start = clock();
    }

    int j = 1;
    //MPI_Win win;
    //MPI_Win_create(&j, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    // Bloqueamos los procesos hasta que todos esten listos
    MPI_Barrier(MPI_COMM_WORLD);

    // Arranca del rango del proceso + 1
    // Incrementa a partir del numero de procesos
    // Por ejemplo con 8 procesos: Proceso 0: 1, 9, 17... 
    for (int i = rank + 1; i <= 1000000; i += size) {
        //MPI_Win_lock(MPI_LOCK_SHARED, rank, 0, win);
        if (esPrimo(i)) {
            printf("Proceso %d encontró el número primo: %d\n", rank, i);
        }
        // Comunicamos a los demas procesos el numero que se evaluó
        MPI_Bcast(&j, 1, MPI_INT, rank, MPI_COMM_WORLD);
    }
   
    //MPI_Win_unlock(rank, win);
    //MPI_Win_free(&win);

    // Bloqueamos los procesos hasta que todos terminen para obtener el tiempo real
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

/* 
void my_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator) {
  int world_rank;
  MPI_Comm_rank(communicator, &world_rank);
  int world_size;
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root) {
    // If we are the root process, send our data to everyone
    int i;
    for (i = 0; i < world_size; i++) {
      if (i != world_rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    // If we are a receiver process, receive the data from the root
    MPI_Recv(data, count, datatype, root, 0, communicator,
             MPI_STATUS_IGNORE);
  }
}
*/
