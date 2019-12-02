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
                    col = i;
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
                    col = i;
                    break;
                }
            }
        }
    }
}

Pos::Pos(char l, char c){
    if((l >= 65 && l <= 74) && (c >= 48 && c <= 57)){
        for(int i = 0; i < 10; i++){
                if(l == 65+i){
                    lin = i;
                    break;
                }
            }
        for(int i = 0; i < 10; i++){
            if(c == 48+i){
                col = i;
                break;
            }
        }
    }
    else if((l >= 97 && l <= 106) && (c >= 48 && c <= 57)){
            for(int i = 0; i < 10; i++){
                if(l == 97+i){
                    lin = i;
                    break;
                }
            }
            for(int i = 0; i < 10; i++){
                if(c == 48+i){
                    col = i;
                    break;
                }
            }
        }
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
    cout << "Digite a linha[A-B ou a-b]: ";
    cin >> l;
    cout << "Digite a coluna[0-9]: ";
    cin >> c;
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



