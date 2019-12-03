#include <iostream>
#include <pos.h>
#include <navio.h>
#include <tabuleiro.h>
#include <fstream>
#include <batalhanaval.h>

using namespace std;

#define PORTA_TESTE "23456"

int main()
{
    int controle;
    bool cliente =false, servidor=false;
    BatalhaNaval jogo;

    ///VARIAVEIS DE COMUNICACAO
    mysocket_status iResult;
    tcp_mysocket_server c;
    tcp_mysocket s;
    bool fim = false;
    string msg;

    // Inicializa a biblioteca de sockets (exigida no Windows)
    iResult = mysocket::init();
    if (iResult != mysocket_status::SOCK_OK) {
      cerr << "Biblioteca mysocket nao pode ser inicializada\n";
      exit(1);
    }

    do{
        cout << "digite o modo do compudor:"<< endl;
        cout << "1 - SERVIDOR"<< endl;
        cout << "2 - CLIENTE" << endl;
        cin >> controle;
    }while (controle != 1 && controle != 2);
    if(controle == 1)
        servidor = true;
    if(controle == 2)
        cliente = true;

    do{
        cout << "Escolha o modo de inicializar o tabuleiro " << endl;
        cout << "1 - ARQUIVO"    << endl;
        cout << "2 - MANUAL"     << endl;
        cout << "3 - AUTOMATICA" << endl;
        cin >> controle;
    }while(controle != 1 && controle != 2 && controle != 3);

    jogo.initTabuleiros();
    jogo.imprimirTabs();

    do{
        cout << "Escolha o modo do jogador " << endl;
        cout << "1 - MANUAL"     << endl;
        cout << "2 - AUTOMATICA" << endl;
        cin >> controle;
    }while(controle != 1 && controle != 2);








    return 0;
}
