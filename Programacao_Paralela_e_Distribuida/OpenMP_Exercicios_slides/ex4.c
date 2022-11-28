#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n, i;
  double pi, h, sum, x, a;
  n = atoi(argv[1]);
  h = 1.0 / (double)n;
  sum = 0.0;

#pragma omp parallel for private(i, x) shared(h) reduction(+ \
                                                           : sum)
  for (i = 1; i <= n; i++)
  {
    x = h * ((double)i - 0.5);
    sum += 4.0 / (1.0 + x * x);
  }
  pi = h * sum;
  printf("pi is approximately %.16f", pi);
  return 0;
}