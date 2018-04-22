#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int n=200,number;
  float** a = (float**) malloc(sizeof(float*)*n);
  float** b = (float**) malloc(sizeof(float*)*n);
  float** c = (float**) malloc(sizeof(float*)*n);

  for (int i = 0; i < n; i++){
    a[i] = (float*) malloc(sizeof(float)*n);
    b[i] = (float*) malloc(sizeof(float)*n);
    c[i] = (float*) malloc(sizeof(float)*n);
  }

  //Filling all the positions of the matrix a with value 1
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
    {
      a[i][j] = 1;
    }
  }

  //Filling all the positions of the matrix b with value 1
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
    {
      b[i][j] = 1;
    }
  }

  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);



  //MUL
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

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