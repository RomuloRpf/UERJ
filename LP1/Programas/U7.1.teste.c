#include <stdio.h>
#include "prototipo.h"

int main(void) {
  float max, min;
  scanf("%f%f", &max, &min);
  maxmin(max,min);
  return 0;
}

void maxmin(float max,float min)
{
  if(max < min)
  {
    swap(&max,&min);
    printf("%f\n%f\n",max,min);
  }
  else printf("%f\n%f\n",max,min);
}

void swap(float* x, float* y)
{
  float temp;
  temp = *x;
  *x = *y;
  *y = temp;
}