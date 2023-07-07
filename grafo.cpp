#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>

#include "grafo.hpp"

using namespace std;

Grafo::Grafo(bool _direcionado) : direcionado(_direcionado) {}

int Grafo::retornarPesoMaximoClique()
{
    return pesoMaximoEncontradoPraClique;
}

void Grafo::adicionarVertice(int valor)
{
    Vertice vertice(valor);
    vertices.push_back(vertice);
    adj.push_back(list<Aresta>());
}

// Adicionar Aresta sem peso
void Grafo::adicionarAresta(int v1, int v2)
{
    adj[v1].push_back(Aresta(v2));
    if (!direcionado)
        adj[v2].push_back(Aresta(v1));
}

// Adicionar Aresta com peso
void Grafo::adicionarAresta(int v1, int v2, int peso)
{
    adj[v1].push_back(Aresta(v2, peso));
    if (!direcionado)
        adj[v2].push_back(Aresta(v1, peso));
}

// Retornar Viznhança aberta - H
list<int> Grafo::retornarVizinhancaAberta(int v)
{

    // Monta a lista de vertices da vizinhança aberta
    list<int> vizinhancaAberta;
    list<Aresta>::iterator it;
    for (it = adj[v].begin(); it != adj[v].end(); ++it)
    {
        if (it->destino != v)
            vizinhancaAberta.push_back(it->destino);
    }

    // Ordena os vertices
    set<int> viznhancaAbertaOrdenada(vizinhancaAberta.begin(), vizinhancaAberta.end());

    // Devolve uma lista com os vertices ordenados
    list<int> listaOrdenada;
    for (int vertice : viznhancaAbertaOrdenada)
    {
        listaOrdenada.push_back(vertice);
    }

    return listaOrdenada;
}

// Retornar Viznhança fechada - I
list<int> Grafo::retornarVizinhancaFechada(int v)
{

    // Monta a lista de vertices da vizinhança fechada
    list<int> vizinhancaFechada;
    list<Aresta>::iterator it;
    vizinhancaFechada.push_back(v);
    for (it = adj[v].begin(); it != adj[v].end(); ++it)
    {
        vizinhancaFechada.push_back(it->destino);
    }

    // Ordena os vertices
    set<int> viznhancaFechadaOrdenada(vizinhancaFechada.begin(), vizinhancaFechada.end());

    // Devolve uma lista com os vertices ordenados
    list<int> listaOrdenada;
    for (int vertice : viznhancaFechadaOrdenada)
    {
        listaOrdenada.push_back(vertice);
    }

    return listaOrdenada;
}

// Verificar se o grafo é bipartido - L
bool Grafo::verificarGrafoBipartido()
{

    enum Cor
    {
        BRANCO,
        VERMELHO,
        AZUL
    };

    // Armazena a cor de cada vértice
    int numVertices = adj.size();
    vector<Cor> cores(numVertices, BRANCO);

    for (int i = 1; i < numVertices; ++i)
    {
        // Colore o vertice caso ele seja branco
        if (cores[i] == BRANCO)
        {
            cores[i] = VERMELHO;

            list<int> vizinhos = retornarVizinhancaAberta(i);

            for (int vertice : vizinhos)
            {
                if (cores[vertice] == BRANCO || cores[vertice] == AZUL)
                {
                    cores[vertice] = AZUL;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            list<int> vizinhos = retornarVizinhancaAberta(i);
            Cor corQueNaoPodeSer = cores[i];

            for (int vertice : vizinhos)
            {
                if (cores[vertice] == corQueNaoPodeSer)
                {
                    return false;
                }
                else if (cores[vertice] == BRANCO)
                {
                    cores[vertice] = corQueNaoPodeSer == VERMELHO ? AZUL : VERMELHO;
                }
            }
        }
    }

    return true;
}

// Retornar Fecho transitivo direto - O
list<int> Grafo::retornarFechoTransitivoDireto(int v)
{

    int numVertices = adj.size();
    vector<bool> visitado(numVertices, false);
    list<int> vizinhos = retornarVizinhancaAberta(v);

    dfs(v, vizinhos, visitado);

    list<int> fechoTransitivoDireto;
    for (int i = 0; i < numVertices; ++i)
    {
        if (visitado[i])
        {
            fechoTransitivoDireto.push_back(i);
        }
    }

    return fechoTransitivoDireto;
}

void Grafo::dfs(int vertice, list<int> vizinhos, vector<bool> &visitado)
{
    visitado[vertice] = true;

    // Para cada viznho é verificado se já foi visitado, se não foi ele marca como visitado e repete a recursão para o não visitado
    for (int vizinho : vizinhos)
    {
        if (!visitado[vizinho])
        {
            list<int> vizinhosDoProximoVertice = retornarVizinhancaAberta(vizinho);
            dfs(vizinho, vizinhosDoProximoVertice, visitado);
        }
    }
}

// Retornar Fecho transitivo indireto - P
list<int> Grafo::retornarFechoTransitivoIndireto(int v)
{
    list<int> fechoTransitivo;
    vector<bool> visitado(adj.size(), false);

    stack<int> pilha;
    pilha.push(v);
    visitado[v] = true;

    while (!pilha.empty())
    {
        int verticeAtual = pilha.top();
        pilha.pop();
        fechoTransitivo.push_back(verticeAtual);

        for (int vizinho : retornarVizinhancaAberta(verticeAtual))
        {
            if (!visitado[vizinho])
            {
                pilha.push(vizinho);
                visitado[vizinho] = true;
            }
        }
    }

    return fechoTransitivo;
}

// Retorna subgrafo vértice induzido - R --- Concertar (provavelmente sera necessário retonar um grafo novo e lá usar a função exibirGrafo)
list<int> Grafo::retornarSubgrafoVerticeInduzido(list<int> vertices)
{
    list<int> subgrafo;

    for (int vertice : vertices)
    {
        if (vertice >= 0 && vertice < adj.size())
        {
            subgrafo.push_back(vertice);
        }
    }

    return subgrafo;
}

// Encontrar clique de peso Maximo - Algoritmo guloso
list<int> Grafo::retornarCliqueDePesoMaximoGuloso()
{
    list<int> cliquePesoMaximo;
    int pesoMaximo = 0;

    for (int v = 1; v < vertices.size(); ++v)
    {
        list<int> cliqueAtual;
        cliqueAtual.push_back(v);

        for (int vizinho : retornarVizinhancaAberta(v))
        {
            if (find(cliqueAtual.begin(), cliqueAtual.end(), vizinho) == cliqueAtual.end())
            {
                bool formaClique = true;

                for (int v1 : cliqueAtual)
                {
                    if (!existeAresta(vizinho, v1))
                    {
                        formaClique = false;
                        break;
                    }
                }

                if (formaClique)
                {
                    cliqueAtual.push_back(vizinho);
                }
            }
        }

        int pesoCliqueAtual = 0;
        for (int v1 : cliqueAtual)
        {
            for (Aresta aresta : adj[v1])
            {
                if (find(cliqueAtual.begin(), cliqueAtual.end(), aresta.destino) != cliqueAtual.end())
                {
                    pesoCliqueAtual += aresta.peso;
                }
            }
        }

        pesoCliqueAtual = pesoCliqueAtual / 2; // Aresta tava sendo contada 2 vezes
        if (pesoCliqueAtual > pesoMaximo)
        {
            pesoMaximo = pesoCliqueAtual;
            cliquePesoMaximo = cliqueAtual;
            pesoMaximoEncontradoPraClique = pesoMaximo;
        }
    }

    return cliquePesoMaximo;
}

// Encontrar clique de peso Maximo - Algoritmo guloso randomizado adaptativo

int Grafo::gerarNumeroAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}

bool Grafo::existeAresta(int v1, int v2)
{

    list<Aresta>::iterator it;
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it)
    {
        if (it->destino == v2)
        {
            return true;
        }
    }

    return false;
}

int Grafo::retornaPesoDaAresta(int v1, int v2)
{

    list<Aresta>::iterator it;
    for (it = adj[v1].begin(); it != adj[v1].end(); ++it)
    {
        if (it->destino == v2)
        {
            return it->peso;
        }
    }

    return -1;
}

bool Grafo::formaClique(const list<int> &verticesDaClique)
{
    for (int v1 : verticesDaClique)
    {
        for (int v2 : verticesDaClique)
        {
            if (v1 != v2 && !existeAresta(v1, v2))
            {
                return false;
            }
        }
    }
    return true;
}

int Grafo::calcularPesoClique(const list<int> &verticesDaClique)
{
    int pesoTotal = 0;
    for (int v1 : verticesDaClique)
    {
        for (int v2 : verticesDaClique)
        {
            if (v1 != v2 && existeAresta(v1, v2))
            {
                pesoTotal += retornaPesoDaAresta(v1, v2);
            }
        }
    }
    return pesoTotal;
}

list<int> Grafo::encontrarCliquePesoMaximoRandomizadoAdaptativo(int numIteracoes, int tamanhoMaximo)
{
    int numVertices = adj.size();
    list<int> melhorClique;
    int melhorPeso = 0;

    srand(time(nullptr));

    for (int i = 0; i < numIteracoes; ++i)
    {
        list<int> cliqueAtual;
        int pesoAtual = 0;
        vector<int> verticesDisponiveis(numVertices);
        for (int j = 0; j < numVertices; ++j)
        {
            verticesDisponiveis[j] = j;
        }

        random_shuffle(verticesDisponiveis.begin(), verticesDisponiveis.end());

        for (int j = 0; j < tamanhoMaximo && j < numVertices; ++j)
        {
            cliqueAtual.push_back(verticesDisponiveis[j]);
        }

        int iteracoesSemMelhora = 0;

        while (iteracoesSemMelhora < 100)
        {
            bool melhorou = false;

            for (int j = 0; j < numVertices; ++j)
            {
                if (find(cliqueAtual.begin(), cliqueAtual.end(), j) == cliqueAtual.end())
                {
                    list<int> novaClique = cliqueAtual;
                    novaClique.push_back(j);

                    if (formaClique(novaClique))
                    {
                        int novoPeso = calcularPesoClique(novaClique) / 2;

                        if (novoPeso > pesoAtual)
                        {
                            cliqueAtual = novaClique;
                            pesoAtual = novoPeso;
                            melhorou = true;
                            iteracoesSemMelhora = 0;
                        }
                    }
                }
            }

            if (!melhorou)
            {
                ++iteracoesSemMelhora;
            }
        }

        if (pesoAtual > melhorPeso)
        {
            melhorClique = cliqueAtual;
            melhorPeso = pesoAtual;
            pesoMaximoEncontradoPraClique = melhorPeso;
        }
    }

    return melhorClique;
}

// Encontrar clique de peso Maximo - Algoritmo guloso randomizado adaptativo e reativo
int Grafo::obterSomaDePesosDasArestasDeUmVerticeDaClique(const list<int> &verticesDaClique, int v)
{
    int pesoTotal = 0;

    for (int vertice : verticesDaClique)
    {
        if (vertice != v)
        {
            pesoTotal += retornaPesoDaAresta(vertice, v);
        }
    }

    return pesoTotal;
}

list<int> Grafo::encontrarCliquePesoMaximoRandomizadoAdaptativoReativo(int numIteracoes, int tamanhoMaximo)
{
    list<int> melhorClique;
    int melhorPeso = 0;

    srand(time(nullptr));

    vector<double> probabilidades(vertices.size(), 1.0);

    for (int iteracao = 0; iteracao < numIteracoes; ++iteracao)
    {
        list<int> cliqueAtual;
        int pesoAtual = 0;

        vector<int> verticesDisponiveis(vertices.size());
        for (int i = 0; i < vertices.size(); ++i)
        {
            verticesDisponiveis[i] = i; // vertices disponiveis recebem todos os vertices
        }

        random_shuffle(verticesDisponiveis.begin(), verticesDisponiveis.end());

        // Selecionar os primeiros 'tamanhoMaximo' vértices como a clique inicial
        for (int i = 0; i < tamanhoMaximo; ++i)
        {
            cliqueAtual.push_back(verticesDisponiveis[i]);
            pesoAtual += obterSomaDePesosDasArestasDeUmVerticeDaClique(cliqueAtual, verticesDisponiveis[i]); // considerando o peso das arestas
        }

        int iteracoesSemMelhora = 0;
        bool melhorou = false;

        while (iteracoesSemMelhora < 100)
        { // Número máximo de iterações sem melhora
            melhorou = false;

            for (int i = tamanhoMaximo; i < vertices.size(); ++i)
            {
                if (cliqueAtual.size() >= vertices.size())
                {
                    break; // Já formou a clique máxima possível
                }

                int verticeAtual = verticesDisponiveis[i];
                double probabilidade = rand() / (double)RAND_MAX;

                if (probabilidade < probabilidades[verticeAtual])
                {
                    // Verificar se a inclusão do vértice atual forma uma clique válida
                    bool formaClique = true;
                    for (int v : cliqueAtual)
                    {
                        if (!existeAresta(verticeAtual, v))
                        {
                            formaClique = false;
                            break;
                        }
                    }

                    if (formaClique)
                    {
                        int novoPeso = (pesoAtual + obterSomaDePesosDasArestasDeUmVerticeDaClique(cliqueAtual, verticeAtual)); // considerando o peso das arestas
                        if (novoPeso > pesoAtual)
                        {
                            cliqueAtual.push_back(verticeAtual);
                            pesoAtual = novoPeso;
                            melhorou = true;
                            iteracoesSemMelhora = 0;
                        }
                    }
                }
            }

            if (!melhorou)
            {
                iteracoesSemMelhora++;
            }
        }

        if (pesoAtual > melhorPeso)
        {
            melhorClique = cliqueAtual;
            melhorPeso = pesoAtual;
            pesoMaximoEncontradoPraClique = melhorPeso;
        }
    }

    return melhorClique;
}

// ================================= Fim randomizado guloso Adaptivo randomizado ==================================

void Grafo::exibirGrafo()
{
    for (int i = 1; i < vertices.size(); ++i)
    {
        cout << "Vértice " << i << " (valor: " << vertices[i].valor << "): ";
        if (!adj[i].empty())
        {
            list<Aresta>::iterator it;
            for (it = adj[i].begin(); it != adj[i].end(); ++it)
            {
                cout << "(" << it->destino;
                if (it->peso != 0)
                    cout << ", " << it->peso;
                cout << ") ";
            }
        }
        cout << endl;
    }
}




//===========Funções do Gabriel, reorganizar, se preciso.===============

void Grafo::BuscaEmProfundidadeAP(int v, int pai, vector<bool> &visitado, vector<int> &ordemVisitados, vector<int> &valoresBaixos)
{
    static int tempo = 0;
    visitado[v] = true;
    ordemVisitados[v] = valoresBaixos[v] = ++tempo;

    // Percorre as arestas do vértice.

    for(const Aresta &aresta : adj[v])
    {
        int vizinho = aresta.destino;

        // Verifica se há um vértice, vizinho ao atual, que ainda não foi visitado.

        if(!visitado[vizinho])
        {
            BuscaEmProfundidadeAP(vizinho, v, visitado, ordemVisitados, valoresBaixos); // Chama a função BuscaEmProfundidadeAP para o vértice vizinho.
            valoresBaixos[v] = min(valoresBaixos[v], valoresBaixos[vizinho]);           // Atualiza o valor mais baixo.

            // verifica se (valoresBaixos[vizinho]) é maior que (ordemVisitados[v]), a classificando como ponte se for o caso.

            if(valoresBaixos[vizinho] > ordemVisitados[v])
                cout << "Aresta (" << v << "-" << vizinho << ") é uma aresta ponte" << endl;
        }
        else if(vizinho != pai)
            valoresBaixos[v] = min(valoresBaixos[v], ordemVisitados[vizinho]);
    }
}

void Grafo::apresentaArestasPonte()
{
    vector<bool> visitado(vertices.size(), false);  // Cria um vetor bool de tamanho igual aos vértices do grafo para identificar vértices visitados.
    vector<int> ordemVisitados(vertices.size(), 0); // Cria um vetor int de tamanho igual aos vértices do grafo para armazenar o indicador da ordem na qual os vértices foram visitados.
    vector<int> valoresBaixos(vertices.size(), 0);  // Cria um vetor int de tamanho igual aos vértices do grafo para armazenar os valores mais baixos de cada vértice durante a busca por arestas ponte.

    // Inicia a busca em profundidade em um vértice que não foi visitado.

    for(int i = 0; i < vertices.size(); i++)
    {
        if(!visitado[i])
            BuscaEmProfundidadeAP(i, -1, visitado, ordemVisitados, valoresBaixos);
    }
}

void Grafo::apresentarRaioDiametroCentroPeriferia()
{
    int numVertices = vertices.size();
    vector<vector<int>> distancias(numVertices, vector<int>(numVertices, numeric_limits<int>::max())); // Vetor para armazenar as distâncias mais curtas entre os pares de vértices.

    // Executa a BFS(Busca em Largura) a partir de cada vértice para calcular as distâncias mais curtas.

    for(int i = 0; i < numVertices; i++)
    {
        vector<bool> visitado(numVertices, false); // Inicializar vetor de visitados.
        distancias[i][i] = 0;                      // Inicializar a distância do vértice atual para ele mesmo como 0.

        // Fila para realizar a BFS.

        queue<int> fila;
        fila.push(i);
        visitado[i] = true;

        // Mantém a BFS enquanto houver vértices na fila que ainda não foram visitados.

        while(!fila.empty())
        {
            int v = fila.front(); // Armazena o elemento na frente da fila na variável int v.
            fila.pop();           // Remove o elemento da frente da fila.

            // Percorre todas as arestas adjacentes a cada vértice presente no grafo.

            for(const Aresta &aresta : adj[v])
            {
                int vizinho = aresta.destino;

                // Verifica se há algum vértice vizinho que ainda não foi visitado.

                if(!visitado[vizinho])
                {
                    distancias[i][vizinho] = distancias[i][v] + 1; // Atualiza a distância do vértice atual para o vizinho.
                    fila.push(vizinho);                            // Adiciona o vértice vizinho a fila de vértices que serão processados na busca em largura.
                    visitado[vizinho] = true;                      // Muda o status de visitado do vértice vizinho para true, significando que ele foi processado durante a busca em largura.
                }
            }
        }
    }

    int raio = numeric_limits<int>::max();
    int diametro = 0;
    int centro = 0;
    vector<int> periferia;

    // Percorre e executa a BFS a partir de cada vértice do grafo.

    for(int i = 0; i < numVertices; i++)
    {
        int maxDistancia = 0;

        // Atualiza as distâncias mais curtas entre os vértices do grafo.

        for(int j = 0; j < numVertices; j++)
        {

            // Verifica se a distância entre os vértices i e j é diferente do valor máximo possível para um inteiro.

            if(distancias[i][j] != numeric_limits<int>::max())
            {
                maxDistancia = max(maxDistancia, distancias[i][j]);
            }
        }

        // Atribuí o raio a distância máxima no caso de ele ser maior que a distância máxima.

        if(maxDistancia < raio)
        {
            raio = maxDistancia;
        }

        // Atribuí o diâmetro a distância máxima e atualiza o valor do centro no caso do diâmetro ser menor que a distância máxima.

        if(maxDistancia > diametro)
        {
            diametro = maxDistancia;
            centro = i;
        }

        // Verifica se a distância máxima encontrada corresponde ao diâmetro do grafo.

        if(maxDistancia == diametro)
        {
            periferia.push_back(i); // Adiciona o vértice atual i ao vetor periferia.
        }
    }

    // Apresentação do raio, diâmetro, centro e periferia.

    cout << "Raio: " << raio << endl;
    cout << "Diâmetro: " << diametro << endl;
    cout << "Centro: " << centro << endl;
    cout << "Periferia: ";
    for (int v : periferia)
    {
        cout << v << " ";
    }
    cout << endl;
}

void Grafo::apresentaAGMouFlorestasDeCustoMinimo()
{
    vector<bool> visitado(numVertices, false);                           // Vetor para marcar os vértices visitados.
    vector<int> custoMinimo(numVertices, numeric_limits<int>::max());    // Vetor para armazenar os custos mínimos dos vértices.
    vector<int> pai(numVertices, -1);                                    // Vetor para armazenar o pai de cada vértice na AGM.
    vector<ArestaAGM> agm;                                               // Vetor para armazenar as arestas da Árvore Geradora Mínima ou Floresta de Custo Mínimo.

    int verticePartida = 0;

    visitado[verticePartida] = true;    // Marca o vértice de partida como visitado.
    custoMinimo[verticePartida] = 0;    // Marca o vértice de partida com custo mínimo 0.

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;     // Cria uma fila de prioridade para armazenar arestas disponíveis.


    // Insire as arestas do vértice de partida na fila de prioridade.

    for(const Aresta& aresta : adj[verticePartida])
    {
        filaPrioridade.push(make_pair(aresta.peso, aresta.destino));
    }


    // Enquanto houver arestas disponíveis na fila de prioridade.

    while(!filaPrioridade.empty())
    {
        int peso = filaPrioridade.top().first;              // Atribuí o elemento no topo de fila de prioridade a int peso, sendo ele a aresta de menor peso.
        int verticeAtual = filaPrioridade.top().second;     // Atribuí ao int verticeAtual o segundo elemento no topo da fila de prioridade.
        filaPrioridade.pop();                               // Remove o elemento de maior prioridade da fila.


        // Se o vértice atual já foi visitado, a aresta é ignorada.

        if (visitado[verticeAtual])
            continue;

        visitado[verticeAtual] = true;                                      // Marca o vértice atual como visitado.
        agm.push_back(ArestaAGM(pai[verticeAtual], verticeAtual, peso));    // Adiciona a aresta a AGM ou a Floresta de Custo Mínimo.


        // Atualiza o custo mínimo e o pai dos vértices adjacentes ao vértice atual

        for(const Aresta& aresta : adj[verticeAtual])
        {
            int verticeAdjacente = aresta.destino;      // Atribui o valor do destino a variável int verticeAdjacente.
            int pesoAresta = aresta.peso;               // Atribui o valor do do peso a variável int pesoAresta.


            // Verifica se o vértice adjacente não foi visitado e se o peso da aresta é menor do que o custo mínimo.

            if(!visitado[verticeAdjacente] && pesoAresta < custoMinimo[verticeAdjacente])
            {
                custoMinimo[verticeAdjacente] = pesoAresta;                     // Atualiza o custo mínimo para alcançar o vértice adjacente.
                pai[verticeAdjacente] = verticeAtual;                           // Atualiza o pai do vértice adjacente para ser o vértice atual.
                filaPrioridade.push(make_pair(pesoAresta, verticeAdjacente));   // Insere o vértice adjacente na fila de prioridade para ser processado posteriormente.
            }
        }
    }


    // Apresenta as arestas da Árvore Geradora Mínima ou Floresta de Custo Mínimo.

    cout << "Arestas da Árvore Geradora Mínima ou Floresta de Custo Mínimo:" << endl;
    for(const ArestaAGM& aresta : agm)
    {
        cout << "(" << aresta.origem << " - " << aresta.destino << ") com peso " << aresta.peso << endl;
    }

};

void Grafo::DijkstraCaminhoMinimo(int origem, int destino, const vector<int>& vetDistancias, const vector<int>& vetCaminhos)
{
    vector<int> caminhos(numVertices);      // Declara um vetor para armazenar o caminho mínimo do vértice de origem ao destino.
    int VetCaminhos = 0;
    int custo = vetDistancias[destino];     // Obtém o custo do caminho mínimo para o destino.
    int caminho = vetCaminhos[destino];     // Obtém o próximo vértice no caminho mínimo para o destino.
    int infoNo1 = origem;                   // Armazena o valor do vértice de origem.
    int infoNo2 = destino;                  // Armazena o valor do vértice de destino.

    cout << endl << "* Caminho do vértice " << infoNo1 << " para o vértice " << infoNo2 << " utilizando Dijkstra *" << endl;


    // Se não passar pelo if, imprime o caminho mínimo. 

    if(custo == INT_MAX)
    {
        cout << endl << "Não há caminho possível entre os vértices " << infoNo1 << " e " << infoNo2 << endl;
    }
    else
    {
        while(caminho != -1)
        {
            caminhos[passoVetCaminhos] = caminho;
            passoVetCaminhos++;
            caminho = vetCaminhos[caminho];
        }
        cout << "Custo:" << custo << endl;
        cout << "Caminho:(" << infoNo1;
        for(int i = passoVetCaminhos - 1; i >= 0; i--)
        {
            cout << "," << caminhos[i];
        }
        cout << "," << infoNo2 << ")" << endl << endl;
    }
}