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
    virtual ~Navio();
    inline int getSize() const {return posicoes.size();}
    virtual void ler(istream &I);
    virtual bool isDestruido();

};

#endif // NAVIO_H
