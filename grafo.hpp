#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <list>
#include <vector>
#include <utility>

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

class Grafo {
    bool direcionado;
    vector<Vertice> vertices;
    vector<list<Aresta>> adj;

public:
    Grafo(bool _direcionado);
    void adicionarVertice(int valor);
    void adicionarAresta(int v1, int v2);
    void adicionarAresta(int v1, int v2, int peso);
    
    list<int> retornarVizinhancaAberta(int v1);  // letra: H
    list<int> retornarVizinhancaFechada(int v1); // letra: I
    bool verificarGrafoBipartido();              // letra: L
    
    void exibirGrafo();
};

#endif