#include "batalhanaval.h"


BatalhaNaval::~BatalhaNaval(){
    meusPontos = 0;
    pontosInimigo = 0;
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

bool BatalhaNaval::verificaDestruido(char& tipo){
    for (meuTabuleiro.iterador = meuTabuleiro.navios.begin();
         meuTabuleiro.iterador != meuTabuleiro.navios.end();
         meuTabuleiro.iterador++){

        //verifica se foi destrudio
        if((*meuTabuleiro.iterador)->isDestruido()){
            //add pontuação
            pontosInimigo += (*meuTabuleiro.iterador)->getSize();
            //add a tipo o tipo do navio q era
            tipo = (*meuTabuleiro.iterador)->getTipo();
            //deleta navio da lista
            meuTabuleiro.navios.erase(meuTabuleiro.iterador);
            return true;
        }
    }
    return false;
}

void BatalhaNaval::addDestruidoToTab(char tipoNav, Pos pos){
    ptr_Navio navio;
/*
    if(tipoNav == 'P' || tipoNav == 'p') navio = new Porta_Avioes();
    if(tipoNav == 'C' || tipoNav == 'c') navio = new Cruzador();
    if(tipoNav == 'D' || tipoNav == 'd') navio = new Destroyer();
    if(tipoNav == 'S' || tipoNav == 's') navio = new Submarino();

    ///desobrir direção
    int tamanho = meuTabuleiro.acertos.size();

    pos.lin = meuTabuleiro.acertos[tamanho-1].lin - meuTabuleiro.acertos[tamanho-2].lin;
    pos.lin = meuTabuleiro.acertos[tamanho-1].lin - meuTabuleiro.acertos[tamanho-2].lin;

    for (int i=0; i<navio->getSize();i++) {

    }
*/
    delete navio;
}

bool BatalhaNaval::isValid(Pos p){

    if(!p.isValid()) return false;

    if(!tabInimigo.isLivre(p)) return false;

    return true;
}

void BatalhaNaval::addPonto(char navio){

    if(navio == 'P' || navio == 'p'){
        meusPontos += Porta_Avioes().getSize();
    }if(navio == 'C' || navio == 'c'){
        meusPontos += Cruzador().getSize();
    }if(navio == 'D' || navio == 'd'){
        meusPontos += Destroyer().getSize();
    }if(navio == 'S' || navio == 's'){
        meusPontos += Submarino().getSize();
    }
    return;
}
