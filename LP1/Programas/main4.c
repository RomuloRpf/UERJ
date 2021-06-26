#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  float tf;
  float c[]={-10,0,10,20,30,40,50};
  int i;
  printf("Celsius     Fahrenheint\n");
  for(i=0;i<7;i++)
  {
    tf = (c[i]*9+160)/5;
    printf("%.2f        %.2f\n", c[i], tf);
  }
  return 0;
}