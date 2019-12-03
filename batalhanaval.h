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
    Tabuleiro meuTabuleiro;
    Tabuleiro tabInimigo;
    string modo;                //indica se está no modo cliente ou servido

    ///variaveis de uso da conexão
    mysocket_status iResult;
    tcp_mysocket_server c;
    tcp_mysocket s;

public:
    ///CONSTRUTORES
    inline BatalhaNaval(){}
    BatalhaNaval(string m);//"cliente" ou "servidor"     //inicia ele com cliente ou servidor
    ~BatalhaNaval();

    ///METODOS
    void initTabuleiros();    //ler e inicia os tabuleiros

    inline void imprimirTabs(){ cout << "MEU TABULEIRO:\n "<< meuTabuleiro << endl  << "TABULEIRO INIMIGO:\n " << tabInimigo;}

    bool Conect();          //inicia a conexão a depender do modo


};

#endif // BATALHANAVAL_H
