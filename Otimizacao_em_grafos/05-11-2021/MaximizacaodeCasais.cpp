/*Neste programa você vai trabalhar com o problema de Maximização de Casais.
1. Complete a função CriaRede() que cria a rede.
2. Complete a função MostraResultado, que imprime os casais que podem ser formados.
3. Rode o programa para o exemplo dos slides.
*/
#include <iostream>
#include<stdlib.h>
#include<string.h>
#define INF 0x3f3f3f3f
#define NVM 1200
using namespace std;
struct par{int m;  int h;};

int C[NVM][NVM], CC[NVM][NVM], F[NVM][NVM], n, m, nh, nm, np, fmax;
bool V[NVM];  par P[100];

void Imprime(){
        cout<<"Fluxo:"<<endl;
        for(int i=1;i<=n;i++) { 
            for(int j=1;j<=n;j++) { 
                if (F[i][j] > 0) cout << i << " " << j << "  "<<F[i][j]<<endl;
            }        
        }     
}
void ImprimeC(){
        cout<<"Rede:"<<endl;
        for(int i=1;i<=n;i++) { 
            for(int j=1;j<=n;j++) { 
                if (CC[i][j] > 0) cout << i << " " << j << "  "<<CC[i][j]<<endl;
            }        
        }     
}

int ExisteCaminho(int v, int s, int mincap) {
    V[v] = true; 
    if (v==s) return mincap;
    for(int i=1; i<=n; i++) {
        if (!V[i] && C[v][i] > 0) {
            if (int fm = ExisteCaminho(i, s, min(mincap, C[v][i]))) {
                C[v][i] -= fm;  C[i][v] += fm;
                F[v][i] += fm;  F[i][v] -= fm;                
                return fm;
            }
        }
    }
    return 0;
}
void CriaRede(){
    int i, j;
    n = nh+nm+2;
    m = nh+nm+np;
	for(i=1; i<=n; i++) for (j=1; j<=n; j++){ CC[i][j]=0;  F[i][j]=0; }
    /*Dicas para a criação da rede
        1. A fonte é o vértice 1
        2. Os homens são os vértices 2 a nh+1
        3. As mulheres são os vértices nh+2 a nh+nm+1
        4. O sumidouro é o vértice n=nh+nm+2;   
		Preencher apenas o vetor de capacidades CC.    
    */

}

void MostraResultado(){
    int i, j;
    /* Dica: imprimir para cada mulher o homem alocado a ela, se existir.
       Para isso procurar o fluxo de saída do vértice correspondente, que é
       igual a 1.  
    */

}

int main() {
	int i;
    while(true){
       cout<<endl<<"Numero mulheres, mhomens e pares com interesse mútuo: "; 
	   cin>>nm>>nh>>np;
	   cout<<"Pares com interesse mútuo:"<<endl;
	   for (i=1; i<= np; i++) cin>>P[i].m>>P[i].h;
       CriaRede();

       cout<<" n= "<<n<<" m= "<<m<<endl;
       for (int i=1; i<=n; i++) for (int j=1; j<=n; j++)
           C[i][j]=CC[i][j];
       fmax = 0;
       memset(V, 0, sizeof(V));           
       while(int fm = ExisteCaminho(1, n, INF)) {
           fmax += fm;
           memset(V, 0, sizeof(V));
       }         
       cout<<"Emparelhmento máximo = "<<fmax<<endl;
       MostraResultado();             
       cin.get();
    }    
}
