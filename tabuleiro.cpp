#include "tabuleiro.h"

void Tabuleiro::initTab(){
    tab.resize(NLin*Ncol);

    for(int i=0;i<NLin;i++){
        for (int j=0;j<Ncol;j++) {
            tab[10*i+j] = EstadoPos::LIVRE;
        }
    }
}

//falta bloquear as casas laterais como nas especificações
bool Tabuleiro::addToTab(ptr_Navio nav){
    ///checar se o espaço é possivel e esta livre
    for (int i=0;i<nav->getSize();i++){
        if(nav->getDir() =='h'|| nav->getDir() =='H'){
            //checa se a posição é valida
            if(!Pos(nav->getPos().lin , nav->getPos().col+i).isValid())
                return false;
            //checa se a posição está livre
            if(!isLivre(Pos(nav->getPos().lin , nav->getPos().col+i)))
                return false;
        }
        if(nav->getDir() =='v'|| nav->getDir() =='V'){
            //checa se a posição é valida
            if(!Pos(nav->getPos().lin+i , nav->getPos().col).isValid())
                return false;
            //checa se a posição está livre
            if(!isLivre(Pos(nav->getPos().lin+i , nav->getPos().col)))
                return false;
        }
    }
    //se chegar aqui é pq todos as posições estão livres
    // add o navio ao Tab (altera o estado das posições)
    for (int i=0;i<nav->getSize();i++){
        if(nav->getDir() =='h'|| nav->getDir() =='H'){
            //marca com o respectivo navio
            tab[10*(nav->getPos().lin)+(nav->getPos().col+i)] = nav->getEstado();

            //bloqueia as leterais
            //...

        }
        if(nav->getDir() =='v'|| nav->getDir() =='V'){
            //marca com o respectivo navio
            tab[10*(nav->getPos().lin+i)+(nav->getPos().col)] = nav->getEstado();

            //bloqueia as leterais
            //...
        }

    }
}

bool Tabuleiro::isLivre(Pos p){
    if(tab[10*p.lin+p.col] == EstadoPos::LIVRE)
        return true;
    else
        return false;
}


//falta tratar os erros e especificações do projeto
//bug se o numero de navios do navio diferente do numero maximo de navios
bool Tabuleiro::ler(istream &I){
    string s;
    Pos p;
    char c,lin,col,tipo,dir;
    int Num_P = 0, Num_C = 0, Num_D = 0, Num_S = 0;

    I >> s;
    //cout << s;
    if(s != "BATALHA_NAVAL") return false;


    for (int i=0;i<(NUM_MAX_P+NUM_MAX_C+NUM_MAX_D+NUM_MAX_S);i++){
        I >> tipo;
        I >> dir;
        I >> lin >> col;
        //cout << "AQUI!!!!";
        p = Pos(lin,col);
        if(!p.isValid()) return false;
        if(!(dir == 'H' || dir == 'h' || dir == 'V' || dir == 'v')) return false;

        //add navio a lista de navios
        if(tipo == 'P' || tipo == 'p')
            navios.push_back(new Porta_Avioes());
        if(tipo == 'C' || tipo == 'c')
            navios.push_back(new Cruzador());
        if(tipo == 'D' || tipo == 'd')
            navios.push_back(new Destroyer());
        if(tipo == 'S' || tipo == 's')
            navios.push_back(new Submarino());

        /// add os dados e add ao tabuleiro
        //cout << tipo <<' '<< dir << " : ";
        //cout << lin <<' '<< col << endl;

        navios.back()->setPos(p);
        navios.back()->setDir(dir);
        addToTab(navios.back()->clone());
    }
    //cout << navios.size() << endl;
    /*for (iterador = navios.begin();iterador != navios.end();iterador++) {
        cout <<"Pos( "<< (*iterador)->getPos().lin << " , " << (*iterador)->getPos().col << " )" <<endl;
        cout <<"dir: " <<  (*iterador)->getDir() << endl;
    }*/
    return true;
}

bool Tabuleiro::digitar(){}
