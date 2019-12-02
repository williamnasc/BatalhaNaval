#include "tabuleiro.h"

void Tabuleiro::initTab(){
    tab.resize(NLin*Ncol);

    for (int i=0;i<NLin*Ncol;i++){
        tab[i] = EstadoPos::LIVRE;
    }
}

bool Tabuleiro::isLivre(Pos p){
    if(tab[10*p.lin+p.col] == EstadoPos::LIVRE)
        return true;
    else
        return false;
}


//apenas adiciona no conteiner,
//falta tratar os erros e especificações do projeto
//falta alterar o tabuleiro ao add navios
bool Tabuleiro::ler(istream &I){
    string s;
    Pos p;
    char lin,col,tipo,dir;
    int Num_P = 0, Num_C = 0, Num_D = 0, Num_S = 0;

    I >> s;
    //cout << s;
    if(s != "BATALHA_NAVAL") return false;

    for (int i=0;i<(NUM_MAX_P+NUM_MAX_C+NUM_MAX_D+NUM_MAX_S);i++) {

        I >> tipo;
        I >> dir;
        cout << tipo << dir<< endl;

        //se dir for valida
        if(!(dir == 'H' || dir == 'h' || dir == 'V' ||dir == 'v')) return false;

        //se pos for valida
        I >> lin;
        I >> col;

        p = Pos(lin,col);

        if(!p.isValid()) return false;

        if(tipo == 'P' || tipo == 'p'){
            navios.push_back(new Porta_Avioes(p,dir));
            Num_P ++;
            continue;
        }
        if(tipo == 'C' || tipo == 'c'){
            navios.push_back(new Cruzador(p,dir));
            Num_C ++;
            continue;
        }
        if(tipo == 'D' || tipo == 'd'){
            navios.push_back(new Destroyer(p,dir));
            Num_D ++;
            continue;
        }
        if(tipo == 'S' || tipo == 's'){
            navios.push_back(new Submarino(p,dir));
            Num_S ++;
            continue;
        }
        //organizar esse final
        cout << "SE CHEGOU AQUI O TIPO É INVALIDO!" << endl;
        return false;
    }
    return true;
}

//falta perceber se ele é grande demais pra ser colocado naquela posição
//falta alterar o tabuleiro ao add navios
bool Tabuleiro::digitar(){
    Pos p;
    char dir;
    for (int i=0;i<NUM_MAX_P;i++){
        do{
            cout << "Add a Posição do Porta Aviões"<< endl;
            //p = digitarPos();
            cout << "Add a direção do Porta Aviões"<< endl;
            cin >> dir;
            if(!(dir == 'H' || dir == 'h' || dir == 'V' ||dir == 'v')){
                cout << "Direcao invalida";
                continue;
            }
            if(isLivre(p)){
                navios.push_back(new Porta_Avioes(p,dir));
            }else
                cout << "não é possivel add nessa posição" << endl;
        }while(isLivre(p));
    }
    for (int i=0;i<NUM_MAX_C;i++){
        do{
            cout << "Add a Posição do Cruzador"<< endl;
            //p = digitarPos();
            cout << "Add a direção do Cruzador"<< endl;
            cin >> dir;
            if(!(dir == 'H' || dir == 'h' || dir == 'V' ||dir == 'v')){
                cout << "Direcao invalida";
                continue;
            }
            if(isLivre(p)){
                navios.push_back(new Cruzador(p,dir));
            }else
                cout << "não é possivel add nessa posição" << endl;
        }while(isLivre(p));
    }
    for (int i=0;i<NUM_MAX_D;i++){
        do{
            cout << "Add a Posição do Destroyer"<< endl;
            //p = digitarPos();
            cout << "Add a direção do Destroyer"<< endl;
            cin >> dir;
            if(!(dir == 'H' || dir == 'h' || dir == 'V' ||dir == 'v')){
                cout << "Direcao invalida";
                continue;
            }
            if(isLivre(p)){
                navios.push_back(new Destroyer(p,dir));
            }else
                cout << "não é possivel add nessa posição" << endl;
        }while(isLivre(p));
    }
    for (int i=0;i<NUM_MAX_S;i++){
        do{
            cout << "Add a Posição do Submarino"<< endl;
            //p = digitarPos();
            cout << "Add a direção do Submarino"<< endl;
            cin >> dir;
            if(!(dir == 'H' || dir == 'h' || dir == 'V' ||dir == 'v')){
                cout << "Direcao invalida";
                continue;
            }
            if(isLivre(p)){
                navios.push_back(new Cruzador(p,dir));
            }else
                cout << "não é possivel add nessa posição" << endl;
        }while(isLivre(p));
    }
}
