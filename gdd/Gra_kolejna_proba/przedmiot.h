#pragma once
#include "pole.h"
#include <string>

enum przedmiotTyp {
    HELM,
    PANCERZ,
    SPODNIE,
    MIECZ,
    PIERSCIEN,
    PAS,
    MIKSTURA
};

using namespace std;

class przedmiot : public Pole {
public:
    przedmiot();
    string nazwa;
    przedmiotTyp typ;
    float zycie, atak, obrona, szczescie, zrecznosc;
};


