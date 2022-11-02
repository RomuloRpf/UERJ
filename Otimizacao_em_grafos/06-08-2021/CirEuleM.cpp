/*Neste programa você vai trabalhar com o algoritmo do Ciclo Euleriano,
   com representação em matriz de adjacências.
1. Observe que, com a implementação feita, o algoritmo será O(nm).
2. Modifique o algoritmo para que ele possa processar hipergrafos(múltiplas arestas
   entre dois vértices e autoloops.
3. Rode o programa para os seguintes grafos:
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
#include<iostream>
#include<string.h>
using namespace std;
const int NVM=1001;

// Declarações para o grafo
int n, m, E[NVM][NVM],  D[NVM];
//Outras declarações
int i,j,u,w,topo, Pil[NVM];

void Inicializa(){
    memset(E, 0, sizeof(E));
    memset(D, 0, sizeof(D));
}
void PUSH(int v){
	Pil[++topo] = v;
}

int POP(){
	return Pil[topo--];
}

int Proxviz(int v){
    for(int j=n; j>=1; j--){
        if (E[v][j] != 0){
            w = j;
        }
    }
    return w;
}

void Remove(int u,int w){
    E[u][w] -=1;
    E[w][u] -=1;
    D[u]--;  D[w]--;
}

int main(){
	while(true){
        cout<<"n m = ";   cin >> n>>m;
	    Inicializa();
	    cout<<"Arestas:"<<endl;
	    for(i=1; i<=m; i++){
		    cin >> u >> w;
		    if (E[u][w] == 1){
                E[u][w] += 1;
                E[w][u] += 1;
		    }
		    else{
                E[u][w] = E[w][u] = 1;
		    }
		    D[u]++;  D[w]++;
	    }
	    //Impressão do grafo
	    for(i=1; i<=n; i++){
		    cout<<"Vizinhos de "<<i<<":";
		    for(j=1; j<=n; j++) if (E[i][j]!=0) cout <<" "<<j;
            cout<<endl;
	    }
	    //Algoritmo CircuitoEuleriano
        cout<<"Circuito Euleriano: "<<endl;
	    topo = 0;  PUSH(1);
	    while(topo){
		    u = Pil[topo];
		    w = Proxviz(u);
		    Remove(u,w);
		    PUSH(w);
		    while((topo) && (!D[ Pil[topo]])){
			    w = POP(); cout<<" "<<w;
		    }
	    }
	    cout<<endl<<endl;
    }
	return 0;
}


