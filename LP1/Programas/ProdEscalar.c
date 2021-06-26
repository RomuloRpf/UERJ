#include <stdio.h>
#include <stdlib.h>
#include "vetinput.h"
#include "escalar.h"
int main()
{
    float v1[50]; float v2[50];
    float produto,verif = 1;
    char arq[256];
    int size1,size2;
    scanf("%s", arq);
    if ( vetinput(arq, v1, 1, &size1) )
    {
        return 0;
    }
    else
    {
        scanf("%s", arq);
        if ( vetinput(arq, v2, 2, &size2) )
        {
            return 0;
        }
        else
        {
            produto = escalar(v1,v2, size1, size2, &verif);
            if (verif)
                printf("%.3f", produto);
            return 0;
        }
    }
}