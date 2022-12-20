#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int inmsg, outmsg, numtasks, rank, dest, source, count, tag = 1;
  MPI_Status Stat; 

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0) {

    FILE *f = fopen(argv[2],"w");
    if(f == NULL) {
      printf("Não foi possível abrir o arquivo.\n");
    }

    dest = 1;
    outmsg = atoi(argv[1] + rank);
    MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

    fprintf(f,"Proc Tag Msg\n");
    for(int i = 1; i < numtasks; i++) {
      MPI_Recv(&inmsg, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
      MPI_Get_count(&Stat, MPI_INT, &count);
      fprintf(f,"%d \t %d \t %d\n", Stat.MPI_SOURCE, Stat.MPI_TAG, inmsg);
    }
    fclose(f);
  }
  else{
    source = rank - 1;
    MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
    outmsg = inmsg + rank;
    MPI_Send(&outmsg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    if(rank < numtasks - 1){
      dest = rank + 1;
      MPI_Send(&outmsg, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      }
  }

  MPI_Finalize();
  return 0;
}
