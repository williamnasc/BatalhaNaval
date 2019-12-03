#include <iostream>
#include <pos.h>
#include <navio.h>
#include <tabuleiro.h>
#include <fstream>
#include <batalhanaval.h>

using namespace std;

#define PORTA_TESTE "23456"

int main(int argc, char **argv)
{

    Pos pos;
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

///CONFIGURA O JOGO
{
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

}

    ///ESTABELECE CONEXAO DO SERVIDOR
    if(servidor){
        /// Coloca o socket de controle em modo de espera
        if (c.listen(PORTA_TESTE,1) != mysocket_status::SOCK_OK) {
          cerr << "Não foi possível abrir o socket de controle\n";
          fim = true;
        }
        else
        {
          // Aguarda uma conexao
          cout << "Aguardando conexao do cliente...\n";
          if (c.accept(s) == mysocket_status::SOCK_OK)
          {
            cout << "Cliente conectado no socket " << s << endl;
          }
          else
          {
            cerr << "Não foi possível estabelecer uma conexão\n";
            fim = true;
          }
        }
    }
    ///ESTABELECE CONEXAO DO CLIENTE
    if(cliente){
        /// Leh o IP do servidor
        if( argc<2 ) {
          cout << "Maquina onde esta rodando o servidor (IP): ";
          cin >> ws;
          getline(cin, msg);
        }
        else {
          msg = argv[1];
        }

        if (s.connect(msg.c_str(), PORTA_TESTE) == mysocket_status::SOCK_OK)
        {
          cout << "Conectado ao servidor " << msg << " na porta " << PORTA_TESTE
               << " pelo socket " << s << endl;
        }
        else
        {
          cerr << "Problema na conexao ao servidor " << msg << " na porta " << PORTA_TESTE << endl;
          fim = true;
        }
    }

///TROCA DE MENSAGENS
{
    ///TROCA DE MENSAGENS
        bool primeiroTiro = true;
        while (!fim)
        {
            if(servidor && primeiroTiro){
                do{
                    /*
                       cout << "Mensagem para o oponente [max " << MYSOCKET_TAM_MAX_STRING << " caracteres, FIM para terminar]: ";
                       cin >> ws;
                       getline(cin,msg);
                    */
                    ///ler a posição do tiro, até que ela seja valida e possivel
                    do{
                        cout << "digite a posição da primeira jogada: ";
                        pos = pos.digitarPos();
                    }while (pos.isValid() && jogo.tabInimigo.isLivre(pos));

                    //msg = pos.imprimir();
                    msg = "A0";
                    ///add tiro aos tiros emitidos
                    jogo.meuTabuleiro.tirosEmitidos.push_back(pos);
                    cout << "   enviado";

                   } while (msg.size()==0 || msg.size()>MYSOCKET_TAM_MAX_STRING);
                     if (!fim) fim = (msg=="FIM");

                     iResult = s.write_string(msg);
                     if ( iResult == mysocket_status::SOCK_ERROR )
                     {
                       cerr << "Problema ao enviar mensagem para o oponente\n";
                       s.close();
                       fim = true;
                     }
                primeiroTiro = false;
            }
          cout << "Aguardando msg do oponente...\n";
          iResult = s.read_string(msg);
          if (iResult != mysocket_status::SOCK_OK)
          {
            if (iResult==mysocket_status::SOCK_ERROR)
            {
              cout << "Erro na recepcao de msg do oponente. Desconectando\n";
              s.close();
              fim = true;
            }
            if (iResult==mysocket_status::SOCK_DISCONNECTED)
            {
              cout << "Oponente desconectou\n";
              s.close();
              fim = true;
            }
            if (iResult==mysocket_status::SOCK_TIMEOUT)
            {
              // Nunca deve acontecer, jah que a read_string nao tem timeout
            }
          }
          else
          {///MENSAGEM RECEBIDA

 /*           cout << "Mensagem recebida do oponente: " << msg << endl;
            if (msg == "FIM")
            {
              cout << "Oponente encerrou\n";
              s.close();
              fim = true;
            }*/
              cout << "Mensagem recebida do oponente: " << msg << endl;
              cout <<msg[0] <<endl<<msg[0] <<endl<<msg[0] <<endl
          }

          if (!fim) do
          {
            cout << "Mensagem para o oponente [max " << MYSOCKET_TAM_MAX_STRING << " caracteres, FIM para terminar]: ";
            cin >> ws;
            getline(cin,msg);
          } while (msg.size()==0 || msg.size()>MYSOCKET_TAM_MAX_STRING);
          if (!fim) fim = (msg=="FIM");

          iResult = s.write_string(msg);
          if ( iResult == mysocket_status::SOCK_ERROR )
          {
            cerr << "Problema ao enviar mensagem para o oponente\n";
            s.close();
            fim = true;
          }
        }

}


    // Desliga os sockets
    cout << "Encerrando o socket de conexoes\n";
    c.close();
    cout << "Encerrando o socket de comunicacao\n";
    s.close();

    /// Encerramento da biblioteca de sockets
    mysocket::end();

    return 0;
}
