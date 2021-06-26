#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(void)
{
  char octal[100], *bin, *hex;
  int i,j,tb,th,aux,x;
  fgets(octal,100,stdin);
  tb=(strlen(octal)-1)*3;
  j=tb;
  bin=(char*)malloc(tb*sizeof(char));
  for(i=(strlen(octal)-2);i>=0;i--)
  {
    aux=octal[i]-'0';
    for(x=0;x<3;x++)
    {
      bin[j]=aux%2+'0';
      aux=aux/2;
      j--;
    }
  }
  for(i=0;i<=tb;i++)
  {
    printf("%c",bin[i]);
  }

  th=(strlen(bin)-1)/4;
  hex=(char*)malloc(tb*sizeof(char));
  for(i=(strlen(bin)-2);i>=0;i--)
  {
    aux=bin[i]-'0';
    for(x=0;x<=4;x++)
    {
      hex[j]=aux*pow(2,x)+'0';
      aux=aux/2;
      j--;
    }
  }
  return 0;

}
