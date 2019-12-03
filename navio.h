#ifndef NAVIO_H
#define NAVIO_H

#include <pos.h>
#include <list>
#include <vector>
#include <algorithm>

#define NUM_MAX_P 2
#define NUM_MAX_C 2
#define NUM_MAX_D 2
#define NUM_MAX_S 2

class Navio;
typedef Navio* ptr_Navio;

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
    inline Navio(const Pos &pos, char direcao){
        bool igual = p==pos;
        if(igual == false) p=pos;
        if(direcao=='v' || direcao=='V' || direcao=='h' || direcao=='H') dir = direcao;
        else  dir = '0';
    }

    virtual inline ~Navio(){}
    virtual ptr_Navio clone() const = 0;

    virtual inline void setPos(Pos pos){p = pos;}
    virtual inline void setDir(char d){dir = d;}
    virtual int getSize() const = 0;
    virtual inline char getDir(){return dir;}
    virtual inline Pos getPos(){return p;}
    virtual EstadoPos getEstado() = 0;
    //virtual void ler(istream &I)=0;
    //virtual bool isDestruido()=0;

    friend class BatalhaNaval;
};

class Porta_Avioes: public Navio
{
public:
    inline ~Porta_Avioes(){}
    inline Porta_Avioes(): Navio(){}
    inline Porta_Avioes(char direcao):Navio(direcao){}
    inline Porta_Avioes(unsigned tiros):Navio(tiros){}
    inline Porta_Avioes(const Pos &ponto, char direcao):Navio(ponto,direcao){}

    inline ptr_Navio clone() const {return new Porta_Avioes(*this);}
    virtual inline EstadoPos getEstado(){return EstadoPos::PORTA_AVIAO;}
    inline int getSize() const {return 5;}
    inline bool isDestruido() {if(tiros_levados == 5) return true; else return false;}
};

class Cruzador: public Navio
{
public:
    inline ~Cruzador(){}
    inline Cruzador(): Navio(){}
    inline Cruzador(char direcao):Navio(direcao){}
    inline Cruzador(unsigned tiros):Navio(tiros){}
    inline Cruzador(const Pos &ponto, char direcao):Navio(ponto,direcao){}

    inline ptr_Navio clone() const {return new Cruzador(*this);}
    virtual inline EstadoPos getEstado(){return EstadoPos::CRUZADOR;}
    inline int getSize() const {return 4;}
    inline bool isDestruido() {if(tiros_levados == 4) return true; else return false;}
};

class Destroyer: public Navio
{
public:
    inline ~Destroyer(){}
    inline Destroyer(): Navio(){}
    inline Destroyer(char direcao):Navio(direcao){}
    inline Destroyer(unsigned tiros):Navio(tiros){}
    inline Destroyer(const Pos &ponto, char direcao):Navio(ponto,direcao){}

    inline ptr_Navio clone() const {return new Destroyer(*this);}
    virtual inline EstadoPos getEstado(){return EstadoPos::DESTROYER;}
    inline int getSize() const {return 3;}
    inline bool isDestruido() {if(tiros_levados == 3) return true; else return false;}
};

class Submarino: public Navio
{
public:
    inline ~Submarino(){}
    inline Submarino(): Navio(){}
    inline Submarino(char direcao):Navio(direcao){}
    inline Submarino(unsigned tiros):Navio(tiros){}
    inline Submarino(const Pos &ponto, char direcao):Navio(ponto,direcao){}

    inline ptr_Navio clone() const {return new Submarino(*this);}
    virtual inline EstadoPos getEstado(){return EstadoPos::SUBMARINO;}
    inline int getSize() const {return 2;}
    inline bool isDestruido() {if(tiros_levados == 2) return true; else return false;}
};


#endif // NAVIO_H
