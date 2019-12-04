#ifndef BATALHANAVAL_H
#define BATALHANAVAL_H

#include <tabuleiro.h>
#include <mysocket.h>
#include <iostream>
#include <string.h>

#define PORTA_TESTE "23456"

class BatalhaNaval
{
private:
    int meusPontos;
    int pontosInimigo;
public:
    Tabuleiro meuTabuleiro;
    Tabuleiro tabInimigo;

    ///CONSTRUTORES
    inline BatalhaNaval(){}
    ~BatalhaNaval();

    ///METODOS
    void initTabuleiros();    //ler e inicia os tabuleiros
    inline void imprimirTabs(){
        cout << "MEU TABULEIRO:\n "<< meuTabuleiro << endl
             << "TABULEIRO INIMIGO:\n " << tabInimigo;
    }
    inline int getMeusPontos(){return meusPontos;}
    inline int getPontosInimigo(){return pontosInimigo;}

    bool verificaAcerto(Pos pos);
    //verifica se alguem foi destruido, atualiza o tab e exclui o navio de navios, tipo vira char de tipo do navio
    bool verificaDestruido(char& tipo);
    bool verificaFim();
    void addDestruidoToTab(char tipoNav, Pos pos);
    bool isValid(Pos p);
    void addPonto(char navio);
};

#endif // BATALHANAVAL_H
