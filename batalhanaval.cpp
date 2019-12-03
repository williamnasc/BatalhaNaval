#include "batalhanaval.h"

BatalhaNaval::BatalhaNaval(string m):modo(m){

    // Inicializa a biblioteca de sockets (exigida no Windows)
    iResult = mysocket::init();
    if (iResult != mysocket_status::SOCK_OK) {
      cerr << "Biblioteca mysocket nao pode ser inicializada\n";
      exit(1);
    }

    if(modo == "servidor"){
        cout << "SERVIDOR INICIADO!";
    }
    if(modo == "cliente"){
        cout << "CLIENTE INICIADO!";
    }
    if(modo != "servidor" && modo == "cliente" )
        cerr << "MODO INVALIDO!";
}

BatalhaNaval::~BatalhaNaval(){

    // Desliga os sockets
    cout << "Encerrando o socket de conexoes\n";
    c.close();
    cout << "Encerrando o socket de comunicacao\n";
    s.close();

    /// Encerramento da biblioteca de sockets
    mysocket::end();
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

bool BatalhaNaval::Conect(){}
