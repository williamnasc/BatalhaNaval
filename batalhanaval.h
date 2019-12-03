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

public:
    Tabuleiro meuTabuleiro;
    Tabuleiro tabInimigo;

    ///CONSTRUTORES
    inline BatalhaNaval(){}
    ~BatalhaNaval();

    ///METODOS
    void initTabuleiros();    //ler e inicia os tabuleiros

    inline void imprimirTabs(){ cout << "MEU TABULEIRO:\n "<< meuTabuleiro << endl  << "TABULEIRO INIMIGO:\n " << tabInimigo;}

    bool Conect();          //inicia a conexão a depender do modo


};

#endif // BATALHANAVAL_H
