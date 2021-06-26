#ifndef _LISTENC3_H
#define _LISTENC3_H
struct vetor
{
  int chave,chave2;
  struct vetor *prox;
};
void insereinicio(struct vetor**,int,int);
void imprimelista(struct vetor*);
void limparlista(struct vetor**);
void imprimechave(struct vetor*);
struct vetor* buscachave(int,int,struct vetor*);
void excluirelem(int, int,struct vetor**);
#endif