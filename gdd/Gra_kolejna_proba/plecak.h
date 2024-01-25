#pragma once
#include <vector>
#include "przedmiot.h"

class Gracz;

class Plecak {
public:
    Plecak();

    void dodajPrzedmiot(przedmiot& przedmiot);

    void wyswietlZawartosc();
    void wyswietlZawartoscEkwipunek();
    void usunPrzedmiot(unsigned int indeks);
    void zalozPrzedmiotZPlecaka(unsigned int indeks, Gracz &gracz);
    void sciagnijPrzedmiotZEkwipunku(unsigned int indeks, Gracz &gracz);
    void uleczGracza(int indeks,Gracz &gracz);
    std::vector<przedmiot> zawartosc;
    std::vector<przedmiot> ekwipunek;
    static const int maksymalnaIloscPrzedmiotow = 6;
};
