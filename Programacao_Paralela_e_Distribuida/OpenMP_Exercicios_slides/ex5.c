#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  double sum;
  double a[256], b[256];
  int n = 256, i;

  for (i = 0; i < n; i++)
  {
    a[i] = i * 0.5;
    b[i] = i * 2.0;
  }
  sum = 0;

#pragma omp parallel for shared(a, b, n, sum) private(i) reduction(+ : sum)
  for (i = 1; i < n; i++)
  {
    sum = sum + a[i] * b[i];
  }
  printf("sum = %f\n", sum);
}
