#ifndef _LISTENC_H
#define _LISTENC_H
struct vetor
{
  int chave;
  struct vetor *prox;
};
void inserefim(struct vetor**,int);
void imprimelista(struct vetor*);
void limparlista(struct vetor**);
#endif