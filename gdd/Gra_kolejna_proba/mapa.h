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
    void dodajLas(int ilosc);
    int szerokoscMapy;
    int wysokoscMapy;
    void stworzMape();
    void wyswietl();
    void dodajGracza(int x, int y, Gracz &gracz);
    void dodajPrzedmiot(string nazwa, float atak,float obrona,float szczescie, float zrecznosc, przedmiotTyp typ);
    void dodajPrzeciwnika(int x, int y, char pole, string nazwa, int atak, int obrona, int zycie, float zrecznosc, float szczescie, int wartoscDoswiadczenia);
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
    void testujWalkiWielokrotnie(int iloscTestow);
    vector<przedmiot> przedmioty;
    vector<Przeciwnik> przeciwnicy;
    vector<vector<Pole>> mapa;
    void floodFill(int x, int y, char symbol);
    bool sprawdzDostepnosc();
    void dodajSciany(int ilosc);
    bool czyObszarPusty(int x, int y, int szerokosc, int wysokosc);
    void dodajPokoje(int ilosc);
    void floodFillPrzejscie(int x, int y, int &maxKroki, int &maxX, int &maxY, int kroki);
    void ustawSymbolNajdalszegoPola();
    void generujNowaMape(Mapa &mapa);
    Goblin goblin;
    Szczur szczur;
    Zombi zombi;
    Ogr ogr;
    bool czyWszystkiePolaPoprawne();
    Zywiolak zywiolak;
};


