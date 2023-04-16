#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

class Grafo;

class IO {
private:
    char diretorioEntradas[200];
    char diretorioSaidas[200];
    std::string nomeEntrada;

    const char* getCaminhoDiretorio();
    void leituraGrafo(Grafo* g, char* caminhoDiretorio);
    void geraSaidaBusca(std::string saida, char* nomeArquivo, char* caminhoSaida);

public:
    IO(std::string = "");
    ~IO(){};
    char* getDiretorioEntradas(){return diretorioEntradas;};
    std::string getNomeEntrada(){return nomeEntrada;};
    void setNomeEntrada(std::string nomeArquivo){nomeEntrada= nomeArquivo;};

    void leGrafo(Grafo* g);
    void saidaBusca(char* nomeArquivo, std::string saida);
};

#endif // IO_HPP_INCLUDED
