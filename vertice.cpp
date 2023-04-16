#include <iostream>
#include "aresta.hpp"
#include "vertice.hpp"
#define imprimeDestrutor false

using namespace std;

No::No(int vid, int vinfo, int vgrauEntrada, int vgrauSaida, int vpesoNo)
{
    id = vid; //chave primaria
    info = vinfo; //informa��o do n�
    grauEntrada = vgrauEntrada;
    grauSaida = vgrauSaida;
    peso = vpesoNo;
}
int No::getId(){return id;}
int No::getInfo(){return info;}
int No::getGrauEntrada(){return grauEntrada;};
int No::getGrauSaida(){return grauSaida;};
int No::getPeso(){return peso;}
void No::setId(int n){id = n;}
void No::setInfo(int n){info = n;}
void No::setGrauEntrada(int n){grauEntrada = n;};
void No::setGrauSaida(int n){grauSaida = n;};
void No::setPeso(int n){peso = n;}


Vertice::Vertice(int numNos, No* novo)
{
    n = novo;
    arestas = new ListaAresta(NULL, NULL, 0); //desconsidera selfloop
    prox = NULL;
}

Vertice::~Vertice(){
    delete arestas;
    delete n;
};


ListaVertice::ListaVertice(Vertice* r, Vertice* u, int nNos)
{
    raiz = r;
    ultimo = u;
    numNos = nNos;
}

ListaVertice::~ListaVertice()
{
    Vertice *v = raiz;
    Vertice *w;
    while(v != NULL)
    {
        if (imprimeDestrutor)
            cout << "Destrutor: Excluindo vertice " << v->getNo()->getInfo() << endl;
        w = v->getProx();
        delete v;
        v = w;
    }
}
Vertice* ListaVertice::getRaiz(){return raiz;}
Vertice* ListaVertice::getUltimo(){return ultimo;}
int ListaVertice::getNumNos(){return numNos;}
void ListaVertice::setRaiz(Vertice* v){raiz = v;}
void ListaVertice::setUltimo(Vertice* v){ultimo = v;}
void ListaVertice::setNumNos(int n){numNos = n;}

/**
 * Cria um novo v�rtice e o insere na lista de v�rtices
 **/
void ListaVertice::insereVertice(No* n)
{
    Vertice* v = new Vertice(numNos, n);
    if(raiz == NULL)
    {//se o grafo for nulo, ser� o primeiro v�rtice e, portanto, ra�z da lista
        raiz = v;
        ultimo = v;
    }
    else
    {//se n�o, ser� inserido logo ap�s o �ltimo vertice da lista
        ultimo->setProx(v);
        ultimo = v;
    }
    numNos++;
}

/**
 * @param infoNo - informa��o de um n�.
 * Pesquisa, utilizando 'infoNo', se um v�rtice existe na lista de v�rtices e o retorna.
 * Retorna NULL se o v�rtice n�o existir.
 **/
Vertice* ListaVertice::buscaVertice(int infoNo)
{
    if(raiz != NULL)
    {
        Vertice* v = raiz;
        //caso o grafo n�o seja nulo, percorre a lista de vertices
        //e retorna se achar o v�rtice pesquisado
        while(v != NULL)
        {
            if(v->getNo()->getInfo() == infoNo)
                return v;
            else
                v = v->getProx();
        }
    }
    return NULL;
}

/**
 * @param id - identificador (chave prim�ria) de um n�.
 * Pesquisa, utilizando 'id', se um v�rtice existe na lista de v�rtices e o retorna.
 * Retorna NULL se o v�rtice n�o existir.
 **/
Vertice* ListaVertice::buscaVerticePorId(int id)
{
    if(raiz != NULL)
    {
        Vertice* v = raiz;
        //caso o grafo n�o seja nulo, percorre a lista de vertices
        //e retorna se achar o v�rtice pesquisado
        while(v != NULL)
        {
            if(v->getNo()->getId() == id)
                return v;
            else
                v = v->getProx();
        }
    }
    return NULL;
}

/**
 * @param grau - grau de entrada de um n�.
 * Pesquisa se existe um v�rtice na lista de v�rtices com o grau referente e o retorna.
 * Retorna NULL se o v�rtice n�o existir.
 **/
Vertice* ListaVertice::buscaVerticePorGrau(int grau)
{
    if(raiz != NULL)
    {
        Vertice* v = raiz;
        //caso o grafo n�o seja nulo, percorre a lista de vertices
        //e retorna se achar o v�rtice pesquisado
        while(v != NULL)
        {
            if(v->getNo()->getGrauEntrada() == grau)
                return v;
            else
                v = v->getProx();
        }
    }
    return NULL;
}



/**
 *
 *
 **/
void ListaVertice::excluiVertice(int infoNo)
{
    Vertice* v = raiz;
    Vertice* vAnt;
    Vertice* dV;
    Aresta* x;
    Aresta* x1;
    Aresta* ant;
    ListaAresta *la;

    while(v != NULL)
    {
        if(v->getNo()->getInfo() == infoNo)
        {
            dV = v;
            if(v == raiz)
            {
                raiz = v->getProx();
            }
            else
            {
                vAnt->setProx(v->getProx());
            }
        }
        else
        {
            Aresta* a1 = v->getArestas()->getRaiz();
            while(a1 != NULL)
            {
                if(a1->getVertice()->getNo()->getInfo() == infoNo)
                {
                    x = a1;
                    if(a1->getVertice()->getNo()->getInfo() == v->getArestas()->getRaiz()->getVertice()->getNo()->getInfo())
                        v->getArestas()->setRaiz(a1->getProx());
                    else
                        ant->setProx(a1->getProx());
                    break;
                }
                ant = a1;
                a1 = a1->getProx();
            }
        }
        vAnt = v;
        v = v->getProx();
    }
    x = dV->getArestas()->getRaiz();
    la = dV->getArestas();
    while(x != NULL)
    {
        x1 = x;
        cout << "Aresta com o " << x->getVertice()->getNo()->getInfo() << " liberada" << endl;
        x = x->getProx();
    }
    delete x;
    delete dV;

}

/**
 * Insere uma aresta ou arco entre dois vertices.
 * Pesquisa se a aresta/arco j� existe e a cria em caso negativo.
 **/
void ListaVertice::insereAresta(Vertice* vertice, Vertice* aresta, int pesoAresta, bool eDirecionado)
{
    Vertice*v = vertice; //origem
    Vertice*a = aresta; //destino

    int i=0;
    //considera inicialmente que a aresta entre origem e destino n�o existe e, por isso, os graus precisam ser corrigidos
    bool flagGrau = false;
    Aresta* adjV = v->getArestas()->getRaiz(); //raiz da lista de arestas do vertice de origem
    Aresta* adjA = a->getArestas()->getRaiz(); //raiz da lista de arestas do vertice de destino

    //percore a lista de arestas do v�rtice de origem buscando pela aresta com o v�rtice de destino, caso exista
    while(adjV != NULL)
    {
        if(adjV->getVertice()->getNo()->getId() != a->getNo()->getId())
        {
            i++;
            adjV = adjV->getProx();
        }
        //caso localize a aresta entre origem e destino, torna flagGrau verdadeira e interrompe o loop
        else
            {flagGrau = true; break;}
    }
    //caso a aresta entre origem e destino n�o exista, a cria
    if(adjV == NULL)
    {
        v->getArestas()->insere(a, v, pesoAresta); //utiliza o proprio vertice, como � o mesmo ponteiro, quando uma de suas informa��es se altera, ela se mantem atualizada nas arestas
    }
    v->getNo()->setGrauSaida( (v->getNo()->getGrauSaida())+1 ); //incrementa o grau
    a->getNo()->setGrauEntrada( (a->getNo()->getGrauEntrada())+1 ); //incrementa o grau

    //caso o grafo n�o seja direcionado, realiza o mesmo procedimento na lista de arestas do v�rtice de destino
    if(!eDirecionado)
    {
        int j=0;
        flagGrau = false;
        while(adjA != NULL) //percore a lista buscando pela aresta, caso exista
        {
            if(adjA->getVertice()->getNo()->getId() != v->getNo()->getId())
            {
                j++;
                adjA = adjA->getProx();
            }
            else
                {flagGrau = true; break;}
        }
        if(adjA == NULL)
        {
            a->getArestas()->insere(v, a, pesoAresta);
        }
        if(!flagGrau)
        {
            a->getNo()->setGrauSaida( (a->getNo()->getGrauSaida())+1 );
            v->getNo()->setGrauEntrada( (v->getNo()->getGrauEntrada())+1 );
        }
    }

}

/**
 * Imprime todo o grafo e suas informa��es.
 **/
void ListaVertice::imprime()
{
    if(raiz != NULL)
    {
        cout << endl << "(InfoVertice, GrauEntVertice, GrauSaiVertice, IdVertice) -> (InfoAresta, GrauEntAresta, GrauSaiAresta, PesoAresta, IdAresta)" << endl << endl;
        Vertice* v = raiz;
        while(v != NULL)
        {//percorre a lista de vertices imprimindo o pr�prio e sua lista de arestas.
            cout << "(" << v->getNo()->getInfo() << ", " << v->getNo()->getGrauEntrada() << ", " << v->getNo()->getGrauSaida() << ", " << v->getNo()->getId() << ") -> ";
            Aresta* a = v->getArestas()->getRaiz();
            while(a!= NULL)
            {
                cout << "(" << a->getVertice()->getNo()->getInfo() << ", " << a->getVertice()->getNo()->getGrauEntrada() << ", "
                << a->getVertice()->getNo()->getGrauSaida() << ", " << a->getPeso() << ", " << a->getVertice()->getNo()->getId() << ") ";
                a = a->getProx();
            }
            v = v->getProx();
            cout << endl;
        }
    }
}
