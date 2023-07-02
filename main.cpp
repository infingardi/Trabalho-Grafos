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
    bool continuarRodando = true;

    while(continuarRodando) {
        cout << "Digite o valor da opção que deseja executar" << endl;
        cout << "1) Mostrar a vizinhança aberta de um nó" << endl;
        cout << "2) Mostrar a vizinhança fechada de um nó" << endl;
        cout << "3) Verificar se o grafo é bipartido" << endl;

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

