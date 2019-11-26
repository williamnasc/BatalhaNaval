#ifndef NAVIO_H
#define NAVIO_H

#include <pos.h>
#include <list>
#include <algorithm>


class Navio
{
protected:
    vector<Pos> posicoes;
public:
    Navio();

    virtual void ler(istream &I);
    virtual bool isDestruido();
};

#endif // NAVIO_H
