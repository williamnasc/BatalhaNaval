#include "pos.h"

Pos::Pos(char l, char c){
    lin = l;
    col = c;
    if(!isValid(this)){
        cerr << " coordenadas invalidas ";
        lin = ' ';
        col = ' ';
    }

}

bool Pos::isValid(Pos p){
    if(
            isLinValid(p.lin) &&
            isColValid(p.col)
       )
        return false;
    return true;
}
bool Pos::isLinValid(char c){
    if((c<'A' || c>'J'))
        return false;
    return true;
}
bool Pos::isColValid(char c){
    if((c<'0' || c>'9'))
        return false;
    return true;
}

Pos Pos::nextVertical(const Pos p){
    char c = p.col;
    if(isColValid(c++))
        return Pos(p.lin,c++);
    return p;
}
Pos Pos::nextHorizontal(const Pos p){
    char c = p.lin;
    if(isLinValid(c++))
        return Pos(lin++,col);
    return p;
}

void Pos::operator=(const Pos p){
    lin = p.lin;
    col = p.col;
}
bool Pos::operator==(const Pos p){
    if((lin == p.lin)&&(col == p.col))
        return true;
    else {

    }
}

