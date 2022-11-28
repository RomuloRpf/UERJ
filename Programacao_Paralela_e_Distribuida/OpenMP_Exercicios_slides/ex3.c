#include <stdlib.h>
#include <stdio.h>
#define SIZE 1000 /* Max size of matrices */
int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

int main(int argc, char *argv[])
{
  int i, j, k, N;
  N = atoi(argv[1]);
  fill_matrix(A);
  fill_matrix(B);
#pragma omp parallel shared(A, B, C, N) private(i, j, k)
#pragma omp for
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      C[i][j] = 0.0;
      for (k = 0; k < N; k++)
      {
        C[i][j] = C[i][j] + A[i][k] * B[k][j];
      }
    }
  }
}