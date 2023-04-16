#ifndef VERTICE_HPP_INCLUDED
#define VERTICE_HPP_INCLUDED

class ListaAresta;//apenas a declaração para o programa saber que existe




class No{
private:
    int id; //PK
    int info;
    int grauEntrada;
    int grauSaida;
    int peso;
public:
    No(int vid, int vinfo, int vgrauEntrada, int vgrauSaida, int vpesoNo);
    int getId();
    int getInfo();
    int getGrauEntrada();
    int getGrauSaida();
    int getPeso();
    void setId(int n);
    void setInfo(int n);
    void setGrauEntrada(int n);
    void setGrauSaida(int n);
    void setPeso(int n);
    ~No(){};
};

class Vertice{
private:
    No* n;
    ListaAresta* arestas;
    Vertice* prox;
public:
    Vertice(int numNos, No* novo);
    ListaAresta* getArestas(){return arestas;};
    No* getNo(){return n;};
    Vertice* getProx(){return prox;};
    void setProx(Vertice* v){prox = v;};
    ~Vertice();
};

class ListaVertice{
private:
    Vertice* raiz;
    Vertice* ultimo;
    int numNos;
public:
    ListaVertice(Vertice* r, Vertice* u, int nNos);
    ~ListaVertice();
    Vertice* getRaiz();
    Vertice* getUltimo();
    int getNumNos();
    void setRaiz(Vertice* v);
    void setUltimo(Vertice* v);
    void setNumNos(int n);
    void insereVertice(No* n);
    void excluiVertice(int infoNo);
    Vertice* buscaVertice(int infoNo);
    Vertice* buscaVerticePorId(int id);
    Vertice* buscaVerticePorGrau(int grau);
    void insereAresta(Vertice* vertice, Vertice* aresta, int pesoAresta, bool eDirecionado);
    void imprime();
};

#endif // VERTICE_HPP_INCLUDED
