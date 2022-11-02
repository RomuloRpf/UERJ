#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRINT_MSG(NUM) printf("\n\n***********\n     %d     \n***********\n\n",NUM);

struct histograma{
	unsigned int Maximo;
	long int *Vetor;
};

struct histograma criaHistograma(char*);
int ComparaHistogramas(struct histograma, struct histograma);
void deletaHistograma(struct histograma*);
void imprimeHistograma(struct histograma);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Erro: numero de argumentos deve ser igual a três\n");
		return 1;
	}
   
   struct histograma Histograma1 = criaHistograma(argv[1]);
	imprimeHistograma(Histograma1);
    
	struct histograma Histograma2 = criaHistograma(argv[2]);
	imprimeHistograma(Histograma2);

	if (ComparaHistogramas(Histograma1, Histograma2))
		printf("Os histogramas das imagens %s e %s são idênticos\n\n",argv[1],argv[2]);
	else
		printf("Os histogramas das imagens %s e %s são distintos\n\n",argv[1],argv[2]);

	deletaHistograma(&Histograma1);
	deletaHistograma(&Histograma2);
}


struct histograma criaHistograma(char* nome)
{
	FILE* arq;
	struct histograma leitura;
	char tipo[30];
	int coluna,linha,aux,i,j;
	arq = fopen(nome,"r");
    if(arq==NULL)
    {
        printf("Erro arquivo inexistente\n");
        exit(1);
    }
	fscanf(arq,"%s",tipo);
	fscanf(arq,"%d %d",&coluna,&linha);
	fscanf(arq,"%d",&leitura.Maximo);
	leitura.Vetor=(long int*)malloc(((leitura.Maximo)+1)*(sizeof(long int)));
    for(i=0;i<=leitura.Maximo;i++)
    {
        leitura.Vetor[i]=0;
    }
	for(i=0;i<linha;i++)
	{
		for(j=0;j<coluna;j++)
		{
			fscanf(arq,"%d",&aux);
			leitura.Vetor[aux]+=1;	
		}
	}
	fclose(arq);
	return leitura;
}

int ComparaHistogramas(struct histograma h1,struct histograma h2)
{
	int i;
	if(h1.Maximo!=h2.Maximo)
	{
		return 0;
	}
	else
	{
		for(i=0;i<=h1.Maximo;i++)
		{
			if(h1.Vetor[i]!=h2.Vetor[i])
			{
				return 0;
			}
		}
	}
    return 1;
}

void deletaHistograma(struct histograma* p)
{
	(p->Maximo)=0;
	free(p->Vetor);
    p->Vetor=NULL;
}

void imprimeHistograma(struct histograma h)
{
    int i;
    printf("Histograma\n");
    for(i=0;i<=h.Maximo;i++)
    {
        printf("%d->%ld\n",i,h.Vetor[i]);
    }
    printf("\n");	
}
