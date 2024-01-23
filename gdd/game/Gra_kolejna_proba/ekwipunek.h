#pragma once
#include "gracz.h"
#include "przedmiot.h"
#include <vector>

class Ekwipunek {
public:
    Ekwipunek();

    void dodajPrzedmiotZPlecaka(Gracz &gracz, int indeks);
    void wyswietlZawartosc();
    void usunPrzedmiot(int indeks);


    std::vector<przedmiot> ekwipunek;
    static const int maksymalnaIloscPrzedmiotow = 6;
};
