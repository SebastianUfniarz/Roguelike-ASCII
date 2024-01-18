#pragma once

class Gracz {

public:

    Gracz();
    void inicjalizajca(int poziom, int zycie, int atak, int obrona,int zrecznosc, int szczescie, int doswiadczenie);

    int obrazenia();

    void ustawPozycje(int x, int y);

    void dostanPozycje(int &x, int &y);

    void dostanDoswiadczenie(int doswiadczenie);

    int dostanObrazenia(int obrazenia);

    bool unik(Gracz &gracz);

    bool ciosKrytyczny(Gracz &gracz);

    void wyswietlStatystyki();

private:

    int x, y, poziom, zycie, atak, obrona, zrecznosc, doswiadczenie, szczescie;


};
