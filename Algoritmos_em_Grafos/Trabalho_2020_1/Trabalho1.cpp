#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include "Trabalho1.h"

using namespace std;

vector<Grafo>colecaoDegrafos;
vector<Grafo*>apontadoresGrafos;



bool Comparador(Grafo*a, Grafo*b)
{
    return (a->getNomeGrafo() < b->getNomeGrafo());
}

int** CompletaMatriz(int** p,int n)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=i; j<n; j++)
        {
            if(i==j)
            {
                p[i][j] = 0;
            }
            else
            {
                p[j][i] = p[i][j];
            }
        }
    }
    return p;
}

void ImprimeMatriz(int **M, int n)
{
    int i,j;
    cout<<endl;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(j==(n-1))
            {
                printf("%d ",M[i][j]);
                cout<<endl;
            }
            else
            {
                printf("%d ",M[i][j]);
            }
        }
    }
    cout << endl;
}

void CarregaGrafo()
{
    int fim = apontadoresGrafos.size(), comeco = 0, i;
    string nome;
    if(fim > 0)
    {
        cout << "Digite o nome do grafo que quer carregar: ";
        cin >> nome;
        while(comeco <= fim)
        {
            i = floor((comeco + fim)/2);
            if(nome < apontadoresGrafos[i]->getNomeGrafo())
            {
                fim = i-1;
            }
            else if(nome > apontadoresGrafos[i]->getNomeGrafo())
            {
                comeco = i+1;
            }
            else
            {
                comeco = fim+1;
            }
        }
        if(apontadoresGrafos[i]->getNomeGrafo() == nome)
        {
            ImprimeMatriz(apontadoresGrafos[i]->getMatriz(),apontadoresGrafos[i]->getTamanhoMatriz());
        }
        else
        {
            cout << "\nNao existe um grafo com esse nome!" << endl << endl;
        }
    }
    else
    {
        cout << "Nao ha grafos armazenados!" << endl << endl;
    }

}

int** CriaMatriz(int n)
{
    int i,j,**p = NULL;
    p = (int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++)
    {
        p[i] = (int*)malloc(n*sizeof(int));
        for(j=i+1; j<n; j++)
        {
            printf("Digite o elemento %d %d: ",i,j);
            cin >> p[i][j];
        }
    }
    p = CompletaMatriz(p,n);
    ImprimeMatriz(p,n);
    return p;
}

void ImprimeNoArquivo()
{
    ofstream arquivo;
    int i,j, n,**p = NULL,fim = apontadoresGrafos.size();
    arquivo.open("grafos.txt",ios::app);
    arquivo << apontadoresGrafos[fim-1]->getNomeGrafo() << " ";
    n = apontadoresGrafos[fim-1]->getTamanhoMatriz();
    arquivo << n << " ";
    p = apontadoresGrafos[fim-1]->getMatriz();
    for(i=0; i<(n-1); i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(i==(n-2))
            {
                arquivo << p[i][j] <<endl;
            }
            else
            {
                arquivo << p[i][j] << " ";
            }


        }
    }
    arquivo.close();
}

void CriaGrafo()
{
    string nome;
    int n;
    cout << "Digite o nome do grafo: ";
    cin >> nome;
    try
    {
        cout << "Digite um numero inteiro positivo: ";
        if(scanf("%d",&n)>0)
        {
            cout<<endl;
            Grafo *novoGrafo = new Grafo(nome,CriaMatriz(n),n);
            apontadoresGrafos.push_back(novoGrafo);
            colecaoDegrafos.push_back(*(novoGrafo));
            ImprimeNoArquivo();
        }
        else
        {
            throw invalid_argument("n invalido");
        }
    }
    catch(invalid_argument& e)
    {
        cout << "\n-------Digite um numero valido!!!------\n"<< endl;
    }
}

void LerArquivo()
{
    Grafo *novoGrafo;
    FILE *arq;
    char nome[20];
    int n,i,j,**p = NULL;
    arq = fopen("grafos.txt","r");
    while(fscanf(arq,"%s",nome) > 0)
    {
        fscanf(arq,"%d", &n);
        p = (int**)malloc(n*sizeof(int*));
        for(i=0; i<n; i++)
        {
            p[i] = (int*)malloc(n*sizeof(int));
            for(j=i+1; j<n; j++)
            {
                fscanf(arq,"%d",&p[i][j]);
            }
        }
        p = CompletaMatriz(p,n);
        novoGrafo = new Grafo(nome,p,n);
        apontadoresGrafos.push_back(novoGrafo);
        colecaoDegrafos.push_back(*(novoGrafo));
    }
    fclose(arq);
}

void CriaGrafoTeste()
{
    Grafo *novoGrafo;
    string nome = "teste";
    int i,**p = NULL, n = 5;
    p = (int**)malloc(n*sizeof(int*));
    for(i=0; i<n; i++)
    {
        p[i] = (int*)malloc(n*sizeof(int));
    }
    p[0][1] = 1;
    p[0][2] = 1;
    p[0][3] = 0;
    p[0][4] = 1;
    p[1][2] = 1;
    p[1][3] = 0;
    p[1][4] = 0;
    p[2][3] = 1;
    p[2][4] = 0;
    p[3][4] = 1;
    p = CompletaMatriz(p,n);
    novoGrafo = new Grafo(nome,p,n);
    apontadoresGrafos.push_back(novoGrafo);
    colecaoDegrafos.push_back(*(novoGrafo));
}

int main()
{
    FILE* arq;
    int opcao;
    arq = fopen("grafos.txt","r");
    if(arq != NULL)
    {
        fclose(arq);
        LerArquivo();
    }
    else
    {
        CriaGrafoTeste();
    }
    cout << "1. Carregar um grafo" << endl;
    cout << "2. Criar um grafo" << endl;
    cout << "Digite o numero da opcao que deseja: ";
    cin >> opcao;
    cout << endl;
    if(opcao == 1)
    {
        if((apontadoresGrafos.size() > 0))
        {
            sort(apontadoresGrafos.begin(),apontadoresGrafos.end(),Comparador);
        }
        CarregaGrafo();
    }
    else if(opcao == 2)
    {
        CriaGrafo();
    }
    else
    {
        cout << "Opcao invalida" <<endl;
    }

    return 0;
}

