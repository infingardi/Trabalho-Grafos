#ifndef GRAFO_HPP_INCLUDED
#define GRAFO_HPP_INCLUDED

#include "aresta.hpp"
#include "vertice.hpp"
#include "io.hpp"


class Grafo{
private:
    ListaVertice* lv;
    int numeroNos;
    int contadorNos;
    int numeroArestas;
    int grauEntrada;
    int grauSaida;
    bool flagDir;
    int id;
    bool idsAtualizados;

    void buscaEmProfundidadeF(Vertice* v, bool* vetColoracao, int nivel, Vertice* pai, IO* saida, char* nomeArquivo);
    void buscaEmLarguraF(Vertice* v, int* vetColoracao, bool* vetColoracaoB, bool* vetColoracaoC, IO* saida, char* nomeArquivo);
    void setDefault(int numNos);
    void limpaGrafo();

public:
    Grafo(int numNos, bool dir);
    ~Grafo();

    void resetaGrafo();
    int getId(){return id;};
    int getNumNos(){return numeroNos;};
    int getNumArestas(){return numeroArestas;};
    int getGrauEntrada(){return grauEntrada;};
    int getGrauSaida(){return grauSaida;};
    bool isDir(){return flagDir;};
    void setNumNos(int n){numeroNos = n;};
    void setNumArestas(int n){numeroArestas = n;};
    void setGrauEntrada(int n){grauEntrada = n;};
    void setGrauSaida(int n){grauSaida = n;};
    void setFlagDir(bool n){flagDir = n;};

    void insereVertice(int infoNo, int pesoNo);
    void insereAresta(int infoNo1, int pesoNo1, int infoNo2, int pesoNo2, int pesoAresta);
    void imprimeGrafo();
    void buscaEmProfundidade(int infoNo);
    void buscaEmLargura(int infoNo);

};

#endif // GRAFO_HPP_INCLUDED
