#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

struct Vertice {
    int valor;

    Vertice() : valor(0) {} // Caso não passe parêmetro o valor do vértice é 0
    Vertice(int _valor) : valor(_valor) {} // Caso com vértice ponderado
};

struct Aresta {
    int destino;
    int peso;

    Aresta(int _destino) : destino(_destino), peso(0) {} // Caso não passe parêmetro o valor da aresta é 0
    Aresta(int _destino, int _peso) : destino(_destino), peso(_peso) {} // Caso com aresta ponderada
};

struct ArestaAGM {
    int origem;
    int destino;
    int peso;

    ArestaAGM(int _origem, int _destino, int _peso) : origem(_origem), destino(_destino), peso(_peso) {}
};

class Grafo {
    bool direcionado;
    int pesoMaximoEncontradoPraClique;
    vector<Vertice> vertices;
    vector<list<Aresta>> adj;
    int numVertices;
    int passoVetCaminhos;

public:
    Grafo(bool _direcionado);
    void adicionarVertice(int valor);
    void adicionarAresta(int v1, int v2);
    void adicionarAresta(int v1, int v2, int peso);
    int retornarPesoMaximoClique();
    
    list<int> retornarVizinhancaAberta(int v);                          // letra: H
    list<int> retornarVizinhancaFechada(int v);                         // letra: I
    bool verificarGrafoBipartido();                                     // letra: L
    list<int> retornarFechoTransitivoDireto(int v);                     // letra: O
    list<int> retornarFechoTransitivoIndireto(int v);                   // letra: P
    list<int> retornarSubgrafoVerticeInduzido(list<int> vertices);      // letra: R (Arrumar)
    void apresentaArestasPonte();                                       // letra: W
    void apresentarRaioDiametroCentroPeriferia();                       // letra: X
    void apresentaAGMouFlorestasDeCustoMinimo();                        // letra: Y

    // letra Z
    void DijkstraCaminhoMinimo(int origem, int destino, const vector<int>& vetDistancias, const vector<int>& vetCaminhos);


    list<int> retornarCliqueDePesoMaximoGuloso();      // Algoritmo guloso
    
    void exibirGrafo();
    void dfs(int v, list<int> vizinhos, vector<bool> &visitado); // busca em profundidade
    
    int gerarNumeroAleatorio(int min, int max);
    bool existeAresta(int v1, int v2);
    int retornaPesoDaAresta(int v1, int v2);
    bool formaClique(const list<int> &verticesDaClique);
    int calcularPesoClique(const list<int> &verticesDaClique);
    list<int> encontrarCliquePesoMaximoRandomizadoAdaptativo(int numIteracoes, int tamanhoMaximo);
    
    int obterSomaDePesosDasArestasDeUmVerticeDaClique(const list<int> &verticesDaClique, int v);
    list<int> encontrarCliquePesoMaximoRandomizadoAdaptativoReativo(int numIteracoes, int tamanhoMaximo);

    void BuscaEmProfundidadeAP(int v, int pai, vector<bool>& visitado, vector<int>& ordemVisitados, vector<int>& valoresBaixos);    // Função de busca em profundidade adaptada para buscar arestas ponte
    
    
};

#endif