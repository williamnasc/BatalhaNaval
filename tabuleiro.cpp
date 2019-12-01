#include "tabuleiro.h"

bool Tabuleiro::ler(istream &I){
    string s;

    I >> s;

    cout << s;
    if(s != "BATALHA_NAVAL") return false;


    return true;
}
