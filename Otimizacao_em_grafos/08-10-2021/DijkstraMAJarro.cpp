/*Neste programa você vai trabalhar com o algoritmo de Dijkstra
   para digrafos, usando a representação de matriz de adjacências,
   e implementando o Problema dos Jarros:
   tem-se dois jarros com capacidades a e b (inteiros) e uma bica d'água.
   Os jarros estão inicialmente vazios. Quer-se conseguir uma quantidade c de água no primeiro jarro.
   As operações que podem ser feitas são as seguintes:
	a) Encher completamente um jarro
	b) Jogar fora toda a água de um jarro
	c) Transferir a água de um jarro para o outro até esvaziar o primeiro jarro ou encher
	completamente o segundo.
1. Observe que existem funções já criadas para transformar um estado (x, y) em um vértice,
   onde x é o conteudo do jarro 1 e y o conteudo do jarro 2.
   A primeira função é Convertexyv(x, y, a, b), que transforma o estado (x, y) no vértice v.
   A segunda, faz o inverso: ConvInvvxy(v, a, b), que transforma o vértice v no estado (x, y).
2. A modelagem do problema já foi escrita. Implemente os procedimentos
   Dijkstra(v) e CaminhoMinimo(vi, vf, Di[vf]).
Vejam um exemplo:

Capacidades dos jarros: a b = 20 17
Situacao final desejada: (jaf jbf) = 15 0
Caminho minimo:
0/0(0)
20/0(1)
3/17(2)
3/0(3)
0/3(4)
20/3(5)
6/17(6)
6/0(7)
0/6(8)
20/6(9)
9/17(10)
9/0(11)
0/9(12)
20/9(13)
12/17(14)
12/0(15)
0/12(16)
20/12(17)
15/17(18)
15/0(19)
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
const int NVM=1001;
      int INF=1000000000;
struct nojar{int x;  int y;};
// Declarações para o grafo
int a, b, c, n, m, pre[NVM], E[NVM][NVM], Di[NVM];  nojar noj;

void Inicializa(int n){
    memset(E, 0, sizeof(E));
    memset(pre, 0, sizeof(pre));
    for (int i=1; i<=n+1; i++) Di[i]=INF;
    m=0;
}

int Convertexyv (int x, int y, int a, int b){
    int v = ((b+1)*x + y+1);
    return v;
}

nojar ConvInvvxy (int v, int a, int b){
    nojar noj;
    noj.y = (v-1) % (b+1);
    noj.x = (v-noj.y-1)/(b+1);
    return noj;
}

void CriaDigrafo (int n, int a, int b){
    int v, w, xo, xd, yo, yd, t;  nojar nojo, nojd;
    for (v=1; v<=(a+1)*(b+1); v++){
        noj = ConvInvvxy(v, a, b);  xo = noj.x;  yo = noj.y;
		//Aresta do tipo 1: encher o jarro 1
		if (xo < a){
		    xd = a;  yd = yo;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 1;
		}
		//Aresta do tipo 2: encher o jarro 2
		if (yo < b){
		    xd = xo;  yd = b;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 2;
		}
		//Aresta do tipo 3: esvaziar jarro 1
		if (xo > 0){
		    xd = 0;  yd = yo;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 3;
		}
		//Aresta do tipo 4: esvaziar jarro 2
		if (yo > 0){
		    xd = xo;  yd = 0;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 4;
		}
		//Aresta do tipo 5: transferir do jarro 1 para o 2
		if (xo > 0 && yo < b){
		    t = min(xo, b-yo);  xd = xo-t;  yd = yo+t;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 5;
		}
		//Aresta do tipo 6: transferir do jarro 2 para o 1
		if (xo < a && yo > 0){
		    t = min(a-xo, yo);  xd = xo+t;  yd = yo-t;  w = Convertexyv(xd, yd, a, b);
		    m++;  E[v][w] = 6;
		}
    }
}

void Dijkstra(int v){
	int i, j, w, z;
	Di[v] = 0;
	for (i = 1; i <= n; i++){
        w = n+1;
        for (j = n; j >= 1 ; j--){
            if((pre[j] == 0) && (Di[j] <= Di[w])){
                w = j;
            }
        }
        pre[w] = 1;
        for (z = 1; z <= n; z++){
            if ((E[w][z] > 0) && (pre[z] == 0)){
                Di[z] = min(Di[z], Di[w]+1);
            }
        }
	}
/* 	Di[v] <-  0
	para i <- 1..n incl.:
		w <- n+1
		para j <- n..1 incl.:
			se j não marcado e Di[j] <= Di[w]:
				w <- j
        marcar w
		para z <- 1..n incl.:
			se E[w,z]> 0 e z não marcado:
				Di[z] <-  min( Di[z], Di[w] + 1)
*/
}

void CaminhoMinimo(int v,int t, int d){
    int i;  nojar noj;

    if(Di[t] > 0){
        for (i = 1; i <= n; i++){
            if ((E[i][t] > 0) && ((Di[i]+1) == d)){
                CaminhoMinimo(v,i,Di[i]);
                break;
            }
        }
    }
    noj = ConvInvvxy(t,a,b);
    cout<<noj.x<<"/"<<noj.y<<endl;
/*  se Di[t] > 0:
        para i <- 1..n incl.:
            se  E[i,t] > 0 e  Di[i]+E[i,t] = d:
                CaminhoMinimo(v, i, Di[i])
                parar loop
    (x, y) <- ConvInvvxy(t, a, b)
    escrever (x, y)
*/
}

int main(){
    int i, j, k,v,t, vi, vf, jai, jbi, jaf, jbf;
	while (true){
        cout<<endl<<"Capacidades dos jarros: a b = ";  cin>>a>>b;
        n =(a+1)*(b+1);
	    Inicializa(n);
        CriaDigrafo(n, a, b);
	    jai = 0;  jbi = 0;
	    vi = Convertexyv(jai, jbi, a, b);
	    Dijkstra(vi);
	    //cout<<"Distancias minimas: ";
	    //for(i=1; i<=n; i++) cout<<Di[i]<<" ";  cout<<endl<<endl;
	    while(true){
            cout<<endl<<endl<<"Situacao final desejada: (jaf jbf) = " ; cin>>jaf>>jbf;
            vf = Convertexyv(jaf, jbf, a, b);
	        if (jaf == -1) break;
	        cout<<endl;
	        cout<<"Caminho minimo:"<<endl;
            CaminhoMinimo(vi, vf, Di[vf]);
        }
	}
	return 0;
}


