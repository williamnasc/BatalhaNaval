#ifndef NAVIO_H
#define NAVIO_H

#include <pos.h>
#include <list>
#include <vector>
#include <algorithm>


class Navio
{
protected:
    Pos p;
    char dir;
    unsigned tiros_levados;
public:
    inline Navio(): p(), dir(' '),tiros_levados(0){;}
    inline Navio(const Pos &ponto){
        bool igual = p==ponto;
        if(igual == false) p=ponto;
    }
    inline Navio(char direcao){
        if(direcao=='v' || direcao=='V' || direcao=='h' || direcao=='H') dir = direcao;
    }
    inline Navio(unsigned tiros){
        if(tiros >= 0) tiros_levados = tiros;
    }
    inline Navio(const Ponto &ponto, char direcao){
        bool igual = p==ponto;
        if(igual == false) p=ponto;
        if(direcao=='v' || direcao=='V' || direcao=='h' || direcao=='H') dir = direcao;
    }
    virtual int getSize() const = 0;
    virtual ~Navio();
    virtual void ler(istream &I)=0;
    virtual bool isDestruido()=0;
};

#endif // NAVIO_H
