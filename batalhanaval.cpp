#include "batalhanaval.h"

BatalhaNaval::BatalhaNaval(string m):modo(m){}

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

