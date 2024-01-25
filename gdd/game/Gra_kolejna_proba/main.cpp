#include "mapa.h"
#include <iostream>
#include <systemgry.h>
#include <ctime>
using namespace std;

int main()
{
        srand(time(0));
        SystemGry systemGry;
        systemGry.mapa.stworzMape();
        systemGry.zacznijGre();

    return 0;
}
