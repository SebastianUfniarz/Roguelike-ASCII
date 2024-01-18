#pragma once

class Gracz {

public:

    Gracz();
    void inicjalizajca(int poziom, int zycie, int atak, int obrona, int doswiadczenie);

    int obrazenia();

    void ustawPozycje(int x, int y);

    void dostanPozycje(int &x, int &y);

    void dostanDoswiadczenie(int doswiadczenie);

    int dostanObrazenia(int obrazenia);

private:

    int x, y, poziom, zycie, atak, obrona, doswiadczenie;


};
