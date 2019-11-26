#ifndef NAVIO_H
#define NAVIO_H

#include <pos.h>
#include <list>
#include <algorithm>

#define N_MAX_SUB 2

class Navio
{
protected:
    vector<Pos> posicoes;
public:
    Navio(int t);
    virtual ~Navio();
    inline int getSize() const {return posicoes.size();}
    virtual void ler(istream &I)=0;
    virtual bool isDestruido()=0;

};

class PortaAvioes: Navio{

};

#endif // NAVIO_H
