/*Neste programa você vai trabalhar com o algoritmo do Ciclo Euleriano,
   com representação em vector.
1. Observe que, com a implementação feita, o algoritmo será O(nm).
2. Implementar o algoritmo do circuito euleriano
3. Rode o programa para os dois grafos abaixo e responda se ele funciona corretamente
   para grafos simples e multigrafos.
   Resposta:   (X) SIM      ( ) NÃO
G1:
11 13
11 10
2 11
2 8
9 8
9 10
1 2
2 3
3 4
4 1
5 4
5 6
6 7
4 7
G2:
11 17
11 10
2 11
2 8
9 8
9 10
2 1
1 2
2 3
3 2
3 4
4 3
4 1
1 4
5 4
5 6
6 7
4 7

*/
#include <stdio.h>
#include <string.h>
#include<iostream>
#include<vector>
using namespace std;
const int NVM=10000000;

// Declarações para o grafo
vector<int> A[NVM];
int n, m, u, w, D[NVM];
//Outras declarações
int i, j, k, topo, Pil[NVM];;

void Inicializa(int n){
	for (int i=0; i<=n; i++) {
		A[i].clear();
		D[i] = 0;
	}
}

void Esvazia (int Pil[], int &topo){
	topo = 0;
}

void PUSH(int Pil[], int &topo, int v){
	Pil[++topo] = v;
}

int POP(int Pil[], int &topo){
	return Pil[topo--];
}

int Proxviz(int v){
    w = A[v][0];
    return w;
}

void Remove(int u,int w){
    for (int i=0; i<A[u].size(); i++){
        if (A[u][i]==w){
            A[u].erase(A[u].begin()+i);
            break;
        }
    }
    for (int i=0; i<A[w].size(); i++){
        if (A[w][i]==u){
            A[w].erase(A[w].begin()+i);
            break;
        }
    }
    D[u]--;  D[w]--;
}

int main(){
	while(true){
        cout<<"n m = ";   cin >> n>>m;
	    Inicializa(n);
	    cout<<"Arestas:"<<endl;
	    for(i = 1; i<=m; i++){
	    	cin>>u>>w;
			A[u].push_back(w);  A[w].push_back(u);
			D[u]++;  D[w]++;
	    }
	    //Impressão do grafo
	    for(i=1; i<=n; i++){
		    cout<<"Vizinhos de "<<i<<":";
		    for(j=0; j<A[i].size(); j++)
				cout <<" "<<A[i][j];
            cout<<endl;
	    }
	    //Algoritmo CircuitoEuleriano
        cout<<"Circuito Euleriano: "<<endl;

        Esvazia(Pil,topo);
        PUSH(Pil, topo, 1);
        while (topo > 0){
            u = Pil[topo];
            w = Proxviz(u);
            PUSH(Pil, topo, w);
            Remove(u,w);
            while ((topo) && (!D[Pil[topo]])) {
                w = POP(Pil, topo);
                cout<< " " << w;
            }
        }
        /*
        Esvazia(Pil, topo)
		PUSH (Pil, topo, 1)
		enquanto topo > 0:
			u <- Pil[topo]
			w <- Proxviz(u)
			PUSH (Pil, topo, w)
			Remove (u, w)
			enquanto topo > 0 e D[Pil[topo]] = 0:
				w <- POP(Pil, topo)
				Imprimir w

        */
	    cout<<endl<<endl;
    }
	return 0;
}



