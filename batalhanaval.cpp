#include "batalhanaval.h"


BatalhaNaval::~BatalhaNaval(){
}


void BatalhaNaval::initTabuleiros(){
    meuTabuleiro.initTab();
    tabInimigo.initTab();
    string s;
    ifstream a;
    cout << "digite o nome do arquivo de leitura:";
    //cin >> s;
    a.open("bn");
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

bool BatalhaNaval::verificaAcerto(Pos pos){
    char dir;
    int i=0;
    for (meuTabuleiro.iterador = meuTabuleiro.navios.begin();
         meuTabuleiro.iterador != meuTabuleiro.navios.end();
         meuTabuleiro.iterador++){
        ///pega direção do navio
        dir = (*meuTabuleiro.iterador)->getDir();
        for(int i=0;i<(*meuTabuleiro.iterador)->getSize();i++){
            if(dir =='h'|| dir =='H'){
                //checa se a posição da função é igual a alguma posição que o navio ocupa
                if(Pos((*meuTabuleiro.iterador)->getPos().lin , (*meuTabuleiro.iterador)->getPos().col+i) == pos){
                    (*meuTabuleiro.iterador)->tiros_levados += 1;
                    return true;
                }

            }
            if(dir =='v'|| dir =='V'){
                //checa se a posição da função é igual a alguma posição que o navio ocupa
                if(Pos((*meuTabuleiro.iterador)->getPos().lin+i , (*meuTabuleiro.iterador)->getPos().col) == pos){
                    (*meuTabuleiro.iterador)->tiros_levados += 1;
                    return true;
                }
            }
        }
    }
    return false;
}

