#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "grafo.hpp"
#include "aresta.hpp"
#include "vertice.hpp"
#include "io.hpp"

using namespace std;

/**
 *
 * Função responsável pela interface com o usuário pela ler o nome do arquivo de entrada
 *
 **/
string leNomeArquivoEntrada(){
    string escolha;
    cout<< "Deseja digitar o nome do arquivo de entrada ou utilizar o primeiro arquivo válido?" << endl << "As instancias deverao estar no diretório 'Entradas' "<<endl<<endl;
    cout<< "1) Informar nome do arquivo txt 2) Usar primeiro arquivo válido" << endl <<"Escolha:";
    string nomeArquivo;
    while (true){
        cin >> escolha;
        if (escolha=="1"){
            cout << "Nome do arquivo (sem extensão):";
            cin >>nomeArquivo;
            nomeArquivo += ".txt";
            return nomeArquivo;
        } else if (escolha=="2"){
            return "";
        } else{
            cout << "Opção inválida" << endl << "Digite sua escolha novamente:";
        }
    }
}

/**
 *
 * Função responsável por inserir o menu em tela e realizar os tratamentos e chamadas de funções
 * de acordo com a opção escolhida
 *
 **/
void incluirMenu(Grafo *g, IO *x){
    string strEscolha, nomeArquivo, retornar, strEscolhaAux;
    int escolha;
    bool opInvalida =false;
    cout << endl << endl;
    while(true){
        system("clear");
        if (opInvalida)
            cout << "Opção inválida" <<endl << "Digite novamente:" <<endl;
        else
            cout << "Digite a opção desejada:" <<endl;
        opInvalida = false;
        cout << "\t 1) Ler um novo grafo" <<endl;
        cout << "\t 2) Imprimir grafo" <<endl;
        cout << "\t 3) Imprimir número de nós e arestas" <<endl;
        cout << "\t 0) Sair" <<endl;
        cout << endl << "Opção: ";
        cin >> strEscolha;
        escolha = atoi(strEscolha.c_str());
        system("clear");
        switch(escolha){
            case 0:
                cout<< "Saindo do programa;" <<endl;
                return;
            case 1:
                g->resetaGrafo();
                nomeArquivo = leNomeArquivoEntrada();
                x->setNomeEntrada(nomeArquivo);
                x->leGrafo(g);
                break;
            case 2:
                g->imprimeGrafo();
                break;
            case 3:
                cout<< "Número de nós: " << g->getNumNos() << endl;
                cout<< "Número de arestas: " << g->getNumArestas() << endl;
                break;
            default:
                opInvalida = true;

        }

        cout << endl<< endl<<"Pressione ENTER para voltar ao menu."<<endl;

        if (!opInvalida)
            system("read retornar");

    }
}


int main()
{
    string nomeArquivo, direcionado;
    bool flagDir=false;
    nomeArquivo = leNomeArquivoEntrada();
    system("clear");

    Grafo* g = new Grafo(1, flagDir);
    IO *x = new IO(nomeArquivo);
    x->leGrafo(g);
    incluirMenu(g,x);


    delete g;
    delete x;
    return 0;
}
