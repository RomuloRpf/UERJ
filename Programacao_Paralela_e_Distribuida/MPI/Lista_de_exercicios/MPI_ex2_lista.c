#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int inmsg, outmsg, numtasks, rank, count, tag;
  MPI_Status Stat; 

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {

    FILE *f = fopen(argv[1],"w");
    if(f == NULL) {
      printf("Não foi possível abrir o arquivo.\n");
    }
    fprintf(f,"Proc Tag Msg\n");

    for(int i = 0; i < (numtasks - 1)*100; i++) {
      MPI_Recv(&inmsg, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Stat);
      MPI_Get_count(&Stat, MPI_INT, &count);
      fprintf(f,"%d \t %d \t %d\n", Stat.MPI_SOURCE, Stat.MPI_TAG, inmsg);
    }
    fclose(f);
  }
  else{
    srand(time(NULL));
    for(int i = 0; i < 100; i++){
      outmsg = rand() % 100;
      tag = rand() % 100;
      MPI_Send(&outmsg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}
