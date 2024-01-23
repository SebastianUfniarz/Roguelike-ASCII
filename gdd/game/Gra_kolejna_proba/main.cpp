#include "mapa.h"
#include <iostream>
#include <systemgry.h>
using namespace std;

int main()
{

        SystemGry systemGry;
        systemGry.mapa.stworzMape(50,20);
        systemGry.zacznijGre();

    return 0;
}
