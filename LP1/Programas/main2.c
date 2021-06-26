#include <stdio.h>
#include <stdlib.h>
#include "listenc2.h"

int main(void) 
{
  struct vetor *phead=NULL;
  int tam,i,valor,valor2;
  scanf("%d",&tam);
  for(i=0;i<tam;i++)
  {
    scanf("%d %d",&valor,&valor2);
    insereinicio(&phead,valor,valor2);
  }
  imprimelista(phead);
  limparlista(&phead);
}

struct vetor * criano(int x,int y)
{
  struct vetor *p=(struct vetor*)malloc(sizeof(struct vetor));
  p->chave=x;
  p->chave2=y;
  return p;
}

void insereinicio(struct vetor**p,int x,int y)
{
  struct vetor*elem=criano(x,y);
  elem->prox=(*p);
  *p=elem;
}

void imprimelista(struct vetor*p)
{
  if(p)
  {
    imprimechave(p);
    imprimelista(p->prox);
  }
  else
  {
    printf("fim da lista\n");
  }
}

void imprimechave(struct vetor*e)
{
  if(e)
  {
    printf("(%hd,%hd)",e->chave,e->chave2);
  }
}

void liberar(struct vetor*e)
{
  free(e);
}

void limparlista(struct vetor**p)
{
  if(*p)
  {
    limparlista(&(*p)->prox);
    liberar(*p);
    *p=NULL;
  }
}