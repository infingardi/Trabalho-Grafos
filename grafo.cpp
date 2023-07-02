#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>

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

// Retornar Viznhança aberta - H
list<int> Grafo::retornarVizinhancaAberta(int v) {
    
    // Monta a lista de vertices da vizinhança aberta
    list<int> vizinhancaAberta;
    list<Aresta>::iterator it;
    for (it = adj[v].begin(); it != adj[v].end(); ++it) {
        if(it->destino != v)
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

// Retornar Viznhança fechada - I
list<int> Grafo::retornarVizinhancaFechada(int v) {

    // Monta a lista de vertices da vizinhança fechada
    list<int> vizinhancaFechada;
    list<Aresta>::iterator it;
    vizinhancaFechada.push_back(v);
    for (it = adj[v].begin(); it != adj[v].end(); ++it) {
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

// Retornar Fecho transitivo direto - O
list<int> Grafo::retornarFechoTransitivoDireto(int v) {

    int numVertices = adj.size();
    vector<bool> visitado(numVertices, false);
    list<int> vizinhos = retornarVizinhancaAberta(v);

    dfs(v, vizinhos, visitado);

    list<int> fechoTransitivoDireto;
    for (int i = 0; i < numVertices; ++i) {
        if (visitado[i]) {
            fechoTransitivoDireto.push_back(i);
        }
    }

    return fechoTransitivoDireto;
}

void Grafo::dfs(int vertice, list<int> vizinhos, vector<bool>& visitado) {
    visitado[vertice] = true;

    // Para cada viznho é verificado se já foi visitado, se não foi ele marca como visitado e repete a recursão para o não visitado
    for (int vizinho : vizinhos) {
        if (!visitado[vizinho]) {
            list<int> vizinhosDoProximoVertice = retornarVizinhancaAberta(vizinho);
            dfs(vizinho, vizinhosDoProximoVertice, visitado);
        }
    }
}

// Retornar Fecho transitivo indireto - P
list<int> Grafo::retornarFechoTransitivoIndireto(int v) {
    list<int> fechoTransitivo;
    vector<bool> visitado(adj.size(), false);

    stack<int> pilha;
    pilha.push(v);
    visitado[v] = true;

    while (!pilha.empty()) {
        int verticeAtual = pilha.top();
        pilha.pop();
        fechoTransitivo.push_back(verticeAtual);

        for (int vizinho : retornarVizinhancaAberta(verticeAtual)) {
            if (!visitado[vizinho]) {
                pilha.push(vizinho);
                visitado[vizinho] = true;
            }
        }
    }

    return fechoTransitivo;
}

// Retorna subgrafo vértice induzido - R --- Concertar (provavelmente sera necessário retonar um grafo novo e lá usar a função exibirGrafo)
list<int> Grafo::retornarSubgrafoVerticeInduzido(list<int> vertices) {
    list<int> subgrafo;

    for (int vertice : vertices) {
        if (vertice >= 0 && vertice < adj.size()) {
            subgrafo.push_back(vertice);
        }
    }

    return subgrafo;
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