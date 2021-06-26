#include <stdio.h>

int main(void) 
{
  FILE *p;
  char frase[100];
  p = fopen("teste.txt","r");
  if(p == NULL)
  {
    printf("deu bosta");
    getchar();
  }
  while(fgets(frase,100,p) !=NULL)
  {
    printf("%s",frase);
  }
  fflush(p);
  fclose(p);
  return 0;
}