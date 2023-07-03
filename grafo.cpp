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

// Encontrar clique de peso Maximo - Algoritmo guloso
list<int> Grafo::retornarCliqueDePesoMaximoGuloso() {
    list<int> cliquePesoMaximo;
    int pesoMaximo = 0;

    for (int v = 1; v < vertices.size(); ++v) {
        list<int> cliqueAtual;
        cliqueAtual.push_back(v);

        for (int vizinho : retornarVizinhancaAberta(v)) {
            if (find(cliqueAtual.begin(), cliqueAtual.end(), vizinho) == cliqueAtual.end()) {
                cliqueAtual.push_back(vizinho);
            }
        }

        int pesoCliqueAtual = 0;
        for (int v1 : cliqueAtual) {
            for (Aresta aresta : adj[v1]) {
                if (find(cliqueAtual.begin(), cliqueAtual.end(), aresta.destino) != cliqueAtual.end()) {
                    pesoCliqueAtual += aresta.peso;
                }
            }
        }

        if (pesoCliqueAtual > pesoMaximo) {
            pesoMaximo = pesoCliqueAtual;
            cliquePesoMaximo = cliqueAtual;
        }
    }

    return cliquePesoMaximo;
}

// Encontrar clique de peso Maximo - Algoritmo guloso randomizado adaptativo

int Grafo::gerarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool Grafo::existeAresta(int v1, int v2) {

    list<Aresta>::iterator it;
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it) {
        if(it->destino == v2) {
            return true;
        }
    }

    return false;
}

int Grafo::retornaPesoDaAresta(int v1, int v2) {

    list<Aresta>::iterator it;
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it) {
        if(it->destino == v2) {
            return it->peso;
        }
    }

    return -1;
}

bool Grafo::formaClique(const list<int>& verticesDaClique) {
    for (int v1 : verticesDaClique) {
        for (int v2 : verticesDaClique) {
            if (v1 != v2 && !existeAresta(v1, v2)) {
                return false;
            }
        }
    }
    return true;
}

int Grafo::calcularPesoClique(const list<int>& verticesDaClique) {
    int pesoTotal = 0;
    for (int v1 : verticesDaClique) {
        for (int v2 : verticesDaClique) {
            if (v1 != v2 && existeAresta(v1, v2)) {
                pesoTotal += retornaPesoDaAresta(v1, v2);
            }
        }
    }
    return pesoTotal;
}


// Encontrar clique de peso Maximo - Algoritmo guloso randomizado adaptativo e reativo
int Grafo::obterSomaDePesosDasArestasDeUmVerticeDaClique(const list<int> &verticesDaClique, int v) {
    int pesoTotal = 0;

    for(int vertice : verticesDaClique) {
        if(vertice != v) {
            pesoTotal += retornaPesoDaAresta(vertice, v);
        }
    }

    return pesoTotal;
}


list<int> Grafo::encontrarCliquePesoMaximoRandomizadoAdaptativoReativo(int numIteracoes, int tamanhoMaximo) {
    list<int> melhorClique;
    int melhorPeso = 0;

    srand(time(nullptr));

    vector<double> probabilidades(vertices.size(), 1.0);

    for (int iteracao = 0; iteracao < numIteracoes; ++iteracao) {
        list<int> cliqueAtual;
        int pesoAtual = 0;

        vector<int> verticesDisponiveis(vertices.size());
        for (int i = 0; i < vertices.size(); ++i) {
            verticesDisponiveis[i] = i;
        }

        random_shuffle(verticesDisponiveis.begin(), verticesDisponiveis.end());

        // Selecionar os primeiros 'tamanhoMaximo' vértices como a clique inicial
        for (int i = 0; i < tamanhoMaximo; ++i) {
            cliqueAtual.push_back(verticesDisponiveis[i]);
            pesoAtual += obterSomaDePesosDasArestasDeUmVerticeDaClique(cliqueAtual, verticesDisponiveis[i]); // considerando o peso das arestas
        }

        int iteracoesSemMelhora = 0;
        bool melhorou = false;

        while (iteracoesSemMelhora < 100) { // Número máximo de iterações sem melhora
            melhorou = false;

            for (int i = tamanhoMaximo; i < vertices.size(); ++i) {
                if (cliqueAtual.size() >= vertices.size()) {
                    break; // Já formou a clique máxima possível
                }

                int verticeAtual = verticesDisponiveis[i];
                double probabilidade = rand() / (double)RAND_MAX;

                if (probabilidade < probabilidades[verticeAtual]) {
                    // Verificar se a inclusão do vértice atual forma uma clique válida
                    bool formaClique = true;
                    for (int v : cliqueAtual) {
                        if (!existeAresta(verticeAtual, v)) {
                            formaClique = false;
                            break;
                        }
                    }

                    if (formaClique) {
                        int novoPeso = pesoAtual + obterSomaDePesosDasArestasDeUmVerticeDaClique(cliqueAtual, verticeAtual); // considerando o peso das arestas
                        if (novoPeso > pesoAtual) {
                            cliqueAtual.push_back(verticeAtual);
                            pesoAtual = novoPeso;
                            melhorou = true;
                            iteracoesSemMelhora = 0;
                        }
                    }
                }
            }

            if (!melhorou) {
                iteracoesSemMelhora++;
            }
        }

        if (pesoAtual > melhorPeso) {
            melhorClique = cliqueAtual;
            melhorPeso = pesoAtual;
        }
    }

    return melhorClique;
}

list<int> Grafo::encontrarCliquePesoMaximoRandomizadoAdaptativo(int numIteracoes, int tamanhoMaximo) {
    int numVertices = adj.size();
    list<int> melhorClique;
    int melhorPeso = 0;

    srand(time(nullptr));

    for (int i = 0; i < numIteracoes; ++i) {
        list<int> cliqueAtual;
        int pesoAtual = 0;
        vector<int> verticesDisponiveis(numVertices);
        for (int j = 0; j < numVertices; ++j) {
            verticesDisponiveis[j] = j;
        }

        random_shuffle(verticesDisponiveis.begin(), verticesDisponiveis.end());

        for (int j = 0; j < tamanhoMaximo && j < numVertices; ++j) {
            cliqueAtual.push_back(verticesDisponiveis[j]);
        }

        int iteracoesSemMelhora = 0;

        while (iteracoesSemMelhora < 100) {
            bool melhorou = false;

            for (int j = 0; j < numVertices; ++j) {
                if (find(cliqueAtual.begin(), cliqueAtual.end(), j) == cliqueAtual.end()) {
                    list<int> novaClique = cliqueAtual;
                    novaClique.push_back(j);

                    if (formaClique(novaClique)) {
                        int novoPeso = calcularPesoClique(novaClique);

                        if (novoPeso > pesoAtual) {
                            cliqueAtual = novaClique;
                            pesoAtual = novoPeso;
                            melhorou = true;
                            iteracoesSemMelhora = 0;
                        }
                    }
                }
            }

            if (!melhorou) {
                ++iteracoesSemMelhora;
            }
        }

        if (pesoAtual > melhorPeso) {
            melhorClique = cliqueAtual;
            melhorPeso = pesoAtual;
        }
    }

    return melhorClique;
}


// ================================= Fim randomizado guloso Adaptivo randomizado ==================================


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