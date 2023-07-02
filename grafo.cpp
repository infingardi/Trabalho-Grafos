#include <iostream>
#include <set>
#include <queue>

#include "grafo.hpp"

using namespace std;

Grafo::Grafo(bool _direcionado) : direcionado(_direcionado) {}

void Grafo::adicionarVertice(int valor) {
    Vertice vertice(valor);
    vertices.push_back(vertice);
    adj.push_back(list<Aresta>());
}

// Adicionar Aresta sem peso
void Grafo::adicionarAresta(int v1, int v2) {
    adj[v1].push_back(Aresta(v2));
    if (!direcionado)
        adj[v2].push_back(Aresta(v1));
}

// Adicionar Aresta com peso
void Grafo::adicionarAresta(int v1, int v2, int peso) {
    adj[v1].push_back(Aresta(v2, peso));
    if (!direcionado)
        adj[v2].push_back(Aresta(v1, peso));
}

// Mostrar Viznhança aberta - H
list<int> Grafo::retornarVizinhancaAberta(int v1) {
    
    // Monta a lista de vertices da vizinhança aberta
    list<int> vizinhancaAberta;
    list<Aresta>::iterator it;
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it) {
        if(it->destino != v1)
            vizinhancaAberta.push_back(it->destino);
    }

    // Ordena os vertices
    set<int> viznhancaAbertaOrdenada(vizinhancaAberta.begin(), vizinhancaAberta.end());

    // Devolve uma lista com os vertices ordenados
    list<int> listaOrdenada;
    for (int vertice : viznhancaAbertaOrdenada) {
        listaOrdenada.push_back(vertice);
    }
    
    return listaOrdenada;
}

// Mostrar Viznhança fechada - I
list<int> Grafo::retornarVizinhancaFechada(int v1) {

    // Monta a lista de vertices da vizinhança fechada
    list<int> vizinhancaFechada;
    list<Aresta>::iterator it;
    vizinhancaFechada.push_back(v1);
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it) {
        vizinhancaFechada.push_back(it->destino);
    }

    // Ordena os vertices
    set<int> viznhancaFechadaOrdenada(vizinhancaFechada.begin(), vizinhancaFechada.end());

    // Devolve uma lista com os vertices ordenados
    list<int> listaOrdenada;
    for (int vertice : viznhancaFechadaOrdenada) {
        listaOrdenada.push_back(vertice);
    }
    
    return listaOrdenada;
}

// Verificar se o grafo é bipartido - L
bool Grafo::verificarGrafoBipartido() {
    
    enum Cor {
        BRANCO,
        VERMELHO,
        AZUL
    };

    // Armazena a cor de cada vértice
    int numVertices = adj.size();
    vector<Cor> cores(numVertices, BRANCO);

    for (int i = 1; i < numVertices; ++i) {
        // Colore o vertice caso ele seja branco
        if (cores[i] == BRANCO) {
            cores[i] = VERMELHO;

            list<int> vizinhos = retornarVizinhancaAberta(i);

            for(int vertice : vizinhos) {
                if(cores[vertice] == BRANCO || cores[vertice] == AZUL) {
                    cores[vertice] = AZUL;
                } else {
                    return false;
                }
            }
        } else {
            list<int> vizinhos = retornarVizinhancaAberta(i);
            Cor corQueNaoPodeSer = cores[i];
            
            for(int vertice : vizinhos) {
                if(cores[vertice] == corQueNaoPodeSer) {
                    return false;
                } else if(cores[vertice] == BRANCO) {
                    cores[vertice] = corQueNaoPodeSer == VERMELHO ? AZUL : VERMELHO;
                }
            }
        }
    }

    return true;
}

void Grafo::exibirGrafo() {
    for (int i = 1; i < vertices.size(); ++i) {
        cout << "Vértice " << i << " (valor: " << vertices[i].valor << "): ";
        if (!adj[i].empty()) {
            list<Aresta>::iterator it;
            for (it = adj[i].begin(); it != adj[i].end(); ++it) {
                cout << "(" << it->destino;
                if (it->peso != 0)
                    cout << ", " << it->peso;
                cout << ") ";
            }
        }
        cout << endl;
    }
}