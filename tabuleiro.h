#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <navio.h>

class Tabuleiro
{
private:
    list<Navio> navios;
    list<Pos> locMarcados;
public:
    ///CONSTRUTORES E DESTRUTORES
    inline Tabuleiro();
    ~Tabuleiro();

    ///METODOS
    bool isLivre(Pos); //checa se é possivel colocar um navio nessa posição
    bool ler(istream &I); //ler de arquivo
    bool digitar(istream &I); //ler do usuario
};

inline ostream &operator<<(ostream &O, const Tabuleiro &X);


#endif // TABULEIRO_H
