#include <iostream>
#include <cstdlib>
#include <cmath>
#include  <climits>
#include <time.h>
#include <sstream>

#include "grafo.hpp"
#include "aresta.hpp"
#include "vertice.hpp"

#define imprimeDestrutor false

using namespace std;


Grafo::Grafo(int numNos, bool dir)
{
    flagDir = dir;
    setDefault(numNos);
}

/**
 * Seta opções default do grafo
 * nos dados dele.
 **/
void Grafo::setDefault(int numNos){
    lv = new ListaVertice(NULL, NULL, numNos);
    contadorNos = 0;
    numeroArestas = 0;
    numeroNos = numNos;
    grauEntrada = 0;
    grauSaida = 0;
    id = 0;
    idsAtualizados = true;
}

/**
 * Método responsável por resetar o grafo em tempo de execução
 *
 **/
void Grafo::resetaGrafo(){
    limpaGrafo();
    setDefault(0);
}

/**
 * Método responsável por limpar os dados do grafo
 *
 **/
void Grafo::limpaGrafo(){
    delete lv;
    if (imprimeDestrutor)
        cout << "Grafo excluído" << endl;
}

Grafo::~Grafo()
{
    limpaGrafo();
};


/**
 * Insere um vertice no grafo e realiza os ajustes
 * nos dados dele.
 **/
void Grafo::insereVertice(int infoNo, int pesoNo)
{
    Vertice* v;
    bool vNaoExiste = true;
    if(lv != NULL)
    {
         v = lv->buscaVertice(infoNo);
         if(v != NULL)
            vNaoExiste = false;
    }
    if(vNaoExiste)
    {
        No* n = new No(id, infoNo, 0, 0, pesoNo);
        lv->insereVertice(n);
        v = lv->getUltimo();

        if(v->getNo()->getGrauSaida() > grauSaida)
            grauSaida = v->getNo()->getGrauSaida();
        if(v->getNo()->getGrauEntrada() > grauEntrada)
            grauEntrada = v->getNo()->getGrauEntrada();

        id++;
        contadorNos++;
        if(contadorNos > numeroNos)
            numeroNos = contadorNos;
    }
}


/**
 * Isere uma aresta no grafo e realiza os ajustes
 * nos dados dele.
 * Caso algum dos vértices não exista, o cria.
 **/
void Grafo::insereAresta(int infoNo1, int pesoNo1, int infoNo2, int pesoNo2, int pesoAresta)
{
        Vertice* v = lv->buscaVertice(infoNo1);
        Vertice* a = lv->buscaVertice(infoNo2);

        bool existeV = true;
        bool existeA = true;
        bool existeAresta = false;

        //verifica se os vertices a serem ligados por uma aresta existem. se não, os cria
        if(v == NULL)
        {
            existeV = false;
            insereVertice(infoNo1, pesoNo1);
            v = lv->getUltimo();
        }
        if(a == NULL)
        {
            existeA = false;
            insereVertice(infoNo2, pesoNo2);
            a = lv->getUltimo();
        }

        if(existeV && existeA) //se os dois vertices foram encontrados na busca, pode haver aresta entre eles
        {
            Aresta* arestasV = v->getArestas()->getRaiz();
            while(arestasV != NULL)
            {
                if(infoNo2 == arestasV->getVertice()->getNo()->getInfo())
                {
                    existeAresta = true; //caso a aresta ja exista
                    break;
                }
                else
                {
                    arestasV = arestasV->getProx();
                }
            }
        }

        if(!existeAresta)
        {
            lv->insereAresta(v, a, pesoAresta, flagDir);

            if(v->getNo()->getGrauSaida() > grauSaida)
                grauSaida = v->getNo()->getGrauSaida();
            if(v->getNo()->getGrauEntrada() > grauEntrada)
                grauEntrada = v->getNo()->getGrauEntrada();

            if(a->getNo()->getGrauSaida() > grauSaida)
                grauSaida = a->getNo()->getGrauSaida();
            if(a->getNo()->getGrauEntrada() > grauEntrada)
                grauEntrada = a->getNo()->getGrauEntrada();

            numeroArestas++;
        }


}


/**
 * Imprime o grafo.
 **/
void Grafo::imprimeGrafo()
{
    cout << endl << "Grafo: " << endl;
    lv->imprime();
}


/**
 *
 * Função auxiliar que converte números inteiros para string.
 * @param n - número inteiro a ser transformado em string
 **/
string intToString(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

/**
 * Realiza a busca em profundidade a partir de um no passado por parametro
 * @param infoNo - info do no inicial para a busca
 **/
void Grafo::buscaEmProfundidade(int infoNo)
{
    bool* vetColoracao = new bool[numeroNos]; //Vetor auxiliar para marcar os vertices percorridos
    Vertice* v = lv->getRaiz();
    IO* saida = new IO();
    string resultado = "Inicio";
    char nomeArquivo[10] = "BuscaProf";
    saida->saidaBusca(nomeArquivo,resultado);
    if(!idsAtualizados)
    {
        for(int i=0; v!=NULL && i<numeroNos;i++)
        {
            v->getNo()->setId(i);  //Atualiza ids
            vetColoracao[i]=0;
            v = v->getProx();
        }
        cout << endl << "Ids atualizados!" << endl;
        idsAtualizados = true;
    }
    else
    {
        for(int i=0; i<numeroNos;i++)
        {
            vetColoracao[i]=0;
        }
    }
    int nivel=0;
    Vertice* pai = NULL;
    v = lv->buscaVertice(infoNo);
    resultado = "Busca em profundidade a partir do No: " +  intToString(infoNo);
    cout << resultado << endl;
    saida->saidaBusca(nomeArquivo,resultado);
    if(v!=NULL){
        buscaEmProfundidadeF(v, vetColoracao, nivel, pai,saida,nomeArquivo);
    }
    else{
        resultado = "No nao encontrado!";
        cout << resultado << endl;
        saida->saidaBusca(nomeArquivo,resultado);
    }

    resultado = "Fim";
    saida->saidaBusca(nomeArquivo,resultado);
    delete [] vetColoracao;
    delete saida;
}

/**
 * Parte recursiva da busca em profundidade
 * @param v - Vertice que esta sendo visitado no momento
 * @param vetColoracao - Vetor responsavel pelo armazenamento das cores
 * @param nivel - Nivel a ser impresso da arvore
 * @param pai - Pai do vertice que esta sendo visitado no momento
 * @param saida - objeto responsável pela escrita em arquivo
 * @param nomeArquivo - nome do arquivo de saída
 **/
void Grafo::buscaEmProfundidadeF(Vertice* v, bool* vetColoracao, int nivel, Vertice* pai, IO* saida, char* nomeArquivo)
{
    string resultado;
    if(v == NULL)
        return;
    if(nivel == 0)
        resultado = "No: " + intToString(v->getNo()->getInfo()) + " Pai: NULL Nivel: " + intToString(nivel);
    else
        resultado = "No: " + intToString(v->getNo()->getInfo()) + " Pai: " + intToString(pai->getNo()->getInfo()) + " Nivel: " + intToString(nivel);

    cout << resultado << endl;
    saida->saidaBusca(nomeArquivo,resultado);

    vetColoracao[v->getNo()->getId()] = 1; //marca Nó atual como percorrido
    Aresta* a1 = v->getArestas()->getRaiz();
    while(a1 != NULL)
    {
        if(vetColoracao[a1->getVertice()->getNo()->getId()] == 0) //verifica se o vértice da lista de arestas já foi percorrido
            buscaEmProfundidadeF(a1->getVertice(), vetColoracao, nivel+1, v, saida, nomeArquivo);
        a1 = a1->getProx();
    }
}

/**
 * Realiza a busca em largura a partir de um no passado por parametro
 * @param infoNo - info do no inicial para a busca
 **/
void Grafo::buscaEmLargura(int infoNo)
{
    int* vetColoracao = new int[numeroNos];    //Vetor para armazenar a "fila" dos que serão percorridos
    bool* vetColoracaoB = new bool[numeroNos]; //Vetor auxiliar para marcar os vértices percorridos
    bool* vetColoracaoC = new bool[numeroNos]; //Vetor auxiliar para marcar os vértices impressos
    Vertice* v = lv->getRaiz();
    IO* saida = new IO();
    string resultado = "Inicio";
    char nomeArquivo[13] = "BuscaLargura";
    saida->saidaBusca(nomeArquivo,resultado);
    if(!idsAtualizados)
    {
        for(int i=0; v!=NULL && i<numeroNos;i++)
        {
            v->getNo()->setId(i);       //Atualiza ids
            vetColoracaoB[i] = 0;
            vetColoracaoC[i] = 0;
            v = v->getProx();
        }
        cout << endl << "Ids atualizados!" << endl;
        idsAtualizados = true;
    }
    else
    {
        for(int i=0; i<numeroNos;i++)
        {
            vetColoracaoB[i] = 0;
            vetColoracaoC[i] = 0;
        }
    }
    v = lv->buscaVertice(infoNo);

    resultado = "Busca em largura a partir do No: " + intToString(infoNo);
    cout<< resultado << endl;
    saida->saidaBusca(nomeArquivo,resultado);

    if(v!=NULL){
        buscaEmLarguraF(v, vetColoracao, vetColoracaoB, vetColoracaoC, saida, nomeArquivo);
    }
    else{
        resultado = "No nao encontrado!";
        cout<< resultado << endl;
        saida->saidaBusca(nomeArquivo,resultado);
    }
    resultado = "Fim";
    saida->saidaBusca(nomeArquivo,resultado);
    delete saida;
    delete [] vetColoracaoB;
    delete [] vetColoracaoC;
    delete [] vetColoracao;
}

/**
 * Realiza de fato a busca em profundidade a partir de um no passado por parametro
 * @param pai - Pai do no que esta sendo visitado no momento
 * @param vetColoracao - Vetor responsavel pelo armazenamento da fila de nos nao visitados
 * @param vetColoracaoB - Vetor responsavel por marcar os nos ja percorridos
 * @param vetColoracaoC - Vetor responsavel por marcar os nos ja impressos
 * @param saida - objeto responsável pela escrita em arquivo
 * @param nomeArquivo - nome do arquivo de saída
 **/
void Grafo::buscaEmLarguraF(Vertice* pai, int* vetColoracao, bool* vetColoracaoB, bool* vetColoracaoC, IO* saida, char* nomeArquivo)
{
    int nivel=0; //responsável por imprimir o nivel do Nó
    int posA=0;  //índice responsavél por inserir os Nós na fila
    int posB=0;  //índice responsavel por marcar os Nós que já foram impressos
    int ll=0;    //variavel auxiliar para controlar o valor do nivel
    string resultado;
    resultado = "No: " + intToString(pai->getNo()->getInfo()) + " Pai: NULL Nivel: " + intToString(nivel);
    cout << resultado << endl;
    saida->saidaBusca(nomeArquivo,resultado);

    vetColoracao[posA] = pai->getNo()->getInfo(); //adiciona Nó atual no vetor de percorridos
    vetColoracaoB[pai->getNo()->getId()] = 1;     //marca Nó atualcomo já percorrido
    vetColoracaoC[pai->getNo()->getId()] = 1;     //marca Nó atual como já impresso
    posA++;
    nivel++;

    Aresta* a1 = pai->getArestas()->getRaiz();    //pega a lista de adjacentes do pai
    while(1)
    {
        while(a1 != NULL)
        {
            if(vetColoracaoC[a1->getVertice()->getNo()->getId()] == 0)//só é impresso e adicionado na lista, caso ainda não tenha sido impresso
            {
                resultado = "No: " + intToString(a1->getVertice()->getNo()->getInfo()) + " Pai: " + intToString(pai->getNo()->getInfo()) + " Nivel: " + intToString(nivel);
                cout << resultado << endl;
                saida->saidaBusca(nomeArquivo,resultado);
                vetColoracao[posA] = a1->getVertice()->getNo()->getInfo();  //adiciona filho na lista
                posA++;
            }
            vetColoracaoC[a1->getVertice()->getNo()->getId()] = 1; //marca como já impresso

            a1 = a1->getProx();
        }

        if(posB == ll)  //controla o nivel de cada no
        {
            ll = posA-1;
            nivel++;
        }
        posB++;

        if(posA == posB)
            break;     //se a posiçao vaga do vetor da fila for igual a de quem nao foi percorrido

        pai = lv->buscaVertice(vetColoracao[posB]);  //proximo na fila
        vetColoracaoB[pai->getNo()->getId()] = 1;
        a1 = pai->getArestas()->getRaiz();

        while(a1!=NULL && vetColoracaoB[a1->getVertice()->getNo()->getId()] == 1)
        {
            a1 = a1->getProx();     //para não voltar em vertices ja percorridos
        }
    }
}
