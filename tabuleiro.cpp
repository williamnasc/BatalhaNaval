#include "tabuleiro.h"

void Tabuleiro::initTab(){
    tab.resize(NLin*Ncol);

    for(int i=0;i<NLin;i++){
        for (int j=0;j<Ncol;j++) {
            tab[10*i+j] = EstadoPos::LIVRE;
        }
    }
}

bool Tabuleiro::addToTab(ptr_Navio nav){
    ///checar se o espaço é possivel e esta livre
    Pos ant = nav->getPos();
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
            cout << Pos(nav->getPos().lin+i , nav->getPos().col).imprimir() << endl;
            if(i!=0 && ant == Pos(nav->getPos().lin+i , nav->getPos().col)) return false;
            ant = Pos(nav->getPos().lin+i , nav->getPos().col);

        }


    }
    //se chegar aqui é pq todos as posições estão livres
    // add o navio ao Tab (altera o estado das posições)
    for (int i=0;i<nav->getSize();i++){
        if(nav->getDir() =='h'|| nav->getDir() =='H'){
            //marca com o respectivo navio
            tab[10*(nav->getPos().lin)+(nav->getPos().col+i)] = nav->getEstado();

            //bloqueia as leterais
            //bloqueia lateral de baixo
            if(Pos(nav->getPos().lin+1,nav->getPos().col+i).isValid()){
                if(isLivre(Pos(nav->getPos().lin+1,nav->getPos().col+i))){
                    tab[10*(nav->getPos().lin+1)+(nav->getPos().col+i)] = EstadoPos::BLOQUEADA;
                }
            }
            //bloqueia lateral de cima
            if(Pos(nav->getPos().lin-1,nav->getPos().col+i).isValid()){
                if(isLivre(Pos(nav->getPos().lin-1,nav->getPos().col+i))){
                    tab[10*(nav->getPos().lin-1)+(nav->getPos().col+i)] = EstadoPos::BLOQUEADA;
                }
            }
            if(i==0 || i == (nav->getSize()-1)){
                //bloqueia lateral da esquerda
                if(Pos(nav->getPos().lin,(nav->getPos().col+i)-1).isValid()){
                    if(isLivre(Pos(nav->getPos().lin,(nav->getPos().col+i)-1))){
                        tab[10*(nav->getPos().lin)+((nav->getPos().col+i)-1)] = EstadoPos::BLOQUEADA;
                    }
                }
                //bloqueia lateral da direita
                if(Pos(nav->getPos().lin,(nav->getPos().col+i)+1).isValid()){
                    if(isLivre(Pos(nav->getPos().lin,(nav->getPos().col+i)+1))){
                        tab[10*(nav->getPos().lin)+((nav->getPos().col+i)+1)] = EstadoPos::BLOQUEADA;
                    }
                }
            }


        }
        if(nav->getDir() =='v'|| nav->getDir() =='V'){
            //marca com o respectivo navio
            tab[10*(nav->getPos().lin+i)+(nav->getPos().col)] = nav->getEstado();

            //bloqueia as leterais

            //bloqueia lateral da esquerda
            if(Pos(nav->getPos().lin+i,nav->getPos().col-1).isValid()){
                if(isLivre(Pos(nav->getPos().lin+i,nav->getPos().col-1))){
                    tab[10*(nav->getPos().lin+i)+(nav->getPos().col-1)] = EstadoPos::BLOQUEADA;
                }
            }
            //bloqueia lateral da direita
            if(Pos(nav->getPos().lin+i,nav->getPos().col+1).isValid()){
                if(isLivre(Pos(nav->getPos().lin+i,nav->getPos().col+1))){
                    tab[10*(nav->getPos().lin+i)+(nav->getPos().col+1)] = EstadoPos::BLOQUEADA;
                }
            }
            if(i==0 || i == (nav->getSize()-1)){
                //bloqueia lateral de baixo
                if(Pos(nav->getPos().lin+i+1,nav->getPos().col).isValid()){
                    if(isLivre(Pos(nav->getPos().lin+i+1,nav->getPos().col))){
                        tab[10*(nav->getPos().lin+i+1)+(nav->getPos().col)] = EstadoPos::BLOQUEADA;
                    }
                }
                //bloqueia lateral de cima
                if(Pos(nav->getPos().lin+i-1,nav->getPos().col).isValid()){
                    if(isLivre(Pos(nav->getPos().lin+i-1,nav->getPos().col))){
                        tab[10*(nav->getPos().lin+i-1)+(nav->getPos().col)] = EstadoPos::BLOQUEADA;
                    }
                }
            }
        }

    }
    return true;
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

bool Tabuleiro::digitar(){
    Pos p;
    char li, co, tipo, direcao;
    for(unsigned i = 0; i <(NUM_MAX_P+NUM_MAX_C+NUM_MAX_D+NUM_MAX_S); i++){
        do{
        cout << "QUAL NAVIO? [P, C, D ou S]: ";
        cin >> tipo;
        }while(tipo != 'P' && tipo != 'p' && tipo != 'C' && tipo != 'c' && tipo != 'D' && tipo != 'd'
               && tipo != 'S' && tipo != 's');

        //Porta_Aviao
        if(tipo == 'P' || tipo == 'p'){
            cout << "Digite os " << NUM_MAX_P << " Porta_Avioes" << endl;
            for(unsigned i = 0; i < NUM_MAX_P; i++){
                do{
                    cout << "Linha [A-J] ou [a-j]: ";
                    cin >> li;
                }while(!(li >= 65 && li <= 74) && !(li >= 97 && li <= 106));

                do{
                    cout << "Coluna [1-0]: ";
                    cin >> co;
                }while(co < 48 || co > 57);

                do{
                    cout << "Direcao [V ou H] ou [v ou h]: ";
                    cin >> direcao;
                }while(direcao != 'V' && direcao != 'v' && direcao != 'H' && direcao != 'h');
                p = Pos(li, co);
                navios.push_back(new Porta_Avioes());
                navios.back()->setPos(p);
                navios.back()->setDir(direcao);
                //addToTab(navios.back()->clone());
                cout << endl << endl;
            }
        }

        //Cruzador
        if(tipo == 'C' || tipo == 'c'){
            cout << "Digite os " << NUM_MAX_C << " Cruzadores" << endl;
            for(unsigned i = 0; i < NUM_MAX_C; i++){
                do{
                    cout << "Linha [A-J] ou [a-j]: ";
                    cin >> li;
                }while(!(li >= 65 && li <= 74) && !(li >= 97 && li <= 106));

                do{
                    cout << "Coluna [1-0]: ";
                    cin >> co;
                }while(co < 48 || co > 57);

                do{
                    cout << "Direcao [V ou H] ou [v ou h]: ";
                    cin >> direcao;
                }while(direcao != 'V' && direcao != 'v' && direcao != 'H' && direcao != 'h');
                p = Pos(li, co);
                navios.push_back(new Cruzador());
                navios.back()->setPos(p);
                navios.back()->setDir(direcao);
                //addToTab(navios.back()->clone());
                cout << endl << endl;
            }
        }

        //Destroyer
        if(tipo == 'D' || tipo == 'd'){
            cout << "Digite os " << NUM_MAX_D << " Destroyers" << endl;
            for(unsigned i = 0; i < NUM_MAX_D; i++){
                do{
                    cout << "Linha [A-J] ou [a-j]: ";
                    cin >> li;
                }while(!(li >= 65 && li <= 74) && !(li >= 97 && li <= 106));

                do{
                    cout << "Coluna [1-0]: ";
                    cin >> co;
                }while(co < 48 || co > 57);

                do{
                    cout << "Direcao [V ou H] ou [v ou h]: ";
                    cin >> direcao;
                }while(direcao != 'V' && direcao != 'v' && direcao != 'H' && direcao != 'h');
                p = Pos(li, co);
                navios.push_back(new Destroyer());
                navios.back()->setPos(p);
                navios.back()->setDir(direcao);
                //addToTab(navios.back()->clone());
                cout << endl << endl;
            }
        }

        //Submarino
        if(tipo == 'S' || tipo == 's'){
            cout << "Digite os " << NUM_MAX_S << " Cruzadores" << endl;
            for(unsigned i = 0; i < NUM_MAX_S; i++){
                do{
                    cout << "Linha [A-J] ou [a-j]: ";
                    cin >> li;
                }while(!(li >= 65 && li <= 74) && !(li >= 97 && li <= 106));

                do{
                    cout << "Coluna [1-0]: ";
                    cin >> co;
                }while(co < 48 || co > 57);

                do{
                    cout << "Direcao [V ou H] ou [v ou h]: ";
                    cin >> direcao;
                }while(direcao != 'V' && direcao != 'v' && direcao != 'H' && direcao != 'h');
                p = Pos(li, co);
                navios.push_back(new Submarino());
                navios.back()->setPos(p);
                navios.back()->setDir(direcao);
                //addToTab(navios.back()->clone());
                cout << endl << endl;
            }
        }
    }

}

void Tabuleiro::initAuto(){
    srand(time(NULL));
    Pos p;
    char dir;
    bool c;
    initTab();

    for (int i=0;i<NUM_MAX_P;i++){
        navios.push_back(new Porta_Avioes());

        do{
            // posição aleatoria
            p.lin = int(rand() % 10);
            p.col = int (rand() % 10);

            if(!p.isValid())
                continue;
            //cout << "AQUI!";
            if(((p.lin*p.col)+p.lin+p.col)%2)
                dir = 'H';
            else
                dir = 'V';
            navios.back()->setPos(p);
            navios.back()->setDir(dir);
            c = !addToTab(navios.back()->clone());
            cout << c << endl;
        }while(c);
    }
    for (int i=0;i<NUM_MAX_C;i++){
        navios.push_back(new Cruzador());

        do{
            // posição aleatoria
            p.lin = int(rand() % 10);
            p.col = int (rand() % 10);

            if(!p.isValid())
                continue;
            //cout << "AQUI!";
            if(((p.lin*p.col)+p.lin+p.col)%2)
                dir = 'H';
            else
                dir = 'V';
            navios.back()->setPos(p);
            navios.back()->setDir(dir);
            c = !addToTab(navios.back()->clone());
            cout << c << endl;
        }while(c);
    }
    for (int i=0;i<NUM_MAX_D;i++){
        navios.push_back(new Destroyer());

        do{
            // posição aleatoria
            p.lin = int(rand() % 10);
            p.col = int (rand() % 10);

            if(!p.isValid())
                continue;
            //cout << "AQUI!";
            if(((p.lin*p.col)+p.lin+p.col)%2)
                dir = 'H';
            else
                dir = 'V';
            navios.back()->setPos(p);
            navios.back()->setDir(dir);
            c = !addToTab(navios.back()->clone());
            cout << c << endl;
        }while(c);
    }
    for (int i=0;i<NUM_MAX_S;i++){
        navios.push_back(new Submarino());

        do{
            // posição aleatoria
            p.lin = int(rand() % 10);
            p.col = int (rand() % 10);

            if(!p.isValid())
                continue;
            //cout << "AQUI!";
            if(((p.lin*p.col)+p.lin+p.col)%2)
                dir = 'H';
            else
                dir = 'V';
            navios.back()->setPos(p);
            navios.back()->setDir(dir);
            c = !addToTab(navios.back()->clone());
            cout << c << endl;
        }while(c);
    }
}
