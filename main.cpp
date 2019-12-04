#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <batalhanaval.h>

using namespace std;

#define PORTA_TESTE "23456"

int main(int argc, char **argv)
{
    srand(time(NULL));

    Pos pos,posAnt;
    int controle;
    char respostaTiro = 'i';
    char tipoNav;
    bool cliente =false, servidor=false,
         jManual = false, jAutomatico = false,
         jogRepetida = false;
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
    if(controle == 1)
        jManual = true;
    if(controle == 2)
        jAutomatico = true;

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
                    ///PRIMEIRO TIRO

                    /// MANUALMENTE
                    if(jManual){
                        ///ler a posição do tiro, até que ela seja valida e possivel
                        do{
                            jogRepetida = false;

                            cout << "digite a posição da primeira jogada: ";
                            cin >> ws;
                            getline(cin,msg);
                            pos = Pos(char(msg[0]),char(msg[1]));
                            cout << msg[0] << msg[1];

                        }while(!jogo.isValid(pos)/*(msg.size() != 2) && false*/);

                    }

                    /// AUTOMATICO
                    if(jAutomatico){
                        do{
                            jogRepetida = false;

                            // posição aleatoria
                            pos.lin = int(rand() % 10);
                            pos.col = int (rand() % 10);
                            msg = pos.imprimir();

                        }while(!jogo.isValid(pos)/*(msg.size() != 2) && false*/);
                    }

                } while (msg.size()==0 || msg.size()>MYSOCKET_TAM_MAX_STRING);
                     if (!fim) fim = (msg=="FIM");
                    ///ENVIADO
                     ///add tiro aos tiros emitidos
                     jogo.meuTabuleiro.tirosEmitidos.push_back(10*pos.lin+pos.col);
                     cout << "   enviado";

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
              cout << "GANHEI!!!!!!!!!!!!!!!!!!!!!" <<endl;
              cout << "ACABOU O JOGO:\n";
              cout << "placar: pontos do OPONENTE: " << jogo.getPontosInimigo()<<endl;
              cout << "placar: MEUS pontos       : " << jogo.getMeusPontos()<<endl;
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

 //           cout << "Mensagem recebida do oponente: " << msg << endl;
            if (jogo.verificaFim())
            {
              cout << "ACABOU O JOGO:\n";
              cout << "placar: pontos do OPONENTE: " << jogo.getPontosInimigo()<<endl;
              cout << "placar: MEUS pontos       : " << jogo.getMeusPontos()<<endl;
              s.close();
              fim = true;
              break;
            }
              ///MENSAGEM DO OPONENTE
              cout << "Mensagem recebida do oponente: " << msg << endl;
              //cout <<msg[0] << endl << msg[1] << endl << msg[2] << endl;

              ///MEU TIRO ANTERIOR

              posAnt = pos;

              ///pega o resultado do tiro anterior
              respostaTiro = msg[2];
              cout << "resposta do meu Tiro anterior: " << respostaTiro << endl;
              ///trata o resultado do tiro anterior e escreve no tab inimigo
              if(respostaTiro == '#'){
                jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::ATINGIDA;
                ///add aos acertos
                jogo.meuTabuleiro.acertos.push_back(posAnt);
              }
              if(respostaTiro == 'X' || respostaTiro == 'x')
                  jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::BLOQUEADA;

              if(respostaTiro == 'P' || respostaTiro == 'p'){
                  //addDestruidoToTab(respostaTiro,posAnt)
                  jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::PORTA_AVIAO;
                  jogo.addPonto(respostaTiro);
              }
              if(respostaTiro == 'C' || respostaTiro == 'c'){
                  jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::CRUZADOR;
                  jogo.addPonto(respostaTiro);
              }
              if(respostaTiro == 'D' || respostaTiro == 'd'){
                  jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::DESTROYER;
                  jogo.addPonto(respostaTiro);
              }
              if(respostaTiro == 'S' || respostaTiro == 's'){
                  jogo.tabInimigo.tab[10*(posAnt.lin)+posAnt.col] = EstadoPos::SUBMARINO;
                  jogo.addPonto(respostaTiro);
              }


              ///TIRO RECEBIDO ATUAL
              ///
              ///pega posicao recebida do tiro
              pos = Pos(char(msg[0]),char(msg[1]));
              cout << "tiro que chegou aqui: "<<pos.imprimir() <<" = l: "<<pos.lin<<";c: "<<pos.col <<endl;
              ///testa se o tiro é valido
              if(Pos(char(msg[0]),char(msg[1])).isValid()){

                  //add a tiros recebidos
                  jogo.meuTabuleiro.tirosRecebidos.push_back(pos);

                  //saber se acertou alguma coisa
                  if(jogo.verificaAcerto(pos)){
                      cout << "O TIRO DELE TE ACERTOU!!!!!!"<<endl;
                      respostaTiro = '#';
                      jogo.meuTabuleiro.tab[10*(pos.lin)+pos.col] = EstadoPos::ATINGIDA;

                      //verifica se destruiu algum navio
                      if(jogo.verificaDestruido(tipoNav)){
                            cout << "MEU "<<tipoNav<<" FOI DESTRUIDO" << endl;
                            respostaTiro = tipoNav;

                            //verifica se todos os meus navios foram destrudios -> acabou o jogo
                            if(jogo.verificaFim()){
                                cout << "PERDI!!!!!!!!!!!!!!!!!!!!!" <<endl;
                                cout << "ACABOU O JOGO:\n";
                                cout << "placar: pontos do OPONENTE: " << jogo.getPontosInimigo() <<endl;
                                cout << "placar: MEUS pontos       : " << jogo.getMeusPontos()<< endl;
                                s.close();
                                fim = true;
                                break;
                            }

                      }

                      //alterar no tabuleiro
                      jogo.meuTabuleiro.tab[10*(pos.lin)+pos.col] = EstadoPos::ATINGIDA;
                  }else{
                      cout << "O TIRO DELE ERROU!!!!!!"<<endl;
                      respostaTiro = 'X';
                      jogo.meuTabuleiro.tab[10*(pos.lin)+pos.col] = EstadoPos::BLOQUEADA;


                  }
                    ///imprime os tabuleiros atualizados
                    jogo.imprimirTabs();
              ///tiro n é valido
              }else{
                    cout << "ESSA POSICAO NÃO É VALIDA!!1";
                    respostaTiro = 'i';
              }

          }

          if (!fim) do
          {
              /*
            cout << "Mensagem para o oponente [max " << MYSOCKET_TAM_MAX_STRING << " caracteres, FIM para terminar]: ";
            cin >> ws;
            getline(cin,msg);
                */
              ///RESPOSTA

                /// MANUAL
              if(jManual){
                  ///ler a posição do tiro, até que ela seja valida e possivel
                  do{

                      jogRepetida = false;

                      cout << "digite a posição da primeira jogada: ";
                      cin >> ws;
                      getline(cin,msg);
                      pos = Pos(char(msg[0]),char(msg[1]));
                      cout << msg[0] << msg[1];

                  }while(!jogo.isValid(pos)/*(msg.size() != 2) && false*/);
              }

              ///AUTOMATICA
              if(jAutomatico){
                  do{

                      jogRepetida = false;
                      // posição aleatoria
                      pos.lin = int(rand() % 10);
                      pos.col = int (rand() % 10);
                      msg = pos.imprimir();
                      cout << pos.imprimir() << endl;

                  }while(!jogo.isValid(pos));

              }
             //ADICIONA O RESULTADO DO TIRO ANTERIO A MENSAGEM
              msg += respostaTiro;

          } while (msg.size()==0 || msg.size()>MYSOCKET_TAM_MAX_STRING);

          if (!fim) fim = (msg=="FIM");
          ///add tiro aos tiros emitidos
          jogo.meuTabuleiro.tirosEmitidos.push_back(10*pos.lin+pos.col);
          //cout << "   enviado";

          iResult = s.write_string(msg);
          if ( iResult == mysocket_status::SOCK_ERROR )
          {
            cerr << "Problema ao enviar mensagem para o oponente\n";
            s.close();
            fim = true;
          }
          respostaTiro = 'i'; //reseta desposta tiro;
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
