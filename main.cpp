#include <iostream>
#include <pos.h>
#include <navio.h>
#include <tabuleiro.h>
#include <fstream>
#include <batalhanaval.h>

using namespace std;

int main()
{
    BatalhaNaval b;
    b.initTabuleiros();
    b.imprimirTabs();
    /*
    Tabuleiro t;
    ifstream a;
    t.initTab();

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

    cout << t;
*/
    cout << "Hello World!" << endl;
    return 0;
}
