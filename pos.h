#ifndef POS_H
#define POS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Pos
{
public:

    int lin; //0 a 9
    int col; //0 a 9

    ///CONSTRUTORES
    inline Pos():lin(-1),col(-1){}
    inline Pos(const Pos& p):lin(p.lin),col(p.col){;}
    inline Pos(int l, int c){
        if((l >= 0 && l <= 9) && (l >= 0 && l <= 9)){
            lin = l;
            col = c;
        }
    }
    Pos(string &s);
    Pos(char l, char c);

    bool isLinValid();
    bool isColValid();
    bool isValid();
    Pos nextVerticalCima();
    Pos nextVerticalBaixo();
    Pos nextHorizontalDireita();
    Pos nextHorizontalEsquerda();

    void operator=(const Pos& p);
    bool operator==(const Pos& p);
};

#endif // POS_H
