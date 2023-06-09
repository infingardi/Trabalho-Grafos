#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "grafo.hpp"

using namespace std;

int pegarNumeroDeVertices(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return 0;
    }

    string primeiraLinha;
    getline(arquivo, primeiraLinha);

    arquivo.close();

    return stoi(primeiraLinha);
}

void lerArquivoEadicionarArestas(const string& nomeArquivo, Grafo &grafo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    getline(arquivo, linha);  // Pula a primeira linha

    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        int v1, v2, peso;
        if (iss >> v1 >> v2 >> peso) {
            grafo.adicionarAresta(v1, v2, peso);
        } else {
            cerr << "Erro ao ler a linha: " << linha << endl;
        }
    }

    arquivo.close();
}

Grafo montarGrafo(const string &nomeArquivo, bool grafoDirecionado, bool arestaPonderada, bool verticePonderado) {
    int numeroDeVertices = pegarNumeroDeVertices(nomeArquivo);
    Grafo grafo(grafoDirecionado);

    for(int i = 0; i <= numeroDeVertices; i++) {
        grafo.adicionarVertice(0);
    }

    lerArquivoEadicionarArestas(nomeArquivo, grafo);

    return grafo;
}

void menuDeOpcoes(Grafo &grafo) {
    string opcaoEscolhida, noEscolhido, continuar;
    list<int> conjuntoDeVertices;
    int numVertices;
    bool continuarRodando = true;

    while(continuarRodando) {
        cout << "Digite o valor da opção que deseja executar" << endl;
        cout << "1) Mostrar a vizinhança aberta de um nó" << endl;
        cout << "2) Mostrar a vizinhança fechada de um nó" << endl;
        cout << "3) Verificar se o grafo é bipartido" << endl;
        cout << "4) Mostrar o fecho transitivo direto de um nó" << endl;
        cout << "5) Mostrar o fecho transitivo indireto de um nó" << endl;
        cout << "6) Mostrar o subgrafo vertice induzido de um conjunto de nós" << endl;
        cout << "7) Mostrar o conjunto de vértices formados pela clique de peso maximo (Guloso)" << endl;
        cout << "8) Mostrar o conjunto de vértices formados pela clique de peso maximo (Guloso randomizado adaptativo)" << endl;
        cout << "9) Mostrar o conjunto de vértices formados pela clique de peso maximo (Guloso randomizado adaptativo reativo)" << endl;

        cout << endl << "Opção: ";

        cin >> opcaoEscolhida;

        switch(stoi(opcaoEscolhida)) {
            case 1:
                cout << endl << "Nó: ";
                cin >> noEscolhido;
                cout << "Vizinhança aberta do vértice " << noEscolhido << ": ";
                for(int vertice : grafo.retornarVizinhancaAberta(stoi(noEscolhido))) {
                    cout << vertice << " ";
                }
                break;
            case 2:
                cout << endl << "Nó: ";
                cin >> noEscolhido;

                cout << "Vizinhança fechada do vértice " << noEscolhido << ": ";
                for(int vertice : grafo.retornarVizinhancaFechada(stoi(noEscolhido))) {
                    cout << vertice << " ";
                }
                
                break;
            case 3:
                cout << "O grafo ";
                grafo.verificarGrafoBipartido() ? cout << "é bipartido" : cout << "não é bipartido";

                break;
            case 4:
                cout << endl << "Nó: ";
                cin >> noEscolhido;

                cout << "Fecho transitivo direto do vértice " << noEscolhido << ": ";
                for(int vertice : grafo.retornarFechoTransitivoDireto(stoi(noEscolhido))) {
                    cout << vertice << " ";
                }
                
                break;
            case 5:
                cout << endl << "Nó: ";
                cin >> noEscolhido;

                cout << "Fecho transitivo indireto do vértice " << noEscolhido << ": ";
                for(int vertice : grafo.retornarFechoTransitivoIndireto(stoi(noEscolhido))) {
                    cout << vertice << " ";
                }
                
                break;
            case 6:
                cout << "Digite a quantidade de vértices do conjunto: ";
                cin >> numVertices;
                cout << "Digite os vértices do conjunto:" << endl;
                for (int i = 0; i < numVertices; i++) {
                    int vertice;
                    cin >> vertice;
                    conjuntoDeVertices.push_back(vertice);
                }
                
                cout << "Subgrafo induzido: ";
                for (int vertice : grafo.retornarSubgrafoVerticeInduzido(conjuntoDeVertices)) {
                    cout << vertice << " ";
                }
                
                break;

            case 7:
                cout << "A clique de peso maxima encontrado pelo algoritmo guloso foi: ";
                for (int vertice : grafo.retornarCliqueDePesoMaximoGuloso()) {
                    cout << vertice << " ";
                }

                cout << endl << "O peso da clique encontrada foi: " << grafo.retornarPesoMaximoClique() << " ";
                
                break;
            case 8:
                cout << "A clique de peso maxima encontrado pelo algoritmo guloso randomizado adaptativo foi: ";

                for (int vertice : grafo.encontrarCliquePesoMaximoRandomizadoAdaptativo(100, 1)) {
                    cout << vertice << " ";
                }

                cout << endl << "O peso da clique encontrada foi: " << grafo.retornarPesoMaximoClique() << " ";
                
                break;
            case 9:
                cout << "A clique de peso maxima encontrado pelo algoritmo guloso randomizado adaptativo foi: ";

                for (int vertice : grafo.encontrarCliquePesoMaximoRandomizadoAdaptativoReativo(100, 1)) {
                    cout << vertice << " ";
                }

                cout << endl << "O peso da clique encontrada foi: " << grafo.retornarPesoMaximoClique() << " ";
                
                break;
            default:
                break;
        }

        cout << endl << endl;
        cout << "=========================================================================================";
        cout << endl << endl;

        cout << "Se deseja continuar utilizando o menu digite 's'" << endl;
        cin >> continuar;

        continuarRodando = continuar == "s" ? true : false;

        cout << endl << endl;
        cout << "=========================================================================================";
        cout << endl << endl;
    }
}

int main(int argc, char **argv) {

    string arquivoEntrada = argv[1];
    string arquivoDestino = argv[2];

    bool grafoDirecionado = stoi(argv[3]) == 1 ? true : false;
    bool arestaPonderada = stoi(argv[4]) == 1 ? true : false;
    bool verticePonderado = stoi(argv[5]) == 1 ? true : false;

    Grafo grafo = montarGrafo(arquivoEntrada, grafoDirecionado, arestaPonderada, verticePonderado);

    menuDeOpcoes(grafo);
    
    return 0;
}

