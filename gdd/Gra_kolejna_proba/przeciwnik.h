#pragma once
#include "gracz.h"
#include "pole.h"
#include <string>
#include <iostream>



using namespace std;

class Przeciwnik : public Pole {

public:

    Przeciwnik();

    float obrazenia();
    bool czyNeutralny = true;
    int dostanObrazenia(float obrazenia);
    float zycieMax;
    int x, y;
    void wyswietlStatystyki();
    bool szansaUniuku(float zrecznosc);
    string nazwa;
    int zycie, wartoscDoswiadczenia;
    bool szansaKryta(float szczescie);
    float atak, obrona, zrecznosc, szczescie;
    char dostanRuch(Gracz &gracz);
    vector<Przeciwnik> potwory;

};
