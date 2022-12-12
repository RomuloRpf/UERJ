#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  double start, end, *vec;
  int size, trocas, numtasks, rank, count, dest, source, tag = 1;
  MPI_Status Stat;

  MPI_Init(&argc, &argv);
  start = MPI_Wtime();
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  size = atoi(argv[1]);
  trocas = atoi(argv[2]);

  vec = (double *)malloc(sizeof(double) * size);
  for (int i = 0; i < size; i++)
  {
    vec[i] = -1.0;
  }

  if (rank == 0)
  {
    dest = 1;
    source = 1;
    for (int i = 0; i < trocas; i++)
    {
      for (int j = 0; j < size; j++)
      {
        vec[j] = 2.0;
      }
      MPI_Send(vec, size, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
      MPI_Recv(vec, size, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &Stat);
    }
  }
  else
  {
    dest = 0;
    source = 0;
    for (int i = 0; i < trocas; i++)
    {
      MPI_Recv(vec, size, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &Stat);
      for (int j = 0; j < size; j++)
      {
        vec[j] = 4.0;
      }
      MPI_Send(vec, size, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }
  }

  end = MPI_Wtime() - start;
  printf("time = %10.10lf\n", end);
  MPI_Finalize();
  return 0;
}
