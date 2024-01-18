#pragma once
#include "gracz.h"
#include "poziom.h"

#include <string>

using namespace std;

class SystemGry {

public:

    SystemGry(string nazwaPlikuPoziomu);

    void zacznijGre();
    void ruchGracza();

private:
    Gracz gracz;
    Poziom poziom;

};
