#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

  int numtasks, rank, rc;
  rc = MPI_Init(&argc, &argv);
  if (rc != MPI_SUCCESS)
  {
    printf("Erro ao iniciar o programa MPI. Encerrando programa.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  }
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("Numero de tasks = %d Meu rank é = %d\n", numtasks, rank);

  printf("Hello World\n");
  MPI_Finalize();
  return 0;
}