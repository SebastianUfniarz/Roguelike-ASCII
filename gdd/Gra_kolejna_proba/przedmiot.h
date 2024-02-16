#pragma once
#include "pole.h"
#include <string>

enum przedmiotTyp {
    HELM,
    PANCERZ,
    SPODNIE,
    BRON,
    PIERSCIEN,
    PAS,
    BUTY,
    REKAWICE,
    AMULET,
    MIKSTURA_UZDROWIENIA
};

using namespace std;

class przedmiot : public Pole {
public:
    przedmiot();
    string nazwa;
    przedmiotTyp typ;
    float atak, obrona, szczescie, zrecznosc;
    int szansa;
};

string typToString(przedmiotTyp typ);



