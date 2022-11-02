/*Neste programa você vai trabalhar com o algoritmo de Floyd
   para digrafos, usando a representação de matriz de adjacências,
   e nostrando o caminho mínimo entre dados vértices.
1. Implemente os procedimentos Floyd e CaminhoMinimo.
2. Confira (na mão) o caminho mínimo para um grafo escolhido.
*/
#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
using namespace std;
const int NVM=1001;
      int INF=1000;

// Declarações para o grafo
int n, m, pre[NVM], E[NVM][NVM], D[NVM][NVM], VCM[NVM][NVM];

void Inicializa(int n){
    memset(E, 0, sizeof(E));
}

void Floyd(){
	int i, j, k;
	for (i=1; i <= n; i++){
	    for (j=1; j <= n; j++){
            if ((E[i][j] == 0) && (i != j)){
                D[i][j] = INF;
            }
            else{
                D[i][j] = E[i][j];
                VCM[i][j] = i;
            }
	    }
	}
	for (k=1; k <= n; k++){
	    for (i=1; i <= n; i++){
	        for (j=1; j <= n; j++){
	            if (D[i][j] > D[i][k] + D[k][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    VCM[i][j] = VCM[k][j];
	            }
	        }
        }
	}
/*  para i <- 1..n incl.:
		para j <- 1..n incl.:
			se E[i,j]=0 e i != j:
				D[i,j] <- INFINITO
			senão:
				D[i,j] <- E[i,j]
				VCM[i,j] <- i
	para k <- 1..n incl.:
		para i <- 1..n incl.:
			para j <- 1..n incl.:
 				se D[i, j] > D[i, k] + D[k, j]:
					D[i, j] <- D[i, k] + D[k, j]
					VCM[i,j] <- VCM[k,j]
*/
}


void CaminhoMinimo(int v,int t){
    if (v != t){
        CaminhoMinimo(v,VCM[v][t]);
    }
    cout << t << " ";
/*  se (v != t) então:
        CaminhoMinimo (v, VCM[v,t])
	escrever (t)
*/
}

int main(){
    int i, j, a, b, c, x, k,v,t;
	while (true){
        cout<<endl<<"Dimensoes do grid: a b = ";  cin>>a>>b;
        n =a*b;  cout<<"Grid de dimensoes "<<a<<"x"<<b<<endl;
	    Inicializa(n);
        for(i=1;i<=a;i++) for (j=1; j<b; j++){
            k = (i-1)*b+j;
            c = rand()%10+1;    x = rand()%3;
            if (x==0){
				E[k][k+1]=c;   cout<<k<<" "<<k+1<<" "<<c<<endl;
			}
            else if (x == 1){
				E[k+1][k]=c;   cout<<k+1<<" "<<k<<" "<<c<<endl;
			}
            else{
				E[k][k+1]=E[k+1][k]=c; 	 cout<<k<<" "<<k+1<<" "<<c<<endl;  cout<<k+1<<" "<<k<<" "<<c<<endl;
			}
        }
        for(i=2;i<=a;i++) for (j=1; j<=b; j++){
            k = (i-1)*b+j;
            c = rand()%10+1;  x = rand()%3;
            if (x==0){
				E[k][k-b]=c;   cout<<k<<" "<<k-b<<" "<<c<<endl;
			}
            else if (x == 1){
				E[k-b][k]=c;   cout<<k-b<<" "<<k<<" "<<c<<endl;
			}
            else{
				E[k][k-b]=E[k-b][k]=c;    cout<<k<<" "<<k-b<<" "<<c<<endl;  cout<<k-b<<" "<<k<<" "<<c<<endl;
			}
        }
        Floyd();
        // Matriz de Distâncias mínimas
        cout<<"Matriz D: "<<endl;
	    for (i=1; i<=n; i++){
	        for (j=1; j<=n; j++) cout<<setw(5)<<D[i][j];
	        cout<<endl;
	    }
        // Matriz de VCM
        cout<<"Matriz VCM: "<<endl;
	    for (i=1; i<=n; i++){
	        for (j=1; j<=n; j++) cout<<setw(3)<<VCM[i][j];
	        cout<<endl;
	    }
	    while(true){
            cout<<endl<<"Caminho minimo entre v, t = " ; cin>>v>>t;
	        if (!v) break;
	        if (D[v][t] != INF){
                CaminhoMinimo (v,t);   cout<<endl;
            }
            else cout<<"Nao ha cminho"<<endl;
        }
	}
	return 0;
}


