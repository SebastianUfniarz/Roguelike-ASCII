#include "mapa.h"
#include "boss.h"
#include "podloga.h"
#include "przejscie.h"
#include "sciana.h"
#include <iostream>
#include <random>
#include <vector>
#include "gracz.h"
#include "plecak.h"
#include "przeciwnik.h"
#include <math.h>

void Mapa::czyscMape() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
using namespace std;

Mapa::Mapa() : szerokoscMapy(0), wysokoscMapy(0) {}

void Mapa::stworzMape() {

    int szerokosc = rand() % 15 + 10;
    int wysokosc = rand() % 11 + 10;
    szerokoscMapy = szerokosc;
    wysokoscMapy = wysokosc;
    mapa.resize(wysokosc, std::vector<Pole>(szerokosc, Podloga()));

    for (int i = 0; i < wysokosc; ++i) {
        mapa[i][0] = Sciana();
        mapa[i][szerokosc - 1] = Sciana();
    }

    for (int j = 0; j < szerokosc; ++j) {
        mapa[0][j] = Sciana();
        mapa[wysokosc - 1][j] = Sciana();
    }
    int szansa = 50;
    int randomValue = rand() % 100;

    if(randomValue < szansa){
        dodajPokoje(2);
        dodajPrzeciwnikaLosowo(Szczur(),3);
        dodajPrzeciwnikaLosowo(Goblin(),1);

        dodajMikstureUzdrowienia();
    }
    else {
        dodajSciany(20);
        dodajPrzeciwnikaLosowo(Szczur(),1);
        dodajPrzeciwnikaLosowo(Goblin(),2);

        dodajMikstureUzdrowienia();
    }

}
Przeciwnik Mapa::losujPrzeciwnika(int poziom) {
    int losowa = rand() % 100;

    if (poziom == 1) {
        if (losowa < 70) {
            return losujPrzeciwnikaZPuliLatwiejszej();
        } else {
            return losujPrzeciwnikaZPuliTrudniejszej();
        }
    } else if (poziom == 2) {
        if (losowa < 30) {
            return losujPrzeciwnikaZPuliLatwiejszej();
        } else {
            return losujPrzeciwnikaZPuliTrudniejszej();
        }
    }

    return losujPrzeciwnikaZPuliTrudniejszej();
}

Przeciwnik Mapa::losujPrzeciwnikaZPuliLatwiejszej() {
    Szczur szczur;
    Goblin goblin;
    Zombi zombie;
    int losowa = rand() % 3;
    if (losowa == 0) {
        return szczur;
    }
    else if (losowa == 1){
        return zombie;
    }
    else {
        return goblin;
    }
}

Przeciwnik Mapa::losujPrzeciwnikaZPuliTrudniejszej() {
    Ogr ogr;
    Zywiolak zywiolak;
    int losowa = rand() % 3;
    if (losowa == 0) {
        return zywiolak;
    }
    else {
        return ogr;
    }
}

void Mapa::dodajPrzeciwnikowLosowoNowaMapa(int poziom, Mapa &mapa, int bylawysokosc) {
    int obecnaszerokosc = mapa.szerokoscMapy;
    int obecnawysokosc = mapa.wysokoscMapy;

    for (int k = 0; k < 3; ++k) {
        int x = rand() % (obecnaszerokosc - 1 + 1) + 1 ;
        int y = rand() % (obecnawysokosc - bylawysokosc + 2 + 1) + bylawysokosc + 2;
        Przeciwnik przeciwnik = losujPrzeciwnika(poziom);

        if (mapa.czyPolePuste(x, y)) {
            przeciwnik.x = x;
            przeciwnik.y = y;
            mapa.mapa[y][x] = przeciwnik;
            przeciwnik.zycieMax = przeciwnik.zycie;

            przeciwnicy.push_back(przeciwnik);
        } else {
            --k;
        }
    }
}



void Mapa::ustawSymbolNajdalszegoPola() {
    int xGracza = 0, yGracza = 0;


    for (int i = 0; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            if (mapa[i][j].symbol == '@') {
                xGracza = j;
                yGracza = i;
                break;
            }
        }
    }

    int maxKroki = 0, maxX = 0, maxY = 0;


    for (int i = yGracza; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            if (mapa[i][j].symbol == '.' || mapa[i][j].symbol == 'I' || czyIstniejePrzeciwnik(j, i)) {
                int kroki = abs(xGracza - j) + abs(yGracza - i);
                if (kroki > maxKroki) {
                    maxKroki = kroki;
                    maxX = j;
                    maxY = i;
                }
            }
        }
    }

    if (maxKroki > 0) {
        mapa[maxY][maxX] = Przejscie();
    }
}
void Mapa::dodajSciany(int ilosc) {
    for (int i = 0; i < ilosc; ++i) {
        int x = rand() % (szerokoscMapy - 3 + 1)  ;
        int y = rand() % (wysokoscMapy - 3 + 1)  ;

        if (czyPolePuste(x, y)) {
            mapa[y][x] = Sciana();
        } else {
            --i;
        }
    }
}

void Mapa::dodajScianyNowaMapa(Mapa &mapa, int ilosc, int bylawysokosc) {
    int obecnaszerokosc = mapa.szerokoscMapy;
    bylawysokosc += 2;
    int obecnawysokosc = mapa.wysokoscMapy - 3;
    for (int i = 0; i < ilosc; ++i) {
        int x = rand() % (obecnaszerokosc - 2 + 1) + 2 ;
        int y = rand() % (obecnawysokosc - bylawysokosc + 1) + bylawysokosc ;
        if (mapa.czyPolePuste(x, y)) {
            mapa.mapa[y][x] = Sciana();
        } else {
            --i;
        }
    }
}

void Mapa::dodajPokoje(int ilosc) {
    for (int i = 0; i < ilosc; ++i) {

        int szerokoscPokoju = rand() % 7 + 3;
        int wysokoscPokoju = rand() % 3 + 3;


        int x = rand() % (szerokoscMapy - szerokoscPokoju - 2) + 1;
        int y = rand() % (wysokoscMapy - wysokoscPokoju - 2) + 1;


        if (czyObszarPusty(x, y, szerokoscPokoju, wysokoscPokoju)) {

            for (int j = y; j < y + wysokoscPokoju; ++j) {
                for (int k = x; k < x + szerokoscPokoju; ++k) {
                    if (j == y || j == y + wysokoscPokoju - 1 || k == x || k == x + szerokoscPokoju - 1) {
                        if ((j == y || j == y + wysokoscPokoju - 1) && k == x + szerokoscPokoju / 2) {
                            mapa[j][k] = Podloga();  // Dodaj wejście
                        } else {
                            mapa[j][k] = Sciana();
                        }
                    } else {
                        mapa[j][k] = Podloga();
                    }
                }
            }
        } else {
            --i;
        }
    }
}

void Mapa::dodajPokojeNowaMapa(Mapa &mapa, int ilosc, int bylawysokosc) {
    int obecnaszerokosc = mapa.szerokoscMapy - 5;
    bylawysokosc += 2;
    int obecnawysokosc = mapa.wysokoscMapy - 5;

    for (int i = 0; i < ilosc; ++i) {
        int szerokoscPokoju = rand() % 13 + 3;
        int wysokoscPokoju = rand() % 5 + 3;

        int x = rand() % (obecnaszerokosc - 2 + 1) + 2 ;
        int y = rand() % (obecnawysokosc - bylawysokosc + 1) + bylawysokosc ;

        if (mapa.czyObszarPusty(x, y, szerokoscPokoju, wysokoscPokoju)) {
            for (int j = y; j < y + wysokoscPokoju; ++j) {
                for (int k = x; k < x + szerokoscPokoju; ++k) {
                    if (j == y || j == y + wysokoscPokoju - 1 || k == x || k == x + szerokoscPokoju - 1) {
                        if ((j == y || j == y + wysokoscPokoju - 1) && k == x + szerokoscPokoju / 2) {
                            mapa.mapa[j][k] = Podloga();
                        } else {
                            mapa.mapa[j][k] = Sciana();
                        }
                    } else {
                        mapa.mapa[j][k] = Podloga();
                    }
                }
            }
        } else {
            --i;
        }
    }
}
void Mapa::dodajGracza(int x, int y, Gracz &gracz) {
    x = rand() % (szerokoscMapy - 2) + 1;
    y = rand() % 3 + 1;

        while (!czyPolePuste(x, y)) {
            x = rand() % (szerokoscMapy - 2) + 1;
        }

        gracz.x = x;
        gracz.y = y;
        mapa[y][x] = gracz;
        gracz.inicjalizajca(1, 50, 10, 5, 5, 10, 50);
}

void Mapa::dodajPrzeciwnikaLosowo(Przeciwnik przeciwnik, int ilosc) {
        if(przeciwnik.nazwa == "Boss"){
            int x = szerokoscMapy - 5;
            int y = wysokoscMapy - 5;
            przeciwnik.x = x;
            przeciwnik.y = y;
            mapa[y][x] = przeciwnik;
            przeciwnik.zycieMax=przeciwnik.zycie;
            przeciwnicy.push_back(przeciwnik);
        }
        else{


    for (int k = 0; k < ilosc; ++k) {
        int x = rand() % (szerokoscMapy - 2) + 1;
        int y = rand() % (wysokoscMapy - 2) + 1;

        if (mapa[y][x].symbol == '.') {
            przeciwnik.x = x;
            przeciwnik.y = y;
            mapa[y][x] = przeciwnik;
            przeciwnik.zycieMax=przeciwnik.zycie;


            przeciwnicy.push_back(przeciwnik);
        } else {
            --k;
        }
        }
    }
}
void Mapa::dodajPrzedmiotyStartowe() {
    vector<tuple<string, float, float, float, float, przedmiotTyp, int>> listaPrzedmiotow{
        {"Helm nowicujsza", 0, 2, 0, 0, HELM, 50},
        {"Pancerz nowicujsza", 0, 4, 0, 0, PANCERZ, 50},
        {"Drewniany miecz", 2, 0, 0, 0, BRON, 50},
        {"Pas zrecznosci", 0, 1, 0, 5, PAS, 50},
        {"Pierscien szczescia", 0, 0, 3, 0, PIERSCIEN, 50},
        {"Spodnie nowicujsza", 0, 3, 0, 1, SPODNIE, 50},
        {"Pierscien zrecznosci", 0, 0, 0, 3, PIERSCIEN, 50}
    };

    for (const auto& przedmiotInfo : listaPrzedmiotow) {
        float szansa = static_cast<float>(rand() % 100) + 1;
        float szansaPrzedmiotu = get<6>(przedmiotInfo);

        if (szansa <= szansaPrzedmiotu) {
            dodajPrzedmiot(get<0>(przedmiotInfo), get<1>(przedmiotInfo), get<2>(przedmiotInfo), get<3>(przedmiotInfo), get<4>(przedmiotInfo), get<5>(przedmiotInfo), get<6>(przedmiotInfo));
        }
    }
}
void Mapa::dodajPrzedmiotyNaNowymPoziomie(int poziom, Mapa &mapa, int bylawysokosc) {
    vector<vector<tuple<string, float, float, float, float, przedmiotTyp, int>>> przedmiotyNaPoziomy{
        // Przedmioty dla poziomu 1
        {
            {"Dlugi Pazur", 4, 0, 0, 1, BRON, 50},
            {"Dlugi Pazur", 5, 0, 0, 2, BRON, 20},
            {"Dlugi Pazur", 7, 0, 0, 4, BRON, 10},
            {"Dlugi Pazur", 10, 0, 0, 4, BRON, 1},

            {"Zabawkowy Topor", 6, 0, 0, 0, BRON, 50},
            {"Zabawkowy Topor", 8, 0, 0, 0, BRON, 20},
            {"Zabawkowy Topor", 9, 0, 0, 0, BRON, 10},
            {"Zabawkowy Topor", 14, 0, 0, 0, BRON, 1},

            {"Czapka szybkiego refleksu", 0, 1, 0, 3, HELM, 50},
            {"Czapka szybkiego refleksu", 0, 2, 0, 4, HELM, 20},
            {"Czapka szybkiego refleksu", 0, 4, 0, 5, HELM, 10},
            {"Czapka szybkiego refleksu", 0, 4, 0, 8, HELM, 1},

            {"Pancerz Wiesniaka", 0, 5, 0, 0, PANCERZ, 50},
            {"Pancerz Wiesniaka", 0, 7, 0, 0, PANCERZ, 20},
            {"Pancerz Wiesniaka", 0, 9, 0, 0, PANCERZ, 10},
            {"Pancerz Wiesniaka", 0, 12, 0, 0, PANCERZ, 1},

            {"Rekwawice elektryka wysokich napiec", 0, 3, 2, 0, REKAWICE, 50},
            {"Rekwawice elektryka wysokich napiec", 0, 4, 3, 0, REKAWICE, 20},
            {"Rekwawice elektryka wysokich napiec", 0, 5, 4, 0, REKAWICE, 10},
            {"Rekwawice elektryka wysokich napiec", 0, 8, 6, 0, REKAWICE, 1},

            {"Wiazany Pasek", 0, 3, 0, 6, PAS, 50},
            {"Wiazany Pasek", 0, 4, 0, 7, PAS, 20},
            {"Wiazany Pasek", 0, 4, 0, 8, PAS, 10},
            {"Wiazany Pasek", 0, 5, 0, 12, PAS, 1},

            {"Radosne Rybaczki", 0, 4, 0, 2, SPODNIE, 50},
            {"Radosne Rybaczki", 0, 5, 0, 4, SPODNIE, 20},
            {"Radosne Rybaczki", 0, 5, 0, 6, SPODNIE, 10},
            {"Radosne Rybaczki", 0, 6, 0, 10, SPODNIE, 1},

            {"Buty biednej piechoty", 0, 2, 0, 4, BUTY, 50},
            {"Buty biednej piechoty", 0, 2, 0, 6, BUTY, 20},
            {"Buty biednej piechoty", 0, 3, 0, 7, BUTY, 10},
            {"Buty biednej piechoty", 0, 3, 5, 9, BUTY, 1},

            {"Amulet Szczescia", 0, 0, 2, 0, AMULET, 50},
            {"Amulet Szczescia", 0, 0, 3, 0, AMULET, 20},
            {"Amulet Szczescia", 0, 0, 5, 0, AMULET, 10},
            {"Amulet Szczescia", 0, 0, 7, 0, AMULET, 1},

            {"Pierscien Skromnej Mocy", 3, 3, 0, 3, PIERSCIEN, 50},
            {"Pierscien Skromnej Mocy", 4, 4, 0, 3, PIERSCIEN, 20},
            {"Pierscien Skromnej Mocy", 4, 5, 0, 3, PIERSCIEN, 10},
            {"Pierscien Skromnej Mocy", 5, 5, 0, 5, PIERSCIEN, 1},

        },
        // Przedmioty dla poziomu 2
        {

            {"Miecz Wodnego Pocalunku", 10, 0, 0, 4, BRON, 50},
            {"Miecz Wodnego Pocalunku", 13, 0, 0, 5, BRON, 20},
            {"Miecz Wodnego Pocalunku", 15, 0, 0, 7, BRON, 10},
            {"Miecz Wodnego Pocalunku", 20, 0, 0, 10, BRON, 1},

            {"Topor Siepacza", 14, 0, 0, 0, BRON, 50},
            {"Topor Siepacza", 18, 0, 0, 0, BRON, 20},
            {"Topor Siepacza", 23, 0, 0, 0, BRON, 10},
            {"Topor Siepacza", 30, 0, 0, 0, BRON, 1},


            {"Helm Zagubionego Poszukiwacza", 0, 5, 0, 0, HELM, 50},
            {"Helm Zagubionego Poszukiwacza", 0, 7, 0, 0, HELM, 20},
            {"Helm Zagubionego Poszukiwacza", 0, 10, 0, 0, HELM, 10},
            {"Helm Zagubionego Poszukiwacza", 0, 15, 0, 0, HELM, 1},

            {"Pancerz Barbarzyncy", 5, 8, 0, 0, PANCERZ, 50},
            {"Pancerz Barbarzyncy", 6, 12, 0, 0, PANCERZ, 20},
            {"Pancerz Barbarzyncy", 9, 15, 0, 0, PANCERZ, 10},
            {"Pancerz Barbarzyncy", 13, 20, 0, 0, PANCERZ, 1},

            {"Rekwawice tancerza wiatru", 0, 6, 0, 2, REKAWICE, 50},
            {"Rekwawice tancerza wiatru", 0, 8, 0, 4, REKAWICE, 20},
            {"Rekwawice tancerza wiatru", 0, 9, 0, 5, REKAWICE, 10},
            {"Rekwawice tancerza wiatru", 0, 13, 0, 8, REKAWICE, 1},

            {"Pas Runicznej Ochrony", 0, 7, 0, 3, PAS, 50},
            {"Pas Runicznej Ochrony", 0, 10, 0, 3, PAS, 20},
            {"Pas Runicznej Ochrony", 0, 12, 0, 5, PAS, 10},
            {"Pas Runicznej Ochrony", 0, 16, 0, 9, PAS, 1},

            {"Spodnie Zlodziejskiego Bractwa", 0, 5, 0, 8, SPODNIE, 50},
            {"Spodnie Zlodziejskiego Bractwa", 0, 6, 0, 10, SPODNIE, 20},
            {"Spodnie Zlodziejskiego Bractwa", 0, 8, 0, 13, SPODNIE, 10},
            {"Spodnie Zlodziejskiego Bractwa", 0, 12, 0, 20, SPODNIE, 1},

            {"Buty Szybkiej Podrozy", 0, 6, 0, 8, BUTY, 50},
            {"Buty Szybkiej Podrozy", 0, 7, 0, 9, BUTY, 20},
            {"Buty Szybkiej Podrozy", 0, 10, 0, 12, BUTY, 10},
            {"Buty Szybkiej Podrozy", 0, 15, 0, 25, BUTY, 1},

            {"Pierscien Szalonego Lotrzyka", 0, 0, 5, 4, PIERSCIEN, 50},
            {"Pierscien Szalonego Lotrzyka", 0, 0, 6, 6, PIERSCIEN, 20},
            {"Pierscien Szalonego Lotrzyka", 0, 0, 8, 6, PIERSCIEN, 10},
            {"Pierscien Szalonego Lotrzyka", 0, 0, 10, 10, PIERSCIEN, 1},

            {"Amulet Zapomnianego Czarodzieja", 5, 0, 5, 0, AMULET, 50},
            {"Amulet Zapomnianego Czarodzieja", 8, 0, 5, 0, AMULET, 20},
            {"Amulet Zapomnianego Czarodzieja", 10, 0, 8, 0, AMULET, 10},
            {"Amulet Zapomnianego Czarodzieja", 15, 0, 11, 0, AMULET, 1},
        }
    };

    if (poziom <= przedmiotyNaPoziomy.size()) {
            int obecnaszerokosc = mapa.szerokoscMapy;
            int obecnawysokosc = mapa.wysokoscMapy;

            const auto& przedmiotyPoziomu = przedmiotyNaPoziomy[poziom - 1];


            set<string> dodaneNazwyPrzedmiotow;


            int maksymalnaIloscPrzedmiotow = 4 - (poziom / 5);


            vector<pair<string, float>> dostepnePrzedmioty;

            for (const auto& przedmiotInfo : przedmiotyPoziomu) {
                string nazwaBezPrzydomku = get<0>(przedmiotInfo);
                float szansaPrzedmiotu = get<6>(przedmiotInfo);

                dostepnePrzedmioty.push_back({nazwaBezPrzydomku, szansaPrzedmiotu});
            }


            while (maksymalnaIloscPrzedmiotow > 0 && !dostepnePrzedmioty.empty()) {
                // Losuj indeks przedmiotu na podstawie szansy
                float sumaSzans = 0.0f;
                for (const auto& para : dostepnePrzedmioty) {
                    sumaSzans += para.second;
                }

                float losowaLiczba = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * sumaSzans;

                int wybranyIndeks = -1;
                for (int i = 0; i < dostepnePrzedmioty.size(); ++i) {
                    losowaLiczba -= dostepnePrzedmioty[i].second;
                    if (losowaLiczba <= 0.0f) {
                        wybranyIndeks = i;
                        break;
                    }
                }


                if (wybranyIndeks != -1) {
                    string wybranaNazwa = dostepnePrzedmioty[wybranyIndeks].first;
                    float szansaPrzedmiotu = get<6>(przedmiotyPoziomu[wybranyIndeks]);


                    string przydomek = "";
                    if (szansaPrzedmiotu == 50) {
                        przydomek = "(Zwykly) ";
                    } else if (szansaPrzedmiotu == 20) {
                        przydomek = "(Magiczny) ";
                    } else if (szansaPrzedmiotu == 10) {
                        przydomek = "(Rzadki) ";
                    } else if (szansaPrzedmiotu == 1) {
                        przydomek = "(Legendarny) ";
                    }


                    wybranaNazwa = przydomek + wybranaNazwa;


                    if (dodaneNazwyPrzedmiotow.find(wybranaNazwa) == dodaneNazwyPrzedmiotow.end()) {
                        dodaneNazwyPrzedmiotow.insert(wybranaNazwa);

                        int x, y;

                        do {
                            x = rand() % (obecnaszerokosc - 1 + 1) + 1 ;
                            y = rand() % (obecnawysokosc - bylawysokosc + 2 + 1) + bylawysokosc + 2;
                        } while (!czyPolePuste(x, y));

                        przedmiot nowyPrzedmiot;
                        nowyPrzedmiot.x = x;
                        nowyPrzedmiot.y = y;
                        nowyPrzedmiot.nazwa = wybranaNazwa;
                        nowyPrzedmiot.typ = get<5>(przedmiotyPoziomu[wybranyIndeks]);
                        nowyPrzedmiot.atak = get<1>(przedmiotyPoziomu[wybranyIndeks]);
                        nowyPrzedmiot.szczescie = get<3>(przedmiotyPoziomu[wybranyIndeks]);
                        nowyPrzedmiot.zrecznosc = get<4>(przedmiotyPoziomu[wybranyIndeks]);
                        nowyPrzedmiot.obrona = get<2>(przedmiotyPoziomu[wybranyIndeks]);
                        nowyPrzedmiot.szansa = get<6>(przedmiotyPoziomu[wybranyIndeks]);

                        przedmioty.push_back(nowyPrzedmiot);
                        mapa.mapa[y][x] = nowyPrzedmiot;


                        maksymalnaIloscPrzedmiotow--;
                    }


                    dostepnePrzedmioty.erase(dostepnePrzedmioty.begin() + wybranyIndeks);
                }
            }
        }
}

void Mapa::dodajMikstureUzdrowieniaNowaMapa(Mapa &mapa, int bylawysokosc) {
    int x, y;
    int obecnaszerokosc = mapa.szerokoscMapy;
    int obecnawysokosc = mapa.wysokoscMapy;
    do {
        x = rand() % (obecnaszerokosc - 2 + 1) + 2 ;
        y = rand() % (obecnawysokosc - bylawysokosc + 1) + bylawysokosc ;
    } while (!czyPolePuste(x, y));

    przedmiot mikstura;
    mikstura.x = x;
    mikstura.y = y;
    mikstura.nazwa = "Mikstura Uzdrowienia";
    mikstura.symbol = 'H';
    mikstura.typ = MIKSTURA_UZDROWIENIA;
    mikstura.szansa = szansaMiksturyUzdrowienia;

    przedmioty.push_back(mikstura);
    mapa.mapa[y][x] = mikstura;
}



void Mapa::dodajMikstureUzdrowienia() {
    int x, y;

    do {
        x = rand() % (szerokoscMapy - 2) + 1;
        y = rand() % (wysokoscMapy - 2) + 1;
    } while (!czyPolePuste(x, y));

    przedmiot mikstura;
    mikstura.x = x;
    mikstura.y = y;
    mikstura.nazwa = "Mikstura Uzdrowienia";
    mikstura.symbol = 'H';
    mikstura.typ = MIKSTURA_UZDROWIENIA;
    mikstura.szansa = szansaMiksturyUzdrowienia;

    przedmioty.push_back(mikstura);
    mapa[y][x] = mikstura;
}

void Mapa::dodajPrzedmiot(string nazwa, float atak,float obrona,float szczescie, float zrecznosc, przedmiotTyp typ, int szansa) {
    int x, y;

       do {
           x = rand() % (szerokoscMapy - 2) + 1;
           y = rand() % (wysokoscMapy - 2) + 1;
       } while (!czyPolePuste(x, y));

    przedmiot nowyPrzedmiot;
    nowyPrzedmiot.x = x;
    nowyPrzedmiot.y = y;
    nowyPrzedmiot.nazwa = nazwa;
    nowyPrzedmiot.typ = typ;
    nowyPrzedmiot.atak = atak;
    nowyPrzedmiot.szczescie = szczescie;
    nowyPrzedmiot.zrecznosc = zrecznosc;
    nowyPrzedmiot.obrona = obrona;
    nowyPrzedmiot.szansa = szansa;
    przedmioty.push_back(nowyPrzedmiot);
    mapa[y][x] = nowyPrzedmiot;
}
bool Mapa::czyWszystkiePolaPoprawne(){
    for (int i = 0; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            char symbol = mapa[i][j].symbol;
            if (symbol != '.' && symbol != '@' && symbol != '^' &&
                symbol != '#' && symbol != ' ' && symbol != 'I') {

                mapa[i][j] = Podloga();
            }
        }
    }
    return true;
}
void Mapa::dodajPrzeciwnika(int x, int y, char symbol, string nazwa, int atak, int obrona, int zycie, float zrecznosc, float szczescie, int wartoscDoswiadczenia) {
    if (!czyPolePuste(x, y)) {
        return;
    }

    Przeciwnik nowyPrzeciwnik;
    nowyPrzeciwnik.x = x;
    nowyPrzeciwnik.y = y;
    nowyPrzeciwnik.zycieMax = zycie;
    nowyPrzeciwnik.zycie = zycie;
    nowyPrzeciwnik.zrecznosc = zrecznosc;
    nowyPrzeciwnik.szczescie = szczescie;
    nowyPrzeciwnik.nazwa = nazwa;
    nowyPrzeciwnik.atak = atak;
    nowyPrzeciwnik.symbol = symbol;
    nowyPrzeciwnik.obrona = obrona;
    nowyPrzeciwnik.wartoscDoswiadczenia = wartoscDoswiadczenia;
    przeciwnicy.push_back(nowyPrzeciwnik);
    mapa[y][x] = nowyPrzeciwnik;
}

void Mapa::generujNowaMape(Mapa &mapa) {
    mapa.poziom_mapy=mapa.poziom_mapy + 1;
    cout << "Przeszedles na nastepny poziom: "<< poziom_mapy <<endl;

    int obecnaSzerokosc = mapa.szerokoscMapy;
    int obecnaWysokosc = mapa.wysokoscMapy;


    int xPrzejscia = -1;
    int yPrzejscia = -1;

    for (int i = 0; i < obecnaWysokosc; ++i) {
        for (int j = 0; j < obecnaSzerokosc; ++j) {
            if (mapa.mapa[i][j].symbol == '^') {
                xPrzejscia = j;
                yPrzejscia = i;
                break;
            }
        }
        if (xPrzejscia != -1 && yPrzejscia != -1) {
            break;
        }
    }


    int o_ile = rand() % (17-8+1)+8;

    szerokoscMapy += o_ile;
    wysokoscMapy += o_ile;


    mapa.mapa.resize(wysokoscMapy, vector<Pole>(szerokoscMapy, Podloga()));


    for (int i = 0; i < wysokoscMapy; ++i) {
        mapa.mapa[i][0] = Sciana();
    }
    for (int i = wysokoscMapy-o_ile; i < wysokoscMapy; ++i) {
        mapa.mapa[i][szerokoscMapy - 1] = Sciana();

    }
    for (int j = 0; j < szerokoscMapy; ++j) {
        mapa.mapa[wysokoscMapy - 1][j] = Sciana();
    }


    if (yPrzejscia + 2 < wysokoscMapy) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            mapa.mapa[yPrzejscia + 2][j] = Sciana();
        }
    }

    int szansa = 50;
    int randomValue = rand() % 100;

    if(randomValue < szansa){
        mapa.dodajPokojeNowaMapa(mapa,4, obecnaWysokosc);
    }
    else {
        mapa.dodajScianyNowaMapa(mapa,20,obecnaWysokosc);
    }

    if(poziom_mapy < 2){
        mapa.ustawSymbolNajdalszegoPola();
    }
    if(poziom_mapy == 2){
        mapa.dodajPrzeciwnikaLosowo(Boss(),1);
    }

    if (xPrzejscia != -1 && yPrzejscia != -1) {
        int removeWallX = xPrzejscia;
        int removeWallY1_1 = yPrzejscia -1;
        int removeWallY2_1 = yPrzejscia-2;
        int removeWallY3_1 = yPrzejscia-3;        
        int removeWallY1 = yPrzejscia + 1;
        int removeWallY2 = yPrzejscia + 2;
        int removeWallY3 = yPrzejscia + 3;


        if (removeWallY1 < wysokoscMapy && removeWallY2 < wysokoscMapy && removeWallX >= 0 && removeWallX < szerokoscMapy) {
            mapa.mapa[removeWallY1][removeWallX] = Podloga();
            mapa.mapa[removeWallY2][removeWallX] = Podloga();
            mapa.mapa[removeWallY3][removeWallX] = Podloga();            
            mapa.mapa[removeWallY1_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY2_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY3_1][removeWallX] = Podloga();

        }
    }
    mapa.dodajPrzedmiotyNaNowymPoziomie(mapa.poziom_mapy, mapa, obecnaWysokosc);
    mapa.dodajPrzeciwnikowLosowoNowaMapa(mapa.poziom_mapy, mapa, obecnaWysokosc);
    mapa.dodajMikstureUzdrowieniaNowaMapa(mapa, obecnaWysokosc);

}


void Mapa::przesunGracza(char kierunek, Mapa &mapa, Gracz &gracz) {
    int nowyX = gracz.x;
       int nowyY = gracz.y;

       switch (kierunek) {
           case 'w':
               nowyY--;
               break;
           case 's':
               nowyY++;
               break;
           case 'a':
               nowyX--;
               break;
           case 'd':
               nowyX++;
               break;
           case 'f':
               podniesPrzedmiot(gracz);
               break;
           case 'r':
               potrzebneWyswietlanie = false;
               cout << "Ktory przedmiot sciagnac: ";
               int indee;
               cin >> indee;
               gracz.plecak.sciagnijPrzedmiotZEkwipunku(indee, gracz);
               potrzebneWyswietlanie = true;
               break;
           case 'e':
               cout << "Ktory przedmiot zalozyc: ";
               int inde;
               cin >> inde;
               gracz.plecak.zalozPrzedmiotZPlecaka(inde, gracz);
               break;
           case 'u':
               potrzebneWyswietlanie = false;
               cout << "Ktory przedmiot usunac: ";
               int indeks;
               cin >> indeks;
               gracz.plecak.usunPrzedmiot(indeks);
               system("Pause");
               potrzebneWyswietlanie = true;
               break;
            case 'p':
               potrzebneWyswietlanie = false;
               gracz.wyswietlStatystyki();
               system("Pause");
               potrzebneWyswietlanie = true;
               break;
            case 'q':
               potrzebneWyswietlanie = false;
               gracz.plecak.wyswietlPlecakIEkwipunek();
               system("Pause");
               potrzebneWyswietlanie = true;
               break;
            case 'b':
               potrzebneWyswietlanie = false;
               cout << "Ktora miksture uzdrowienia chcesz uzyc? Podaj indeks z plecaka: ";
               int indeksMikstury;
               cin >> indeksMikstury;

               if (indeksMikstury >= 0 && indeksMikstury < gracz.plecak.zawartosc.size() &&
                   gracz.plecak.zawartosc[indeksMikstury].typ == MIKSTURA_UZDROWIENIA) {
               // Uzyskaj referencję do mikstury z plecaka
               przedmiot &mikstura = gracz.plecak.zawartosc[indeksMikstury];

               // Przywróć zdrowie graczowi
               gracz.przywrocZycie();

               // Usuń miksturę z plecaka
               gracz.plecak.usunPrzedmiot(indeksMikstury);

               cout << "Uzyto mikstury uzdrowienia." << endl;
               }
               else {
               cout << "Nieprawidlowy indeks mikstury lub to nie jest mikstura uzdrowienia." << endl;
               }

               system("Pause");
               potrzebneWyswietlanie = true;
               break;
            case 'h':
               potrzebneWyswietlanie = false;
               gracz.Pomoc();
               system("Pause");
               potrzebneWyswietlanie = true;
               break;
           case 'l':
               cout << "ile : ";
               int ile;
               cin >> ile;
               testujWalkiWielokrotnie(ile);
               break;
           default:
               return;
       }


       if (czyMoznaPrzejsc(nowyX, nowyY)) {
           potrzebneWyswietlanie = true;
           mapa.mapa[gracz.y][gracz.x] = Podloga();


           gracz.x = nowyX;
           gracz.y = nowyY;


           if (mapa.mapa[gracz.y][gracz.x].symbol == '^') {

               generujNowaMape(mapa);
               mapa.mapa[gracz.y][gracz.x] = gracz;
               potrzebneWyswietlanie = true;

           } else {

               mapa.mapa[gracz.y][gracz.x] = gracz;
               potrzebneWyswietlanie = true;
           }
       }
       else {
           wyswietl();
           przesunZAutomatycznymAtakiem(gracz, nowyX, nowyY);
           gracz.wTrakcieWalki = true;
           potrzebneWyswietlanie = false;
       }


       if (potrzebneWyswietlanie) {
           for (int i = 0; i < 30; i++) {
               cout << endl;
           }
           wyswietl();
           gracz.plecak.wyswietlZawartosc();
           gracz.plecak.wyswietlZawartoscEkwipunek();
           gracz.wyswietlInfo();
       }

 }

void Mapa::przesunZAutomatycznymAtakiem(Gracz &gracz, int nowyX, int nowyY) {

    if (czyIstniejePrzeciwnik(nowyX, nowyY)) {
        atakujPrzeciwnika(gracz, nowyX, nowyY);
    } else {
        mapa[gracz.y][gracz.x] = gracz;
    }
}

void Mapa::podniesPrzedmiot(Gracz &gracz) {
    potrzebneWyswietlanie = true;
    int x = gracz.x;
    int y = gracz.y;

    if (x - 1 >= 0 && (mapa[y][x - 1].symbol == 'I' || mapa[y][x - 1].symbol == 'H')) {
        podniesPrzedmiotNaPozycji(x - 1, y, gracz);
    } else if (x + 1 < szerokoscMapy && (mapa[y][x + 1].symbol == 'I' || mapa[y][x + 1].symbol == 'H')) {
        podniesPrzedmiotNaPozycji(x + 1, y, gracz);
    } else if (y - 1 >= 0 && (mapa[y - 1][x].symbol == 'I' || mapa[y - 1][x].symbol == 'H')) {
        podniesPrzedmiotNaPozycji(x, y - 1, gracz);
    } else if (y + 1 < wysokoscMapy && (mapa[y + 1][x].symbol == 'I' || mapa[y + 1][x].symbol == 'H')) {
        podniesPrzedmiotNaPozycji(x, y + 1, gracz);
    } else {
        cout << "Nie ma przedmiotu w zasięgu." << endl;
        system("Pause");
    }
}

void Mapa::podniesPrzedmiotNaPozycji(int x, int y, Gracz &gracz) {
    potrzebneWyswietlanie = true;
    if (gracz.plecak.zawartosc.size() < 6) {

        for (auto it = przedmioty.begin(); it != przedmioty.end();) {
            if (it->x == x && it->y == y) {

                gracz.plecak.dodajPrzedmiot(*it);


                it = przedmioty.erase(it);
            } else {
                ++it;
            }
        }


        setPole(x, y, Podloga().symbol);
    } else {

        cout << "Plecak jest pelny. Nie można podniesc wiecej przedmiotow." << endl;
        system("Pause");
    }
}

void Mapa::setPole(int x, int y, char symbol) {
    mapa[y][x].symbol = symbol;
}

void Mapa::przetworzRuchPrzeciwnika(Gracz &gracz, int przeciwnikIndex, int miejsceX, int miejsceY, Mapa &mapa) {
    int przeciwnikX, przeciwnikY;

    przeciwnikX = przeciwnicy[przeciwnikIndex].x;
    przeciwnikY = przeciwnicy[przeciwnikIndex].y;

    Pole poleRuchu = mapa.mapa[miejsceY][miejsceX];


    if (mapa.mapa[miejsceY][miejsceX].symbol == '#') {
        return;
    }
    else if (mapa.mapa[miejsceY][miejsceX].symbol == 'I') {
        return;
    }
    else if (poleRuchu.symbol == '.') {

        setPole(przeciwnikX, przeciwnikY, '.');


        przeciwnicy[przeciwnikIndex].x = miejsceX;
        przeciwnicy[przeciwnikIndex].y = miejsceY;


        setPole(miejsceX, miejsceY, przeciwnicy[przeciwnikIndex].symbol);

    }
    else if (poleRuchu.symbol == '@') {
        atak(gracz);
        system("Pause");
        potrzebneWyswietlanie = true;
    }

}

void Mapa::aktualizujPotwory(Gracz &gracz, Mapa &mapa) {
    char aiRuch;
    int przeciwnikX, przeciwnikY;


    for(unsigned int i = 0; i < przeciwnicy.size(); i++){
        aiRuch = przeciwnicy[i].dostanRuch(gracz);
        przeciwnikX = przeciwnicy[i].x;
        przeciwnikY = przeciwnicy[i].y;


        switch(aiRuch){
        case 'w':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX, przeciwnikY - 1, mapa);
            break;
        case 's':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX, przeciwnikY + 1, mapa);
            break;
        case 'a':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX - 1, przeciwnikY, mapa);
            break;
        case 'd':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX + 1, przeciwnikY, mapa);
            break;
      }

    }

}

bool Mapa::czyMoznaPrzejsc(int x, int y) {

    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }


    if (mapa[y][x].symbol == '#') {
        return false;
    }


    for (const przedmiot& p : przedmioty) {
        if (p.x == x && p.y == y) {
            return false;
        }
    }
    for (const Przeciwnik& e : przeciwnicy) {
        if (e.x == x && e.y == y) {
            return false;
        }
    }
    return true;
}

bool Mapa::czyIstniejePrzedmiot(int x, int y, Mapa &mapa) {
    return x >= 0 && x < mapa.szerokoscMapy && y >= 0 && y < mapa.wysokoscMapy &&
           mapa.mapa[y][x].symbol == 'I';
}

void Mapa::atak(Gracz &gracz) {
    int graczX = gracz.x;
    int graczY = gracz.y;


    if (czyIstniejePrzeciwnik(graczX - 1, graczY)) {
        atakujPrzeciwnika(gracz, graczX - 1, graczY);
    }

    else if (czyIstniejePrzeciwnik(graczX + 1, graczY)) {
        atakujPrzeciwnika(gracz, graczX + 1, graczY);
    }

    else if (czyIstniejePrzeciwnik(graczX, graczY - 1)) {
        atakujPrzeciwnika(gracz, graczX, graczY - 1);
    }

    else if (czyIstniejePrzeciwnik(graczX, graczY + 1)) {
        atakujPrzeciwnika(gracz, graczX, graczY + 1);
    }
    else {
        cout << "Nie ma przeciwnika w zasiegu." << endl;
    }
}

void Mapa::atakujPrzeciwnika(Gracz &gracz, int celX, int celY) {
    string nazwaPrzeciwnika;
    int ileObrazen, atakRoll, zyciePrzedGracz , zyciePrzedPrzeciwnik;


    for (unsigned int i = 0; i < przeciwnicy.size(); i++) {
        if (przeciwnicy[i].x == celX && przeciwnicy[i].y == celY) {
            nazwaPrzeciwnika = przeciwnicy[i].nazwa;          
            cout << "\n";
            if(nazwaPrzeciwnika == "Lodowy Zywiolak"){
                przeciwnicy[i].czyNeutralny = false;
            }
            cout << "TURA GRACZA: " << endl;
            if(przeciwnicy[i].szansaUniuku(przeciwnicy[i].zrecznosc)){
                cout << "Bohater chybil " << przeciwnicy[i].nazwa << " nie zadajac obrazen " << "\n";
            }
            else if(gracz.szansaKryta(gracz.dostanSzczescie())){
                atakRoll = gracz.obrazenia();
                zyciePrzedPrzeciwnik = przeciwnicy[i].zycie;
                ileObrazen = przeciwnicy[i].dostanObrazenia(atakRoll*2);
                cout << "Bohater trafil krytycznie " << przeciwnicy[i].nazwa << " zadajac: " << abs(zyciePrzedPrzeciwnik-przeciwnicy[i].zycie) << " obrazen" << "\n";
            }
            else {
            atakRoll = gracz.obrazenia();
            zyciePrzedPrzeciwnik = przeciwnicy[i].zycie;
            ileObrazen = przeciwnicy[i].dostanObrazenia(atakRoll);
            cout << "Bohater zaatakowal " << nazwaPrzeciwnika << " zadajac: " << abs(zyciePrzedPrzeciwnik - przeciwnicy[i].zycie) << " obrazen" << "\n";
            if (ileObrazen != 0) {

                setPole(celX, celY, '.');
                cout << nazwaPrzeciwnika << " zginal" << "\n";


                przeciwnicy[i] = przeciwnicy.back();
                przeciwnicy.pop_back();
                i--;

                gracz.dostanDoswiadczenie(ileObrazen);
                gracz.wTrakcieWalki = false;
                potrzebneWyswietlanie = true;
                return;
            }
            }
            // Tura przeciwnika
            cout << "\n";
            cout << "TURA PRZECIWNIKA: " << endl;
            if(gracz.szansaUniuku(gracz.dostanZrecznosc())){
                cout << przeciwnicy[i].nazwa << " chybil " << " nie zadajac obrazen " << "\n";
            }
            else if(przeciwnicy[i].szansaKryta(przeciwnicy[i].szczescie)){
                atakRoll = przeciwnicy[i].obrazenia();
                zyciePrzedGracz = gracz.dostanZycie();
                ileObrazen = gracz.dostanObrazenia(atakRoll*2);
                cout <<przeciwnicy[i].nazwa << " trafil krytycznie zadajac: " << abs(zyciePrzedGracz-gracz.dostanZycie()) << " obrazen" << "\n";
            }
            else {
            atakRoll = przeciwnicy[i].obrazenia();
            zyciePrzedGracz = gracz.dostanZycie();
            ileObrazen = gracz.dostanObrazenia(atakRoll);
            cout << nazwaPrzeciwnika << " zaatakowal bohater zadajac: " << abs(zyciePrzedGracz - gracz.dostanZycie()) << " obrazen" << "\n";

            if (ileObrazen != 0) {

                setPole(gracz.x, gracz.y, 'X');
                cout << "Bohater zginal" << "\n";
                gracz.ekran_koncowy();
                system("PAUSE");
                exit(0);
            }
            }
            cout << "\n";
            cout << "Zycie bohatera: " << gracz.dostanZycie() << endl;
            cout << "\n";

            return;
        }
    }
}

bool Mapa::czyIstniejePrzeciwnik(int x, int y) {

    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }


    for (const Przeciwnik& p : przeciwnicy) {
        if (p.x == x && p.y == y) {
            return true;
        }
    }

    return false;
}

bool Mapa::czyPolePuste(int x, int y) {

    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }


    if (mapa[y][x].symbol != '.' ) {
        return false;
    }

    return true;
}


void Mapa::testujWalkiWielokrotnie(int iloscTestow) {
    srand(static_cast<unsigned>(time(nullptr)));


        std::cout << "Wybierz przeciwnika:" << std::endl;
        std::cout << "1. Ogr" << std::endl;
        std::cout << "2. Goblin" << std::endl;
        std::cout << "3. Szczur" << std::endl;
        std::cout << "4. Zombi" << std::endl;
        std::cout << "5. Zywiolak" << std::endl;

        int wybor;
        std::cin >> wybor;
        int ileObrazen, zyciePrzedGracz, zyciePrzedPrzeciwnik;
        int atakRoll;
        Przeciwnik* przeciwnik = nullptr;
        int wygraneBohater = 0;
        int unikiPrzeciwnik = 0;
        int wygranePrzeciwnik = 0;
        int unikiGracz = 0;
        int krytGracz = 0;
        int krytPrzeciwnik = 0;

        for (int i = 0; i < iloscTestow; ++i) {

            Gracz gracz;
            gracz.inicjalizajca(1, 50, 15, 10, 10, 10, 50);

            switch (wybor) {
                case 1:
                    przeciwnik = new Ogr();
                    break;
                case 2:
                    przeciwnik = new Goblin();
                    break;
                case 3:
                    przeciwnik = new Szczur();
                    break;
                case 4:
                    przeciwnik = new Zombi();
                    break;
                case 5:
                    przeciwnik = new Zywiolak();
                    break;
                default:
                    std::cout << "Zly wybor. wychodze z testowania walki." << std::endl;
                    return;
            }



            std::cout << "Walka " << i + 1 << ":\n";
            std::cout << "Bohater: " << gracz.dostanZycie() << " HP\n";
            std::cout << "Przeciwnik: " << przeciwnik->zycie << " HP\n\n";

            // Przeprowadź walkę
            while (gracz.dostanZycie() > 0 && przeciwnik->zycie > 0) {
                if(przeciwnik->szansaUniuku(przeciwnik->zrecznosc)){
                    cout << "Bohater chybil " << przeciwnik->nazwa << "  nie zadajac obrazen " << "\n";
                    ++unikiPrzeciwnik;
                }
                else if(gracz.szansaKryta(gracz.dostanSzczescie())){
                    atakRoll = gracz.obrazenia();
                    zyciePrzedPrzeciwnik = przeciwnik->zycie;
                    ileObrazen = przeciwnik->dostanObrazenia(atakRoll*2);
                    cout << "Bohater trafil krytycznie " << przeciwnik->nazwa << " zadajac: " << abs(zyciePrzedPrzeciwnik-przeciwnik->zycie) << " obrazen" << "\n";
                    krytGracz++;
                }
                else {
                atakRoll = gracz.obrazenia();
                zyciePrzedGracz = gracz.dostanZycie();
                zyciePrzedPrzeciwnik = przeciwnik->zycie;
                ileObrazen = przeciwnik->dostanObrazenia(atakRoll);
                cout << "Bohater zaatakowal " << przeciwnik->nazwa << " zadajac: " << abs(zyciePrzedPrzeciwnik-przeciwnik->zycie) << " obrazen" << "\n";
                }
                if(gracz.szansaUniuku(gracz.dostanZrecznosc())){
                cout << przeciwnik->nazwa << " chybil " << "  nie zadajac obrazen " << "\n";
                    ++unikiGracz;
                }
                else if(przeciwnik->szansaKryta(przeciwnik->szczescie)){
                    atakRoll = przeciwnik->obrazenia();
                    zyciePrzedPrzeciwnik = przeciwnik->zycie;
                    ileObrazen = gracz.dostanObrazenia(atakRoll*2);
                    cout << "Bohater trafil krytycznie " << przeciwnik->nazwa << " zadajac: " << abs(zyciePrzedPrzeciwnik-przeciwnik->zycie) << " obrazen" << "\n";
                    krytPrzeciwnik++;
                }
                else {
                atakRoll = przeciwnik->obrazenia();
                ileObrazen = gracz.dostanObrazenia(atakRoll);
                cout << przeciwnik->nazwa << " zaatakowal gracza zadajac: " << abs(zyciePrzedGracz - gracz.dostanZycie()) << " obrazen" << "\n";
                }

                std::cout << "Stan walki:\n";                
                std::cout << "Bohater: " << gracz.dostanZycie() << " HP\n";
                std::cout << przeciwnik->nazwa << ": " << przeciwnik->zycie << " HP\n\n";


            }

            if (gracz.dostanZycie() <= 0) {
                std::cout << "Bohater zginął.\n";
                ++wygranePrzeciwnik;
            } else {
                std::cout << "Bohater pokonał przeciwnika.\n\n";
                ++wygraneBohater;
            }

        }
        cout <<  "Wygrane bohater: " << wygraneBohater << endl;
        cout <<  "Uniki "<< "Bohater" << ": " << unikiGracz << endl;
        cout <<  "Trafienia krytyczne "<< "Bohater" << ": " << krytGracz << endl;
        cout <<  "Wygrane "<< przeciwnik->nazwa<< ": " << wygranePrzeciwnik << endl;
        cout <<  "Uniki "<< przeciwnik->nazwa<< ": " << unikiPrzeciwnik << endl;
        cout <<  "Trafienia krytyczne "<< przeciwnik->nazwa << " : " << krytPrzeciwnik << endl<<endl;

        delete przeciwnik;
    }

void Mapa::floodFill(int x, int y, char symbol) {

    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return;
    }


    if (mapa[y][x].symbol == '.' || mapa[y][x].symbol == 'I' || czyIstniejePrzeciwnik(x, y)) {

        mapa[y][x].symbol = '^';


        floodFill(x - 1, y, symbol);
        floodFill(x + 1, y, symbol);
        floodFill(x, y - 1, symbol);
        floodFill(x, y + 1, symbol);
    }
}

void Mapa::floodFillPrzejscie(int x, int y, int &maxKroki, int &maxX, int &maxY, int kroki) {

    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return;
    }


    if (mapa[y][x].symbol != '.' && mapa[y][x].symbol != 'I' && !czyIstniejePrzeciwnik(x, y)) {
        return;
    }


    mapa[y][x] = Przejscie();


    if (kroki > maxKroki) {
        maxKroki = kroki;
        maxX = x;
        maxY = y;
    }


    floodFillPrzejscie(x - 1, y, maxKroki, maxX, maxY, kroki + 1);
    floodFillPrzejscie(x + 1, y, maxKroki, maxX, maxY, kroki + 1);
    floodFillPrzejscie(x, y - 1, maxKroki, maxX, maxY, kroki + 1);
    floodFillPrzejscie(x, y + 1, maxKroki, maxX, maxY, kroki + 1);
}

bool Mapa::sprawdzDostepnosc() {
    int x = 0, y = 0;
    for (int i = 0; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            if (mapa[i][j].symbol == '@') {
                x = j;
                y = i;
                break;
            }
        }
    }


    floodFill(x, y, '@');

    for (int i = 0; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            if (mapa[i][j].symbol == '^') {
                mapa[i][j].symbol = '.';
            }
        }
    }


    int maxKroki = 0, maxX = 0, maxY = 0;
    floodFillPrzejscie(x, y, maxKroki, maxX, maxY, 0);


    if (maxKroki > 0) {
        mapa[15][15].symbol = '!';
    }


    return true;
}

bool Mapa::czyObszarPusty(int x, int y, int szerokosc, int wysokosc) {

    if (x < 0 || x + szerokosc >= szerokoscMapy || y < 0 || y + wysokosc >= wysokoscMapy) {
        return false;
    }


    for (int j = y; j < y + wysokosc; ++j) {
        for (int k = x; k < x + szerokosc; ++k) {
            if (mapa[j][k].symbol != '.') {
                return false;
            }
        }
    }

    return true;
}
void Mapa::wyswietl() {
    for (int i = 0; i < 20; i++){
        cout << endl;
    }
    cout<<"Pomoc odnosnie komend: 'h'" << endl;
    for ( auto& row : mapa) {
        for (auto& pole : row) {
            cout << pole.symbol;
        }
        cout << endl;
    }

}
