#include <iostream>
#include <pos.h>
#include <navio.h>
#include <tabuleiro.h>
#include <fstream>

using namespace std;

int main()
{

    Tabuleiro t;
    Porta_Avioes p('h');
    cout << p.getDir();
    ifstream a;
    a.open("bn");
    if (!a.is_open())
    {
      cout << "arq n aberto";
    }
    if(t.ler(a))
        cout << "\ndeu bom\n";
        else {
        cout << "\ndeu ruim\n";
    }

    cout << "Hello World!" << endl;
    return 0;
}
