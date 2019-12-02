#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <navio.h>

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

    vector<EstadoPos> mapa;
    int NLin;
    int Ncol;



public:
    ///CONSTRUTORES E DESTRUTORES
    inline Tabuleiro(){}
     ~Tabuleiro(){}

    ///METODOS
    bool isLivre(Pos); //checa se é possivel colocar um navio nessa posição
    bool ler(istream &I); //ler de arquivo
    bool digitar(istream &I); //ler do usuario
};

//inline ostream &operator<<(ostream &O, const Tabuleiro &X);


#endif // TABULEIRO_H
