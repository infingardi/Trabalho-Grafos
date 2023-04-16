#include <iostream>
#include "aresta.hpp"
#include "vertice.hpp"
#define imprimeDestrutor false

using namespace std;

Aresta::Aresta(Vertice* v, Vertice* origem, int vpeso)
{
    vertice = v;
    verticeOrigem = origem;
    peso = vpeso;
    prox = NULL;
}
int Aresta::getPeso(){return peso;}
Vertice* Aresta::getVertice(){return vertice;}
Vertice* Aresta::getVerticeOrigem(){return verticeOrigem;}
Aresta* Aresta::getProx(){return prox;}
void Aresta::setPeso(int n){peso = n;}
void Aresta::setVertice(Vertice* v){vertice = v;}
void Aresta::setProx(Aresta* a){prox = a;}



ListaAresta::ListaAresta(Aresta* r, Aresta* u, int nNos)
{
    raiz = r;
    ultimo = u;
    numNos = nNos;
}
ListaAresta::~ListaAresta()
{
    Aresta *a = raiz;
    Aresta *b;
    if (imprimeDestrutor)
            cout << "Destrutor: Excluindo arestas do vertice " << a->getVerticeOrigem()->getNo()->getInfo()<<endl;
    while(a != NULL)
    {
        b = a->getProx();
        delete a;
        a = b;
    }
}
Aresta* ListaAresta::getRaiz(){return raiz;}
Aresta* ListaAresta::getUltimo(){return ultimo;}
int ListaAresta::getNumNos(){return numNos;}
void ListaAresta::setRaiz(Aresta* a){raiz = a;}
void ListaAresta::setUltimo(Aresta* a){ultimo = a;}
void ListaAresta::setNumNos(int n){numNos = n;}

/**
 * Cria uma aresta entre o vértice de origem e o vértice de destino
 * Exemplo: origem -----> destino
 **/
void ListaAresta::insere(Vertice* v,Vertice* origem, int peso)
{
    Aresta* a = new Aresta(v, origem, peso);
    //se o vértice de origem não possuir arestas,
    //o vertice de destino a ser inserido será a raíz da lista de aresta
    if(raiz == NULL)
    {
        raiz = a;
        ultimo = a;
    }
    //se não, será inclúido após o último item
    else
    {
        ultimo->setProx(a);
        ultimo = a;
    }
    numNos++;
}

/**
 * Exclui a aresta corresponde ao vértice passado no parâmetro.
 * Retorna false caso o vértice não existir na lista.
 **/
bool ListaAresta::exclui(Vertice* v)
{
    if(raiz != NULL)
    {
        Aresta* atual = raiz->getProx(); //recebe o segundo vertice da lista de arestas
        if(raiz->getVertice()->getNo()->getId() == v->getNo()->getId())
        {//se a raiz for a aresta a ser excluida
            delete raiz;
            raiz = atual;
            return true;
        }
        else
        {
            Aresta* anterior = raiz;
            Aresta* proximo = NULL;
            //começa do segundo vértice percorrendo a lista de arestas até
            //localizar o vértice a ser excluído desta.
            //quando o localiza, exclui e faz os devidos ajustes na lista
            while(atual != NULL)
            {
                if(atual->getVertice()->getNo()->getId() == v->getNo()->getId())
                {
                    if(atual == ultimo)
                    { //caso o vertice a excluir seja o ultimo da lista de arestas
                        ultimo = anterior;
                    }
                    proximo = atual->getProx();
                    anterior->setProx(proximo);
                    delete atual;
                    numNos--;
                    return true;
                }
                else
                {
                    anterior = atual;
                    atual = atual->getProx();
                }
            }
        }
    }
    return false;
}
