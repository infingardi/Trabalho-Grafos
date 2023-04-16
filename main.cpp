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
 * Fun��o respons�vel pela interface com o usu�rio pela ler o nome do arquivo de entrada
 *
 **/
string leNomeArquivoEntrada(){
    string escolha;
    cout<< "Deseja digitar o nome do arquivo de entrada ou utilizar o primeiro arquivo v�lido?" << endl << "As instancias deverao estar no diret�rio 'Entradas' "<<endl<<endl;
    cout<< "1) Informar nome do arquivo txt 2) Usar primeiro arquivo v�lido" << endl <<"Escolha:";
    string nomeArquivo;
    while (true){
        cin >> escolha;
        if (escolha=="1"){
            cout << "Nome do arquivo (sem extens�o):";
            cin >>nomeArquivo;
            nomeArquivo += ".txt";
            return nomeArquivo;
        } else if (escolha=="2"){
            return "";
        } else{
            cout << "Op��o inv�lida" << endl << "Digite sua escolha novamente:";
        }
    }
}

/**
 *
 * Fun��o respons�vel por inserir o menu em tela e realizar os tratamentos e chamadas de fun��es
 * de acordo com a op��o escolhida
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
            cout << "Op��o inv�lida" <<endl << "Digite novamente:" <<endl;
        else
            cout << "Digite a op��o desejada:" <<endl;
        opInvalida = false;
        cout << "\t 1) Ler um novo grafo" <<endl;
        cout << "\t 2) Imprimir grafo" <<endl;
        cout << "\t 3) Imprimir n�mero de n�s e arestas" <<endl;
        cout << "\t 0) Sair" <<endl;
        cout << endl << "Op��o: ";
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
                cout<< "N�mero de n�s: " << g->getNumNos() << endl;
                cout<< "N�mero de arestas: " << g->getNumArestas() << endl;
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
