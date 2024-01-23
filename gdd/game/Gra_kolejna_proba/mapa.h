#pragma once
#include "gracz.h"
#include "ogr.h"
#include "przeciwnik.h"
#include <vector>
#include <pole.h>
#include <przedmiot.h>
#include "goblin.h"
#include "szczur.h"
#include "zombi.h"
#include "zywiolak.h"
#include <memory>

using namespace std;

class Mapa {
public:
    Mapa();

    int szerokoscMapy;
    int wysokoscMapy;
    void stworzMape(int szerokosc, int wysokosc);
    void wyswietl();
    void dodajGracza(int x, int y, Gracz &gracz);
    void dodajPrzedmiot(int x, int y, string nazwa, int atak, int obrona, przedmiotTyp typ);
    void dodajPrzeciwnika(int x, int y, char pole, string nazwa, int atak, int obrona, int zycie, int wartoscDoswiadczenia);
    void dodajPrzeciwnika();
    void przesunGracza(char kierunek, Mapa &mapa, Gracz &gracz);
    void czyscMape();
    bool czyMoznaPrzejsc(int x, int y);
    void podniesPrzedmiot(Gracz &gracz);
    bool czyIstniejePrzedmiot( int x, int y, Mapa &mapa );
    void setPole(int x, int y, char pole);
    void atak(Gracz &gracz);
    void atakujPrzeciwnika(Gracz &gracz, int celX, int celY);
    void podniesPrzedmiotNaPozycji(int x, int y, Gracz &gracz);
    bool czyPolePuste(int x, int y);
    bool czyIstniejePrzeciwnik(int x, int y);
    void aktualizujPotwory(Gracz &gracz, Mapa &mapa);
    void przetworzRuchPrzeciwnika(Gracz &gracz, int przeciwnikIndex, int miejsceX, int miejsceY, Mapa &mapa);
    void przesunZAutomatycznymAtakiem(Gracz &gracz, int nowyX, int nowyY);
    void dodajPrzeciwnikaLosowo(Przeciwnik przeciwnik, int ilosc);
    vector<przedmiot> przedmioty;
    vector<Przeciwnik> przeciwnicy;
    vector<vector<Pole>> mapa;
    Goblin goblin;
    Szczur szczur;
    Zombi zombi;
    Ogr ogr;
    Zywiolak zywiolak;
};


