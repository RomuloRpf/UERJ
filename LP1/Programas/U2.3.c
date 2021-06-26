#include <stdio.h>
#include <string.h>

int main(void) 
{
  char str[100];
  int i,j;
  fgets(str,100,stdin);
  j=strlen(str)-2;
  for(i=0;i<=j;i++)
  {
    if(str[i] != str[j])
    {
      printf("NAO\n");
      break;
    }
    else if (i==j || i>j)
    {
      printf("SIM\n");
    }
    j--;
  }
  return 0;
}