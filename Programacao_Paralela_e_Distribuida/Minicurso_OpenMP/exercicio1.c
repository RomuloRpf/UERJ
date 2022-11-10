#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
  int thread_num = 0;
  // omp_set_num_threads(2); muda o numero de threads usadas pelo omp

#pragma omp parallel
  {
#if _OPENMP
    thread_num = omp_get_thread_num();
#endif

    printf("Hello World from %d:)\n", thread_num);
  }

  return 0;
}