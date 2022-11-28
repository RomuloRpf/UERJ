#include <iostream>
#include <cmath>
#define N 10000

int main()
{
  float a[N], b[N];
  int i, n;
  float temp, csum;
  n = N;
  csum = 0.0;

#pragma omp parallel for shared(a, b, n) private(temp, i) firstprivate(csum)
  for (i = 0; i < n; i++)
  {
    temp = a[i] / b[i];
    csum += cos(temp);
  }
  std::cout << csum << std::endl;
}