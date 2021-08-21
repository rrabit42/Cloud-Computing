#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


int main(void){
  int A[10][10];
  int B[2][10];
  int my_rank, size, i, j;
  
  /* Start up MPI */
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  if(my_rank == 0){
    for(i=0; i<10; i++){
      for(j=0; j<10; j++){
        A[i][j] = i*10+j;
      }
    }
  }
  
  MPI_Scatter(A, 20, MPI_INT, B, 20, MPI_INT, 0, MPI_COMM_WORLD);
  
  if(my_rank == 3){
    for(i=0; i<2; i++){
      for(j=0; j<10; j++){
        printf("%d ", B[i][j]);
      }
      printf("\n");
    }
  }
  
  /* Shut down MPI */
  MPI_Finalize();
  
  return 0;
}
