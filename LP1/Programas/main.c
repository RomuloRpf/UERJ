#include <stdio.h>
#include <stdlib.h>
#include "listenc.h"

int main(void) 
{
  struct vetor *phead=NULL;
  int tam,i,valor;
  scanf("%d",&tam);
  for(i=0;i<tam;i++)
  {
    scanf("%d",&valor);
    inserefim(&phead,valor);
  }
  imprimelista(phead);
  limparlista(&phead);
}

struct vetor * criano(int x)
{
  struct vetor*p=(struct vetor*)malloc(sizeof(struct vetor));
  p->chave=x;
  return p;
}

void inserefim(struct vetor**p,int valor)
{
  if(*p)
  {
    inserefim(&((*p)->prox),valor);
  }
  else
  {
    struct vetor * elem = criano(valor);
    elem->prox=NULL;
    *p=elem;
  }
}

void imprimechave(struct vetor*e)
{
  if(e)
  {
    printf("%hd ",e->chave);
  }
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
    printf("Fim da lista\n");
  }
}

void liberachave(struct vetor *e)
{
  free(e);
}

void limparlista(struct vetor**p)
{
  if(*p)
  {
    limparlista(&(*p)->prox);
    liberachave(*p);
    *p=NULL;
  }
}