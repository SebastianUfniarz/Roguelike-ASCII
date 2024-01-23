#pragma once
#include "gracz.h"
#include "mapa.h"

#include <string>

using namespace std;

class SystemGry {

public:
    SystemGry();
    void zacznijGre();
    void ruchGracza();
    Gracz gracz;
    Mapa mapa;
    Plecak plecak;
    void ini();
};
