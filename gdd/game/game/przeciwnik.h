#pragma once
#include <string>
#include <iostream>


using namespace std;

class Przeciwnik {

public:

    Przeciwnik(string nazwa, char pole, int atak, int obrona, int zycie, int wartoscDoswiadczenia);

    void ustawPozycje(int x, int y);

    void dostanPozycje(int &x, int &y);

    int obrazenia();

    int dostanObrazenia(int obrazenia);

    string dostanNazwe(){return nazwa;};

    char dostanRuch(int graczX,int graczY);

    char dostanSymbol(){return pole;};

private:
    string nazwa;
    char pole;
    int atak, obrona, zycie, wartoscDoswiadczenia;
    int x, y;
};
