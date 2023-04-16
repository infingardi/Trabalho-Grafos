#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include "io.hpp"
#include "grafo.hpp"

using namespace std;

/**
 * Recupera o caminho completo do diret�rio dos arquivos de c�digo.
 * Utiliza a diretiva "__FILE__", que retorna o caminho completo deste arquivo.
 * Remove o nome do arquivo e retorna a string resultante.
 **/
const char* IO::getCaminhoDiretorio()
{
    string f = "";
    string g = "";
    f += __FILE__;
    unsigned int i = f.size();
    //elimina o nome do arquivo
    while(f[i]!= '/' && i>0)
        i--;
    for(unsigned int j=0; j<i; j++)
        g = g + f[j];

    //trata a string para que fique interpret�vel
    char* h = new char[g.size() + 1];
    copy(g.begin(), g.end(), h);
    h[g.size()] = '\0';

    return h;
}


IO::IO(string nomeArquivo)
{
    const char* diretorio = getCaminhoDiretorio();
    nomeEntrada = nomeArquivo;

    //guarda o caminho do diret�rio que cont�m as inst�ncias
    strcpy(diretorioEntradas, diretorio);
    strcat(diretorioEntradas, "/Entradas/");

    //guarda o caminho do diret�rio que conter� as sa�das das buscas
    strcpy(diretorioSaidas, diretorio);
    strcat(diretorioSaidas, "/Saidas/");
    delete diretorio;
}

/**
 * Executa o procedimento de leitura de arquivo
 * passando o objeto onde o grafo ser� armazenado.
 **/
void IO::leGrafo(Grafo* g)
{
    //passa o objeto e o caminho onde est�o as inst�ncias
    leituraGrafo(g, diretorioEntradas);
}

/**
 * L� uma inst�ncia armazenada no diret�rio passado no par�metro
 * e armazena o grafo no objeto passado no par�metro.
 **/
void IO::leituraGrafo(Grafo* g, char* caminhoDiretorio)
{
    string linha;
    string nomeArquivo =getNomeEntrada();
    char * nomeArquivoChar;
    int num, n1, n2;
    bool flagArq = true;
    ifstream arqGrafo;
    char caminhoArquivo[200];
    strcpy(caminhoArquivo, caminhoDiretorio); //copia caminho do diretorio para o caminho do arquivo
    DIR *d;
    struct dirent *dir;

    d = opendir(caminhoDiretorio); //abre o diretorio
    if(d)
    {
        while ((dir = readdir(d)) != NULL && flagArq)
        {                                   //percorre os arquivos do diretorio, lendo apenas os v�lidos
            if (dir->d_type == DT_REG)
            {
                if (nomeArquivo=="") {
                    nomeArquivoChar= dir->d_name;
                }else{
                    nomeArquivoChar = new char[nomeArquivo.size()+1];
                    copy(nomeArquivo.begin(), nomeArquivo.end(), nomeArquivoChar);
                    nomeArquivoChar[nomeArquivo.size()] = '\0';
                }
                cout << "Indexando grafo: " << nomeArquivo << endl;
                strcat(caminhoArquivo, nomeArquivoChar); //concatena o nome do arquivo � string para o caminho do arquivo, que at�
                                                     //ent�o tem somente o diret�rio
                cout << caminhoArquivo << endl;

                arqGrafo.open(caminhoArquivo, ifstream::binary); //tenta abrir o arquivo e verifica se ocorrreu qualquer
                                                                      //problema no processo
                if(!arqGrafo.is_open())
                {
                    cout << "Erro - leitura Grafo. ID: ";
                    arqGrafo.clear();
                    exit(1);
                }
                flagArq = false;

                //le o n�mero de n�s do grafo, converte para inteiro e guarda no objeto do grafo
                arqGrafo >> linha;
                stringstream convert(linha);
                convert>>num;
                g->setNumNos(num);

                while(!arqGrafo.eof())
                {

                    if(arqGrafo >> linha)
                    {
                        //le a informa��o do v�rtice de origem e converte para inteiro
                        stringstream convert1(linha);
                        convert1>>n1;
                    }

                    if(arqGrafo >> linha)
                    {
                         //le a informa��o do v�rtice de destino e converte para inteiro
                        stringstream convert2(linha);
                        convert2>>n2;
                    }


                     //cria a aresta entre os v�rtices (se n�o existirem, tamb�m os cria)
                    g->insereAresta(n1, 0, n2, 0, 0);
                }

                arqGrafo.close(); //fecha o arquivo
                arqGrafo.clear();
                strcpy(caminhoArquivo, caminhoDiretorio); //faz com que o caminho do arquivo volte a ser apenas o diretorio
            }
        }
        closedir(d); //fecha o diretorio
    }
}


/**
 * Executa o procedimento de recupera��o do arquivo de sa�da
 * passando o seu nome e o conte�do a ser escrito nele
 **/
void IO::saidaBusca(char* nomeArquivo, std::string saida)
{
    //passa o conte�do a ser escrito, o nome do arquivo e o caminho onde est�o os arquivos de sa�da
    geraSaidaBusca(saida, nomeArquivo, diretorioSaidas);
}

/**
 * Escreve o conte�do armazenado pela string 'saida' no arquivo
 * especificado por 'nomeArquivo', localizado o diret�rio 'caminhoSaida'.
 **/
void IO::geraSaidaBusca(string saida, char* nomeArquivo, char* caminhoSaida)
{
    string linha;
    ofstream arqSaida;
    char caminhoArquivoSaida[200];
    strcpy(caminhoArquivoSaida, caminhoSaida); //copia caminho da saida para o caminho do arquivo
    strcat(caminhoArquivoSaida, nomeArquivo);
    strcat(caminhoArquivoSaida, ".txt");

    arqSaida.open(caminhoArquivoSaida, ofstream::app); //tenta abrir o arquivo e verifica se ocorrreu qualquer
                                                                     //problema no processo
    if(!arqSaida.is_open())
    {
        cout << "Erro - saida" << endl;
        arqSaida.clear();
        exit(1);
    }

    //escreve o conteudo da string no arquivo
    arqSaida << saida << "\n";

    arqSaida.close();
    arqSaida.clear();
}

