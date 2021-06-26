#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
int levet(float **);
void somavet(float **, float **, int);
int main()
{
    float *vet1, *vet2;
    int size1, size2;
    size1 = levet(&vet1);
    printf("%d", size1);
    size2 = levet(&vet2);
    printf("%d", size2);
    if (size1 != size2)
    {
        printf("Erro: os vetores tem que ter o mesmo tamanho.\n");
    }
    else
    {
        somavet(&vet1, &vet2, size1);
    }
    free(vet1); free(vet2);
    vet1 = NULL; vet2 = NULL;
    return 0;
}
int levet(float **vet)
{
    char *buffer = (char*) malloc(MAXSIZE);
    int verif = 1, len;
    fgets(buffer, MAXSIZE, stdin);
    sscanf(buffer, "%d", &len);
    *vet = (float *) malloc(len*sizeof(float));
    while (*buffer != '\n')
    {
        if (verif)
        {
            sscanf(buffer, "%f", *vet++);
            verif = 0;
        }
        else if (*buffer == ' ')
        {
            verif = 1;
        }
        buffer++;
    }
    free(buffer);
    buffer = NULL;
    return len;
}
void somavet(float **v1, float **v2, int tamanho)
{
    int i;
    printf("%d ", tamanho);
    for (i=0; i< tamanho; i++)
    {
        **(v1+i) += **(v2+i);
        printf("%1.1f ", **(v1+i));
    }
    printf("%1.1f", **(v1+i)); 
}
