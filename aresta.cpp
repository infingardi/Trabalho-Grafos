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
 * Cria uma aresta entre o v�rtice de origem e o v�rtice de destino
 * Exemplo: origem -----> destino
 **/
void ListaAresta::insere(Vertice* v,Vertice* origem, int peso)
{
    Aresta* a = new Aresta(v, origem, peso);
    //se o v�rtice de origem n�o possuir arestas,
    //o vertice de destino a ser inserido ser� a ra�z da lista de aresta
    if(raiz == NULL)
    {
        raiz = a;
        ultimo = a;
    }
    //se n�o, ser� incl�ido ap�s o �ltimo item
    else
    {
        ultimo->setProx(a);
        ultimo = a;
    }
    numNos++;
}

/**
 * Exclui a aresta corresponde ao v�rtice passado no par�metro.
 * Retorna false caso o v�rtice n�o existir na lista.
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
            //come�a do segundo v�rtice percorrendo a lista de arestas at�
            //localizar o v�rtice a ser exclu�do desta.
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
