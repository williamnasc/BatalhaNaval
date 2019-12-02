#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "navio.h"

/// Os possiveis estados de uma posição do mapa
enum class EstadoPos
{
  LIVRE,
  BLOQUEADA,
  ATINGIDA,
  PORTA_AVIAO,
  CRUZADOR,
  DESTROYER,
  SUBMARINO
};


typedef Navio* ptr_Navio;

class Tabuleiro
{
private:
    list<ptr_Navio> navios;
    vector<EstadoPos> tab;
    int NLin = 10;
    int Ncol = 10;

public:
    ///CONSTRUTORES E DESTRUTORES
    inline Tabuleiro(){}
    ~Tabuleiro(){}

    ///METODOS
    void initTab();             //inicia o tabuleiro com todas as posições livres
    void attTab();              //atualiza o tabuleiro depois de adicionados os respectivos navios

    bool isLivre(Pos p);        //checa se é possivel colocar um navio nessa posição
    bool ler(istream &I);       //ler de arquivo
    bool digitar();   //ler do usuario


};

//inline ostream &operator<<(ostream &O, const Tabuleiro &X);


#endif // TABULEIRO_H
