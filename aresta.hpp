#ifndef ARESTA_HPP_INCLUDED
#define ARESTA_HPP_INCLUDED

class Vertice;//apenas a declaração para o programa saber que existe

class Aresta{
private:
    int peso;
    Vertice* vertice;
    Aresta* prox;
    Vertice* verticeOrigem;
public:
    Aresta(Vertice* v, Vertice* origem, int vpeso);
    int getPeso();
    Vertice* getVertice();
    Vertice* getVerticeOrigem();
    Aresta* getProx();
    void setPeso(int n);
    void setVertice(Vertice* v);
    void setProx(Aresta* a);
    ~Aresta(){};
};

class ListaAresta{
private:
    Aresta* raiz;
    Aresta* ultimo;
    int numNos;
public:
    ListaAresta(Aresta* r, Aresta* u, int nNos);
    ~ListaAresta();
    Aresta* getRaiz();
    Aresta* getUltimo();
    int getNumNos();
    void setRaiz(Aresta* a);
    void setUltimo(Aresta* a);
    void setNumNos(int n);
    void insere(Vertice* v, Vertice* origem, int peso);
    bool exclui(Vertice* v);
};

#endif // ARESTA_HPP_INCLUDED
