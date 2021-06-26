import os.path
import queue


class Vertice:

    def __init__(self,numero,cor):
        self.__numero = numero
        self.__cor = cor
        self.__grau = 0
        
    def setCor(self,cor):
        self.__cor = cor

    def getCor(self):
        return self.__cor

    def getNumero(self):
        return self.__numero
    
    def getGrau(self):
        return self.__grau

    def incrementaGrau(self):
        self.__grau = self.__grau + 1



class Grafo:

    def __init__(self,nome,matriz):
        self.__nome = nome
        self.__matriz_adj = matriz

    def getNome(self):
        return self.__nome

    def getMatriz(self):
        return self.__matriz_adj
    
    def __str__(self):
        string = "\n-----Matriz de Adjacência\n\n"
        n = len(self.__matriz_adj)
        for i in range(0,n):
            for j in range(0,n):
                if j == (n-1):
                    string = string + str(self.__matriz_adj[i][j]) + "\n"
                else:
                    string = string + str(self.__matriz_adj[i][j]) + " "
        return string
    
    def escreve_arquivo(self):
        string = ''
        for linha in self.__matriz_adj:
            string = string + ","
            for coluna in linha:
                string = string + str(coluna)
        string = string + "\n"
                
        arq = open("grafos.txt",'a')
        arq.write(self.__nome)
        arq.write(string)
        arq.close()






def completa_matriz(matriz,n):
    for i in range(0,n):
        for j in range(i,n):
            if i == j:
                matriz[i][j] = 0
            else:
                matriz[j][i] = matriz[i][j]
                
        
def cria_matriz():
    
    n = int(input("Digite n: "))
    matriz = [None] * n
    
    for i in range(0,n):
        matriz[i] = [None] * n
        for j in range(i+1,n):
            matriz[i][j] = int(input("Digite o elemento {} {}: ".format(i+1,j+1)))
    
    completa_matriz(matriz,n)
    return matriz


def le_matriz(lista):
    n = len(lista[0])
    matriz = [None] * n

    for i in range(n):
        matriz[i] = [None] * n
        for j in range(n):
            matriz[i][j] = int(lista[i][j])
    
    return matriz
            
    
def le_arquivo():
    grafos_lista = []
    arq = open("grafos.txt","r")
    for linha in arq:
        linha_lista = linha.rstrip("\n").split(",")
        matriz = le_matriz(linha_lista[1:])
        grafo = Grafo(linha_lista[0],matriz)
        grafos_lista.append(grafo)
    arq.close()

    return grafos_lista


def busca_binaria(lista,elemento):
    primeiro = 0
    ultimo = len(lista) - 1

    while primeiro <= ultimo:
        meio = (primeiro + ultimo)//2
        if (lista[meio].getNome()) == elemento:
            return meio
        else:
            if elemento < (lista[meio].getNome()):
                ultimo = meio - 1
            else:
                primeiro = meio + 1
                
    return -1


def busca_Largura(grafo):
    matriz = grafo.getMatriz()
    tamanho = len(matriz)
    comp_conexas = []
    aux = []
    vertices_lista = []
    fila = queue.Queue()
    
    for  x in range(0,tamanho):
        vert = Vertice(x,'w')
        vertices_lista.append(vert)
    vertices_lista[0].setCor('g')
    fila.put(vertices_lista[0])

    while not fila.empty():
        vertice = fila.get()
        linha = vertice.getNumero()
        aux.append(vertice)
        for j in range(0,tamanho):
            if matriz[linha][j] == 1:
                vertice.incrementaGrau()
                vizinho = vertices_lista[j]
                if  vizinho.getCor() == 'w':
                    vizinho.setCor('g')
                    fila.put(vizinho)
        vertice.setCor('b')
        if fila.empty() == True:
            comp_conexas.append(aux[:])
            aux.clear()
            for i in vertices_lista:
                if i.getCor() == 'w':
                    fila.put(i)
                    break
    
    return comp_conexas


def verificaEuleriano(comp_conexas):
    if len(comp_conexas) == 1:
        all_vertices = comp_conexas[0]
        if len(all_vertices) == 1:
            return False
        for vertice in all_vertices:
            if (vertice.getGrau() % 2) != 0:
                return False
        return True
    else:
        return False
    

def calcula_compC(cc):
    quantidade_cc = len(cc)
    media = 0
    cc_media = 0
    um_vertice = 0
    
    for i in range(quantidade_cc):
        if len(cc[i]) == 1:
            um_vertice += 1
        media = media + len(cc[i])
        
    media = media/quantidade_cc

    for j in range(quantidade_cc):
        if media == len(cc[j]):
            cc_media += 1

    return f'\n{quantidade_cc}, {media}, {cc_media}, {um_vertice}\n'


def remove_duplicatas(lista):
    tamanho = len(lista)
    i = 0
    
    while i < (tamanho - 1):
        if lista[i] == lista[i+1]:
            lista.pop(i)
            tamanho = len(lista)
        else:
            i += 1
            

def seleciona_cor(cores_lista):

    if cores_lista[0] != 1:
        return 1
    else:
        tamanho = len(cores_lista)
        
        for i in range(1,tamanho):
            
            if (cores_lista[i] - 1) != cores_lista[i-1]:
                return (cores_lista[i-1] + 1)
        
        return (cores_lista[tamanho - 1] + 1)



def coloracao(grafo):
    matriz = grafo.getMatriz()
    tamanho = len(matriz)
    vertices_lista = []
    cores = []
    cores_adj = []
    
    for  x in range(0,tamanho):
        vert = Vertice(x,0)
        vertices_lista.append(vert)
        
    vertices_lista[0].setCor(1)
    cores.append(1)

    for i in range(1,tamanho):
        
        for j in range(0,tamanho):
            
            if matriz[i][j] == 1:
                cor = vertices_lista[j].getCor()
                if cor != 0:
                    cores_adj.append(cor)
                    
        if len(cores_adj) > 0:
            cores_adj.sort()
            remove_duplicatas(cores_adj)
            cor_minima = seleciona_cor(cores_adj)
            vertices_lista[i].setCor(cor_minima)
            cores.append(cor_minima)
            cores_adj.clear()
        else:
            vertices_lista[i].setCor(1)
    
    cores.sort()
    remove_duplicatas(cores)  
    return cores


def entrada():
    nome = input("Digite o nome do Grafo: ")
    lista_grafos = le_arquivo()
    lista_grafos.sort(key = lambda grafo: grafo.getNome())
    indice = busca_binaria(lista_grafos,nome)
    return indice, lista_grafos, nome


def main():
    try:
        print("1 - Carregar um grafo")
        print("2 - Criar um grafo")
        print("3 - Busca em Largura")
        print("5 - Coloração Gulosa")
        print("6 - Verificar se é Euleriano")
        opcao = int(input("Digite o número da opção desejada: "))
        if opcao == 1:
            indice, lista_grafos, nome = entrada()
            if indice != -1:
                print(lista_grafos[indice])
            else:
                print(f'\n---Não foi encontrado um grafo com o nome {nome}---')
                
        elif opcao == 2:
            nome = input("Digite o nome do Grafo: ")
            matriz = cria_matriz()
            grafo = Grafo(nome,matriz)
            grafo.escreve_arquivo()
            print(grafo)
            
        elif opcao == 3:
            indice, lista_grafos, nome = entrada()
            if indice != -1:
                comp_conexas = busca_Largura(lista_grafos[indice])
                print(calcula_compC(comp_conexas))
            else:
                print(f'\n---Não foi encontrado um grafo com o nome {nome}---')
                
        elif opcao == 5:
            indice, lista_grafos, nome = entrada()
            if indice != -1:
                vetor_cores = coloracao(lista_grafos[indice])
                print(f'\n{vetor_cores}\n')
            else:
                print(f'\n---Não foi encontrado um grafo com o nome {nome}---')
                
        elif opcao == 6:
            indice, lista_grafos, nome = entrada()
            if indice != -1:
                comp_conexas = busca_Largura(lista_grafos[indice])
                Euleriano = verificaEuleriano(comp_conexas)
                if Euleriano == True:
                    print(f'\n{nome} é Euleriano')
                else:
                    print(f'\n{nome} não é Euleriano')
            else:
                print(f'\n---Não foi encontrado um grafo com o nome {nome}---')
        else:
            print("\n-----Opção inválida!!------\n")
    except ValueError:
        print("\n---Entrada inválida!!!---")
    except:
        print("\n---Ocorreu um erro!!!---")


def teste():
    if os.path.isfile("grafos.txt") == False:
        print("----Teste de Entrada----\n")
        print("Criando grafo:")
        print("Nome: teste\nMatriz de Adjacência: [[0,1,0],[1,0,1],[0,1,0]]\n")
        matriz = [[0,1,0],[1,0,1],[0,1,0]]
        grafo = Grafo("teste",matriz)
        print("Escrevendo grafo no arquivo grafo.txt\n")
        grafo.escreve_arquivo()
        print("Carregando grafo do arquivo grafo.txt")
        lista_g = le_arquivo()
        grafo_lido = busca_binaria(lista_g,"teste")
        print('\nNome: {}'.format(grafo_lido.getNome()))
        print(grafo_lido)
        print("----Fim do Teste----\n")


if __name__ == '__main__':
    teste()
    main()
