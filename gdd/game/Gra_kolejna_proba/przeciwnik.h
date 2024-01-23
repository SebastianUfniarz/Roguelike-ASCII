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

    int dostanObrazenia(float obrazenia);

    int x, y;
    void wyswietlStatystyki();

    string nazwa;
    int zycie, wartoscDoswiadczenia;
    float atak, obrona;
    char dostanRuch(Gracz &gracz);
    vector<Przeciwnik> potwory;
};
