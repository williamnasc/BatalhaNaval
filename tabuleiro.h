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

    int NLin = 10;
    int Ncol = 10;
public:
    vector<EstadoPos> tab;
    vector<Pos> tirosEmitidos;
    vector<Pos> tirosRecebidos;

    ///CONSTRUTORES E DESTRUTORES
    inline Tabuleiro(){}
    ~Tabuleiro(){}

    ///METODOS
    void initTab();             //inicia o tabuleiro com todas as posições livres
    bool addToTab(ptr_Navio nav);  //atualiza o tabuleiro depois de adicionados os respectivos navios

    bool isLivre(Pos p);        //checa se é possivel colocar um navio nessa posição
    bool ler(istream &I);       //ler de arquivo
    bool digitar();             //ler do usuario

    friend class BatalhaNaval;

};

inline ostream &operator<<(ostream &O, const Tabuleiro &X){
    char c1 = '@';
    cout << "  ";
    for(unsigned i = 1; i < 10; i++) O << ' ' << i;
    O << ' ' << 0 << endl << endl;
    for(unsigned i = 0; i < 10; i++){
            c1 = c1+1;
        O << char(c1) << "  ";
        for(unsigned j = 0; j < 10; j++){
            if(X.tab[(10*i+j)] == EstadoPos::LIVRE) cout << '-';
            if(X.tab[(10*i+j)] == EstadoPos::BLOQUEADA) cout << 'X';
            if(X.tab[(10*i+j)] == EstadoPos::ATINGIDA) cout << '*';
            if(X.tab[(10*i+j)] == EstadoPos::PORTA_AVIAO) cout << 'P';
            if(X.tab[(10*i+j)] == EstadoPos::CRUZADOR) cout << 'C';
            if(X.tab[(10*i+j)] == EstadoPos::DESTROYER) cout << 'D';
            if(X.tab[(10*i+j)] == EstadoPos::SUBMARINO) cout << 'S';
            //O << '-';
            O << ' ';
        }
        O << endl;
    }
    return O;
}


#endif // TABULEIRO_H
