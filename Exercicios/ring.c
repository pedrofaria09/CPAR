#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;

    if (world_rank == 0) {
      printf("Por favor introduza um numero \n");
      scanf("%d",&number);
      MPI_Send(&number, 1, MPI_INT, ++world_rank, 0, MPI_COMM_WORLD);
    } else if (world_rank != 0) {
        MPI_Recv(&number, 1, MPI_INT, (world_rank-1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received number %d from process %d\n", world_rank,number, world_rank-1);
        if(world_size-1 != world_rank)
          MPI_Send(&number, 1, MPI_INT, world_rank+1, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}