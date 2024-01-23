#pragma once
#include "pole.h"
#include <string>

enum przedmiotTyp {
    HELM,
    PANCERZ,
    SPODNIE,
    // Dodaj inne miejsca według potrzeb
};

using namespace std;

class przedmiot : public Pole {
public:
    przedmiot();
    string nazwa;
    przedmiotTyp typ;
    int atak, obrona;
};


