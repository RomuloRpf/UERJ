#include <stdio.h>
#include <stdlib.h>

void swap(int*,int*);

int main(void) {
  int **p,i,j,l,c;

  scanf("%d %d",&l,&c);
  p=(int**)malloc(l*sizeof(int*));
  for(i=0;i<l;i++)
  { 
    p[i]=(int*)malloc(c*sizeof(int));
    for(j=0;j<c;j++)
    {
      scanf("%d",&p[i][j]);
    }
  }
  swap(&l,&c);
  for(i=0;i<l;i++)
  {
    printf("\n");
    for(j=0;j<c;j++)
    {
      printf("%d",p[i][j]);
      if(j!=c-1)
      {
        printf("%c",' ');
      }
    }
  }
  for(i=0;i<l;i++)
  {
    free(p[i]);
  }
  free(p);
  return 0;
}
void swap(int*x,int*y)
{
  int temp;
  temp=*x;
  *x=*y;
  *y=temp;
}