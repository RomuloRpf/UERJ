#ifndef _TRABALHO1_
#define _TRABALHO1_

void ImprimeNoArquivo();
void LerArquivo();
void CriaGrafoTeste();
int** CompletaMatriz(int**,int);
void ImprimeMatriz(int**,int);
void CarregaGrafo();
void CriaGrafo();
int** CriaMatriz(int);

class Grafo{
public:
    Grafo(std::string, int**,int);
    std::string getNomeGrafo();
    int** getMatriz();
    int getTamanhoMatriz();
private:
    std::string nomeGrafo;
    int** matriz;
    int tamanhoMatriz;
};

int Grafo::getTamanhoMatriz()
{
    return tamanhoMatriz;
}

int** Grafo::getMatriz()
{
    return matriz;
}
std::string Grafo::getNomeGrafo()
{
    return nomeGrafo;
}

Grafo::Grafo(std::string nome,int **m, int tamanho)
{
    nomeGrafo = nome;
    matriz = m;
    tamanhoMatriz = tamanho;
}

bool Comparador(Grafo*, Grafo*);
#endif // _TRABALHO1_
