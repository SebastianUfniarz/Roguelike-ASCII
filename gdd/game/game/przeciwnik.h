#pragma once
#include <string>
#include <iostream>


using namespace std;

class Przeciwnik {

public:

    Przeciwnik(string nazwa, char pole, int atak, int obrona, int zycie, int zrecznosc, int szczescie, int wartoscDoswiadczenia);

    void ustawPozycje(int x, int y);

    void dostanPozycje(int &x, int &y);

    int obrazenia();

    int dostanObrazenia(int obrazenia);

    string dostanNazwe(){return nazwa;};

    char dostanRuch(int graczX,int graczY);

    char dostanSymbol(){return pole;};

    bool unik(Przeciwnik &Przeciwnik);

    bool ciosKrytyczny(Przeciwnik &Przeciwnik);


private:
    string nazwa;
    char pole;
    int atak, obrona, zycie, zrecznosc, szczescie , wartoscDoswiadczenia;
    int x, y;
};
