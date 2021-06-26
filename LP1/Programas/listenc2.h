#ifndef _LISTENC2_H
#define _LISTENC2_H
struct vetor
{
  int chave,chave2;
  struct vetor *prox;
};
void insereinicio(struct vetor**,int,int);
void imprimelista(struct vetor*);
void limparlista(struct vetor**);
void imprimechave(struct vetor*);
#endif