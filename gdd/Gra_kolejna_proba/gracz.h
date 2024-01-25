#pragma once

#include "plecak.h"
#include "pole.h"



class Gracz : public Pole {
public:
    Gracz();
    void inicjalizajca(int poziom, int zycie, float atak, float obrona, float zrecznosc, float szczescie, int doswiadczenie);
    Plecak plecak;
    void zwiekszenieAtaku(int bonusowyAtak);
    void zwiekszenieObrony(int bonusowaObrona);
    void zwiekszenieZrecznosc(int bonusowyZrecznosc);
    void zwiekszenieSzczescie(int bonusowaSzczescie);
    void zmniejszenieZrecznosc(int bonusowyZrecznosc);
    void zmniejszenieSzczescie(int bonusowaSzczescie);
    void zmniejszenieAtaku(int bonusowyAtak);
    void zmniejszenieObrony(int bonusowaObrona);
    int dostanBonusAtak()  {return bonusAtak;}
    int dostanAtak()  {return atak;}
    int dostanObrona()  {return obrona;}
    int dostanPoziom()  {return poziom;}
    int dostanZycie()  {return zycie;}
    int dostanpoziom()  {return poziom;}
    float dostanZrecznosc(){return zrecznosc;}
    float dostanSzczescie(){return szczescie;}
    int dostandoswiadczenie()  {return atak;}
    void dostanDoswiadczenie(int doswiadczenie);
    bool szansaUniuku(float zrecznosc);
    bool szansaKryta(float szczescie);
    void wyswietlStatystyki();
    void ulecz(int ile, int aktualneZycie);
    float obrazenia();
    int dostanObrazenia(float obrazenia);
    int x, y;
    int maxZycie;
private:
    int poziom, zycie, doswiadczenie, bonusAtak, bonusObrona, bonusZrecznosc, bonusSzczescie;
    float atak, obrona, zrecznosc, szczescie;
};
