#include <bits/stdc++.h>
#include "pos.h"

Pos::Pos(string &s){
    if(s.length() == 2){
        unsigned n = s.length();
        char c[n+1];
        strcpy(c, s.c_str());
        if((c[0] >= 65 && c[0] <= 74) && (c[1] >= 48 && c[1] <= 57)){
            for(int i = 0; i < 10; i++){
                if(c[0] == 65+i){
                    lin = i;
                    break;
                }
            }
            for(int i = 0; i < 10; i++){
                if(c[1] == 48+i){
                    if(c[1]==48){
                        col = 9;
                        break;
                    }
                    col = i-1;
                    break;
                }
            }
        }
        else if((c[0] >= 97 && c[0] <= 106) && (c[1] >= 48 && c[1] <= 57)){
            for(int i = 0; i < 10; i++){
                if(c[0] == 97+i){
                    lin = i;
                    break;
                }
            }
            for(int i = 0; i < 10; i++){
                if(c[1] == 48+i){
                    if(c[1]==48){
                        col = 9;
                        break;
                    }
                    col = i-1;
                    break;
                }
            }
        }
    }
}

Pos::Pos(char l, char c){
    lin =-1;
    col =-1;
    if(l >= 'A' && l <='J')
        lin = l-65;
    if(l >= 'a' && l <='j')
        lin = l-97;
    if(c == '0') col = 9;
    if(c >= '1' && c <= '9')
        col = c-49;
}

bool Pos::isValid(){
    if(
            isLinValid() &&
            isColValid()
       )
        return true;
    return false;
}

bool Pos::isLinValid(){
    if((lin<0 || lin>9))
        return false;
    return true;
}

bool Pos::isColValid(){
    if((col<0 || col>9))
        return false;
    return true;
}

Pos Pos::nextVerticalCima(){
    Pos p1(lin--, col);
    if(p1.isValid()) return p1;
    else {
        Pos p2(lin, col);
        return p2;
    }
}

Pos Pos::nextVerticalBaixo(){
    Pos p1(lin++, col);
    if(p1.isValid()) return p1;
    else {
        Pos p2(lin, col);
        return p2;
    }
}

Pos Pos::nextHorizontalDireita(){
    Pos p1(lin, col++);
    if(p1.isValid()) return p1;
    else {
        Pos p2(lin, col);
        return p2;
    }
}

Pos Pos::nextHorizontalEsquerda(){
    Pos p1(lin, col--);
    if(p1.isValid()) return p1;
    else {
        Pos p2(lin, col);
        return p2;
    }
}

Pos Pos::digitarPos(){
    char l, c;
    bool l_valido = false;
    bool c_valido = false;
    do{
        cout << "Digite a linha[A-B ou a-b]: ";
        cin >> l;
        if((l >= 65 && l <= 74) || (l >= 97 && l <= 106)){
            l_valido = true;
        }
    }while(l_valido != true);

    do{
        cout << "Digite a coluna[1-0]: ";
        cin >> c;
        if(c >= 48 && c <= 57){
            c_valido = true;
        }
    }while(c_valido != true);

    Pos novo(l, c);
    return novo;
}


void Pos::operator=(const Pos& p){
    lin = p.lin;
    col = p.col;
}

bool Pos::operator==(const Pos& p){
    if((lin == p.lin)&&(col == p.col))
        return true;
    else {
        return false;
    }
}

string Pos::imprimir(){
    string s;
    s += char(lin+65);
    if(col == 9) s += char(48);
    else s += char(col+49);
    return s;
}

