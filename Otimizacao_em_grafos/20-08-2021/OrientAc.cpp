/*Neste programa você vai trabalhar com a Busca em Profundidade em um grafo representado
   em matriz d adjacências, para determinar uma orientação acíclica para um grafo.
1. Programe o procedimento BP e modifique-o para imprimir a orientação acíclica.
2. Rode o algoritmo para o seguinte grafo:
G:
6 9
1 2
6 3
2 5
5 3
3 1
4 5
2 3
6 5
2 4
*/
#include <stdio.h>
#include <string.h>
#include<iostream>
using namespace std;
const int NVM=1001;

// Declarações para o grafo
int n, m, E[NVM][NVM], cpre,  pre[NVM], cpos, pos[NVM];
//Outras declarações
int i, j, u, w;

void BP(int u,int v){
    int w;
	pre[v] = ++cpre;
	for (w = v; w <= n; w++){
	    if ((E[v][w] == 1) && (pre[w] == 0)){
            BP(v,w);
	    }
        if ((E[v][w] == 1) && (pre[w] != 0)){
            if (pre[v] < pre[w]){
                cout<< v << " vai para " << w <<endl;
            }
            else{
                cout<< w << " vai para " << v <<endl;
            }
        }
	}
	pos[v] = ++cpos;
    /*
	pre[v] <- ++cpre
	para w <- 1 até n incl:
		se w vizinho de v e w não marcado:
			BP(v,w)
	pos[v] <- ++cpos
	*/
}

void Inicializa(){
    memset(E, 0, sizeof(E));
    memset(pre, 0, sizeof(pre));
	cpre = 0;  cpos=0;
}

int main(){
	while(true){
        cout<<"n m = ";   cin >> n>>m;
	    Inicializa();
	    cout<<"Arestas:"<<endl;
	    for(i=1; i<=m; i++){
		    cin >> u >> w;
		    E[u][w] = E[w][u] = 1;
	    }
	    //Impressão do grafo
	    for(i=1; i<=n; i++){
		    cout<<"Vizinhos de "<<i<<":";
		    for(j=1; j<=n; j++) if (E[i][j]==1) cout <<" "<<j;
            cout<<endl;
	    }
	    cout<<"Orientacao aciclica:"<<endl;
	    for(i = 1;i <= n; i++)
		    if(pre[i] == 0)
			    BP(i,i);
    }
	return 0;
}




