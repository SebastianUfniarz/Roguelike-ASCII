#pragma once
#include <vector>
#include <string>
#include "gracz.h"
#include "przeciwnik.h"

using namespace std;

class Poziom {

public:
    Poziom();

    void wczytaj(string nazwaPliku, Gracz &gracz);
    void wyswietl();
    void rusz(char komenda, Gracz &gracz);
    char dostanPole(int x, int y);
    void ustawPole(int x, int y, char pole);
    void aktualizujPotwory(Gracz &gracz);


private:
    vector <string> mapa;
    void przetworzRuchGracza(Gracz &gracz, int miejsceX, int miejsceY);
    void przetworzRuchPrzeciwnika(Gracz &gracz, int przeciwnikIndex, int miejsceX, int miejsceY);
    void atak(Gracz &gracz, int celX, int celY);
    vector <Przeciwnik> przeciwnicy;
};
