#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "navio.h"
#include "pos.h"

typedef Navio* ptr_Navio;

class Tabuleiro
{
private:
    list<ptr_Navio> navios;
    list<ptr_Navio>::iterator iterador;
    vector<EstadoPos> tab;
    int NLin = 10;
    int Ncol = 10;

public:
    ///CONSTRUTORES E DESTRUTORES
    inline Tabuleiro(){}
    ~Tabuleiro(){}

    ///METODOS
    void initTab();             //inicia o tabuleiro com todas as posições livres
    bool addToTab(Navio &Nav);  //atualiza o tabuleiro depois de adicionados os respectivos navios

    bool isLivre(Pos p);        //checa se é possivel colocar um navio nessa posição
    bool ler(istream &I);       //ler de arquivo
    bool digitar();             //ler do usuario


};

inline ostream &operator<<(ostream &O, const Tabuleiro &X){
    char c1 = '@';
    cout << "  ";
    for(unsigned i = 1; i < 10; i++) O << ' ' << i;
    O << ' ' << 0 << endl;
    O << endl;
    for(unsigned i = 0; i < 10; i++){
            c1 = c1+1;
        O << char(c1) << "  ";
        for(unsigned j = 0; j < 10; j++){
            O << '_' << ' ';
        }
        O << endl;
    }
    return O;
}


#endif // TABULEIRO_H
