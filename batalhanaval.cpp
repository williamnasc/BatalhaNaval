#include "batalhanaval.h"


BatalhaNaval::~BatalhaNaval(){
}


void BatalhaNaval::initTabuleiros(){
    meuTabuleiro.initTab();
    tabInimigo.initTab();
    string s;
    ifstream a;
    cout << "digite o nome do arquivo de leitura:";
    cin >> s;
    a.open(s);
    if (!a.is_open())
    {
      cout << "arq n aberto";
    }
    if(meuTabuleiro.ler(a))
        cout << "\ndeu bom\n";
        else {
        cout << "\ndeu ruim\n";
    }


}

