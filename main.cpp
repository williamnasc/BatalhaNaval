#include <iostream>
#include <pos.h>
#include <navio.h>
#include <tabuleiro.h>
#include <fstream>

using namespace std;

int main()
{

    Tabuleiro t;
    Porta_Avioes p;

    ifstream a;
    a.open("bn");
    t.ler(a);

    cout << "Hello World!" << endl;
    return 0;
}
