#pragma once

#include "plecak.h"
#include "pole.h"


class Gracz : public Pole {
public:
    Gracz();
    void inicjalizajca(int poziom, int zycie, float atak, float obrona, int doswiadczenie);
    Plecak plecak;
    void zwiekszenieAtaku(int bonusowyAtak);
    void zwiekszenieObrony(int bonusowaObrona);
    void zmniejszenieAtaku(int bonusowyAtak);
    void zmniejszenieObrony(int bonusowaObrona);
    int dostanBonusAtak()  {return bonusAtak;}
    int dostanAtak()  {return atak;}
    int dostanObrona()  {return obrona;}
    int dostanPoziom()  {return poziom;}
    int dostanZycie()  {return zycie;}
    int dostanpoziom()  {return poziom;}
    int dostandoswiadczenie()  {return atak;}
    void dostanDoswiadczenie(int doswiadczenie);
    void wyswietlStatystyki();
    float obrazenia();
    int dostanObrazenia(float obrazenia);
    int x, y;
private:
    int poziom, zycie, doswiadczenie, bonusAtak, bonusObrona;
    float atak, obrona;
};
