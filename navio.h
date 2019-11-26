#ifndef NAVIO_H
#define NAVIO_H

#include <pos.h>
#include <list>
#include <algorithm>

#define NUM_MAX_P 2
#define NUM_MAX_C 2
#define NUM_MAX_D 2
#define NUM_MAX_S 2

class Navio
{
protected:
    vector<Pos> posicoes;
public:
    Navio();
    inline Navio(int i){posicoes.resize(i);}
    virtual ~Navio();
    inline int getSize() const {return posicoes.size();}
    bool posicionar(Pos p, char c);
    virtual void ler(istream &I)=0;
    virtual bool isDestruido()=0;
    //fazer a sobrecarga do I e O stream como virtual

};

class PortaAvioes: Navio{
    inline PortaAvioes():Navio(5){}
    PortaAvioes(Pos p, char dir);
};
class Cruzador: Navio{
    inline Cruzador():Navio(4){}
    Cruzador(Pos p, char dir);
};
class Destroyer: Navio{
    inline Destroyer():Navio(3){}
    Destroyer(Pos p, char dir);
};
class Submarino: Navio{
    inline Submarino():Navio(2){}
    Submarino(Pos p, char dir);
};

#endif // NAVIO_H
