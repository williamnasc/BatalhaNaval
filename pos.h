#ifndef POS_H
#define POS_H

#include <iostream>

using namespace std;

class Pos
{
public:

    char lin; //A a J
    char col; //0 a 1

    ///CONSTRUTORES
    inline Pos():lin(' '),col(' '){}
    inline Pos(const Pos& p):lin(p.lin),col(p.col){}
    Pos(char l, char c);
    //falta o por string

    bool isLinValid(char c);
    bool isColValid(char c);
    bool isValid(const Pos p);
    Pos nextVertical(const Pos p); //se n for valido ele retorna o mesmo valor
    Pos nextHorizontal(const Pos p); //se n for valido ele retorna o mesmo valor

    void operator=(const Pos p);
    bool operator==(const Pos p); //deve ser ajustado para que 'A' seja igual a 'a' por exemplo
};

#endif // POS_H
