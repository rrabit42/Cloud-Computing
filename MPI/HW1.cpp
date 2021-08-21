#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define NUM 1000

int main(void){
  int A[NUM], B[NUM];
  int my_rank, size, i, task, result = 0;
  int myresult = 0;
  
  // 배열에 난수값 넣기
  for(i = 0; i < NUM; i++){
    A[i] = (rand() % 100) + 1;
  }
  
  /* Start up MPI */
  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  // 각 프로세스가 일할 양(어차피 홀수 검색에 걸리는 시간은 모두 동일할 것이므로)
  task = NUM / size;
  
  MPI_Scatter(A, task, MPI_INT, B, task, MPI_INT, 0, MPI_COMM_WORLD);

  for(i = 0; i < task; i++){
    if(B[i] % 2 != 0){ myresult += 1; }
  }
  
  MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  
  if(my_rank == 0){
    printf("홀수의 개수는 %d입니다.\n", result);
  }
  
  /* Shut down MPI */
  MPI_Finalize();
  
  return 0;
}
