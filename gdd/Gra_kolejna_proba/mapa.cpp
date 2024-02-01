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

    int szerokosc = rand() % 21 + 10;
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
    dodajPokoje(1);

    dodajPrzeciwnikaLosowo(Szczur(),1);



}

void Mapa::ustawSymbolNajdalszegoPola() {
    // Znajdź pozycję gracza na mapie
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

    // Znajdź najdalsze pole od gracza
    int maxKroki = 0, maxX = 0, maxY = 0;

    for (int i = 0; i < wysokoscMapy; ++i) {
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

    // Oznacz najdalsze pole jako '^'
    if (maxKroki > 0) {
        mapa[maxY][maxX] = Przejscie();
    }
}
void Mapa::dodajSciany(int ilosc) {
    // Dodaj ilość ścian na losowych pozycjach
    for (int i = 0; i < ilosc; ++i) {
        int x = rand() % (szerokoscMapy - 2) + 1;
        int y = rand() % (wysokoscMapy - 2) + 1;

        // Sprawdź, czy pole jest puste
        if (czyPolePuste(x, y)) {
            mapa[y][x] = Sciana();
        } else {
            --i; // Jeśli pole nie jest puste, spróbuj ponownie dla innego losowego miejsca
        }
    }
}
void Mapa::dodajPokoje(int ilosc) {
    for (int i = 0; i < ilosc; ++i) {
        // Losuj rozmiary pokoju
        int szerokoscPokoju = rand() % 20 + 1;
        int wysokoscPokoju = rand() % 10 + 1;

        // Losuj pozycję dla górnego lewego rogu pokoju
        int x = rand() % (szerokoscMapy - szerokoscPokoju - 2) + 1;
        int y = rand() % (wysokoscMapy - wysokoscPokoju - 2) + 1;

        // Sprawdź, czy obszar pokoju jest pusty
        if (czyObszarPusty(x, y, szerokoscPokoju, wysokoscPokoju)) {
            // Dodaj pokoje
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
            --i; // Jeśli obszar nie jest pusty, spróbuj ponownie dla innego losowego miejsca
        }
    }
}
void Mapa::dodajLas(int ilosc) {
    for (int i = 0; i < ilosc; ++i) {
        // Losuj pozycję dla lewego górnego rogu lasu
        int x = rand() % (szerokoscMapy+10) + 1;
        int y = rand() % (wysokoscMapy+20) + 1;

        // Losuj długość lasu (kwadratu)
        int rozmiarLasu = rand() % (10 - 5 + 1) + 2;

        // Dodaj las
        for (int j = y; j < y + rozmiarLasu; ++j) {
            for (int k = x; k < x + rozmiarLasu; ++k) {
                if (czyPolePuste(k, j)) {
                    if (j == y + rozmiarLasu / 3 || j == y + (2 * rozmiarLasu) / 3 ||
                        k == x + rozmiarLasu / 3 || k == x + (2 * rozmiarLasu) / 3) {
                        mapa[j][k] = Podloga();
                    } else {
                        mapa[j][k] = Sciana();
                    }
                }
            }
        }
    }
}

void Mapa::dodajGracza(int x, int y, Gracz &gracz) {
    x = rand() % (szerokoscMapy - 2) + 1; // losowa pozycja wzdłuż osi x
    y = rand() % 3 + 1;  // losowa pozycja na górnym obszarze mapy (np. w pierwszych trzech rzędach)

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

            // Dodaj stworzonego przeciwnika do wektora przeciwnicy
            przeciwnicy.push_back(przeciwnik);
        } else {
            --k;
        }
        }
    }
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
                // Jeżeli symbol nie pasuje do żadnej z obsługiwanych klas, zastąp go kropką
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
    cout<<"Przeszedles na nastepny poziom"<< poziom_mapy<<endl;

    int obecnaSzerokosc = mapa.szerokoscMapy;
    int obecnaWysokosc = mapa.wysokoscMapy;

    // Znajdź symbol '^' na mapie
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




    szerokoscMapy += 10;
    wysokoscMapy += 10;


    mapa.mapa.resize(wysokoscMapy, vector<Pole>(szerokoscMapy, Podloga()));

    for (int i = 0; i < wysokoscMapy; ++i) {
        mapa.mapa[i][0] = Sciana();
    }
    for (int i = wysokoscMapy-10; i < wysokoscMapy; ++i) {
        mapa.mapa[i][szerokoscMapy - 1] = Sciana();

    }
    for (int j = 0; j < szerokoscMapy; ++j) {
        mapa.mapa[wysokoscMapy - 1][j] = Sciana();
    }

    // Dodaj ściany dwa poziomy poniżej symbolu '^'
    if (yPrzejscia + 2 < wysokoscMapy) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            mapa.mapa[yPrzejscia + 2][j] = Sciana();
        }
    }

    int szansa = 50;
    int randomValue = rand() % 100;

    if(randomValue < szansa){
        mapa.dodajPokoje(4);
    }
    else {
        mapa.dodajSciany(50);
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
        int removeWallY4_1 = yPrzejscia-4;
        int removeWallY5_1 = yPrzejscia-5;
        int removeWallY6_1 = yPrzejscia-6;
        int removeWallY1 = yPrzejscia + 1;
        int removeWallY2 = yPrzejscia + 2;
        int removeWallY3 = yPrzejscia + 3;
        int removeWallY4 = yPrzejscia + 4;
        int removeWallY5 = yPrzejscia + 5;
        int removeWallY6 = yPrzejscia + 6;

        if (removeWallY1 < wysokoscMapy && removeWallY2 < wysokoscMapy && removeWallX >= 0 && removeWallX < szerokoscMapy) {
            mapa.mapa[removeWallY1][removeWallX] = Podloga();
            mapa.mapa[removeWallY2][removeWallX] = Podloga();
            mapa.mapa[removeWallY3][removeWallX] = Podloga();
            mapa.mapa[removeWallY4][removeWallX] = Podloga();
            mapa.mapa[removeWallY5][removeWallX] = Podloga();
            mapa.mapa[removeWallY6][removeWallX] = Podloga();
            mapa.mapa[removeWallY1_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY2_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY3_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY4_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY5_1][removeWallX] = Podloga();
            mapa.mapa[removeWallY6_1][removeWallX] = Podloga();
        }
    }
    mapa.dodajPrzeciwnikaLosowo(Goblin(),2);
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
               cout << "Ktory: ";
               int indee;
               cin >> indee;
               gracz.plecak.sciagnijPrzedmiotZEkwipunku(indee, gracz);
               break;
           case 'e':
               cout << "Ktory: ";
               int inde;
               cin >> inde;
               gracz.plecak.zalozPrzedmiotZPlecaka(inde, gracz);
               break;
           case 'u':
               cout << "Ktory: ";
               int indeks;
               cin >> indeks;
               gracz.plecak.usunPrzedmiot(indeks);
               break;
           case 'l':
               cout << "ile : ";
               int ile;
               cin >> ile;
               testujWalkiWielokrotnie(ile);
               break;
           default:
               return; // Ignoruj nieznane komendy
       }

       // Sprawdź, czy nowa pozycja jest poprawna
       if (czyMoznaPrzejsc(nowyX, nowyY)) {
           // Usuń gracza z obecnej pozycji
           mapa.mapa[gracz.y][gracz.x] = Podloga();

           // Przesuń gracza na nową pozycję
           gracz.x = nowyX;
           gracz.y = nowyY;

           // Sprawdź, czy gracz wszedł na pole "^"
           if (mapa.mapa[gracz.y][gracz.x].symbol == '^') {
               // Jeżeli tak, generuj nową mapę
               generujNowaMape(mapa);

           } else {
               // W przeciwnym razie, umieść gracza na nowej pozycji
               mapa.mapa[gracz.y][gracz.x] = gracz;
           }
       } else {
           // Jeżeli nowa pozycja nie jest poprawna, przesuń z automatycznym atakiem
           przesunZAutomatycznymAtakiem(gracz, nowyX, nowyY);
           gracz.wTrakcieWalki = true;
       }

       // Wyswietl nową mapę i inne informacje
       wyswietl();
       gracz.plecak.wyswietlZawartosc();
       gracz.plecak.wyswietlZawartoscEkwipunek();
       gracz.wyswietlStatystyki();
 }

void Mapa::przesunZAutomatycznymAtakiem(Gracz &gracz, int nowyX, int nowyY) {
    // Sprawdź, czy na nowej pozycji jest przeciwnik
    if (czyIstniejePrzeciwnik(nowyX, nowyY)) {
        atakujPrzeciwnika(gracz, nowyX, nowyY);
    } else {
        mapa[gracz.y][gracz.x] = gracz;
    }
}

void Mapa::podniesPrzedmiot(Gracz &gracz) {
    int x = gracz.x;
    int y = gracz.y;

    // Sprawdź, czy istnieje przedmiot na lewo od gracza
    if (x - 1 >= 0 && mapa[y][x - 1].symbol == 'I') {
        podniesPrzedmiotNaPozycji(x - 1, y, gracz);
    }
    // Sprawdź, czy istnieje przedmiot na prawo od gracza
    else if (x + 1 < szerokoscMapy && mapa[y][x + 1].symbol == 'I') {
        podniesPrzedmiotNaPozycji(x + 1, y, gracz);
    }
    // Sprawdź, czy istnieje przedmiot powyżej gracza
    else if (y - 1 >= 0 && mapa[y - 1][x].symbol == 'I') {
        podniesPrzedmiotNaPozycji(x, y - 1, gracz);
    }
    // Sprawdź, czy istnieje przedmiot poniżej gracza
    else if (y + 1 < wysokoscMapy && mapa[y + 1][x].symbol == 'I') {
        podniesPrzedmiotNaPozycji(x, y + 1, gracz);
    } else {
        // Komunikat, jeśli nie znaleziono przedmiotu w zasięgu
        cout << "Nie ma przedmiotu w zasięgu." << endl;
    }
}

void Mapa::podniesPrzedmiotNaPozycji(int x, int y, Gracz &gracz) {
    // Sprawdź, czy plecak gracza ma jeszcze miejsce
    if (gracz.plecak.zawartosc.size() < 6) {
        // Przeszukaj przedmioty na danej pozycji
        for (auto it = przedmioty.begin(); it != przedmioty.end();) {
            if (it->x == x && it->y == y) {
                // Dodaj przedmiot do plecaka gracza
                gracz.plecak.dodajPrzedmiot(*it);

                // Usuń przedmiot z mapy
                it = przedmioty.erase(it);
            } else {
                ++it;
            }
        }

        // Ustaw symbol na mapie (możesz dostosować do własnych potrzeb)
        setPole(x, y, Podloga().symbol);
    } else {
        // Komunikat, jeśli plecak jest pełny
        cout << "Plecak jest pełny. Nie można podnieść więcej przedmiotów." << endl;
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
        system("PAUSE");
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
    // Sprawdź, czy pozycja nie wychodzi poza granice mapy
    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }

    // Sprawdź, czy na danej pozycji jest ściana
    if (mapa[y][x].symbol == '#') {
        return false;
    }

    // Sprawdź, czy na danej pozycji jest przedmiot
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

    // Sprawdź, czy istnieje przeciwnik na lewo
    if (czyIstniejePrzeciwnik(graczX - 1, graczY)) {
        atakujPrzeciwnika(gracz, graczX - 1, graczY);
    }
    // Sprawdź, czy istnieje przeciwnik na prawo
    else if (czyIstniejePrzeciwnik(graczX + 1, graczY)) {
        atakujPrzeciwnika(gracz, graczX + 1, graczY);
    }
    // Sprawdź, czy istnieje przeciwnik u góry
    else if (czyIstniejePrzeciwnik(graczX, graczY - 1)) {
        atakujPrzeciwnika(gracz, graczX, graczY - 1);
    }
    // Sprawdź, czy istnieje przeciwnik na dole
    else if (czyIstniejePrzeciwnik(graczX, graczY + 1)) {
        atakujPrzeciwnika(gracz, graczX, graczY + 1);
    }
    else {
        cout << "Nie ma przeciwnika w zasięgu." << endl;
    }
}

void Mapa::atakujPrzeciwnika(Gracz &gracz, int celX, int celY) {
    string nazwaPrzeciwnika;
    int ileObrazen, atakRoll, zyciePrzedGracz , zyciePrzedPrzeciwnik;

    // Znajdź przeciwnika na danej pozycji
    for (unsigned int i = 0; i < przeciwnicy.size(); i++) {
        if (przeciwnicy[i].x == celX && przeciwnicy[i].y == celY) {
            nazwaPrzeciwnika = przeciwnicy[i].nazwa;
            cout << "\n";
            gracz.wyswietlStatystyki();
            cout << "\n";
            if(nazwaPrzeciwnika == "Lodowy Zywiolak"){
                przeciwnicy[i].czyNeutralny = false;
            }
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
                // Zaktualizuj pole na mapie (zmień symbol na kropkę)
                setPole(celX, celY, '.');
                cout << nazwaPrzeciwnika << " zginal" << "\n";

                // Usuń przeciwnika z listy
                przeciwnicy[i] = przeciwnicy.back();
                przeciwnicy.pop_back();
                i--;

                gracz.dostanDoswiadczenie(ileObrazen);
                gracz.wTrakcieWalki = false;
                return;
            }
            }
            // Tura przeciwnika
            cout << "\n";
            przeciwnicy[i].wyswietlStatystyki();
            cout << "\n";
            if(gracz.szansaUniuku(gracz.dostanZrecznosc())){
                cout << przeciwnicy[i].nazwa << " chybil " << "  nie zadajac obrazen " << "\n";
            }
            else if(przeciwnicy[i].szansaKryta(przeciwnicy[i].szczescie)){
                atakRoll = przeciwnicy[i].obrazenia();
                zyciePrzedPrzeciwnik = przeciwnicy[i].zycie;
                ileObrazen = gracz.dostanObrazenia(atakRoll*2);
                cout <<przeciwnicy[i].nazwa << " trafil krytycznie zadajac: " << abs(zyciePrzedPrzeciwnik-przeciwnicy[i].zycie) << " obrazen" << "\n";
            }
            else {
            atakRoll = przeciwnicy[i].obrazenia();
            zyciePrzedGracz = gracz.dostanZycie();
            ileObrazen = gracz.dostanObrazenia(atakRoll);
            cout << nazwaPrzeciwnika << " zaatakowal gracza zadajac: " << abs(zyciePrzedGracz - gracz.dostanZycie()) << " obrazen" << "\n";

            if (ileObrazen != 0) {
                // Zaktualizuj pole na mapie (zmień symbol na X)
                setPole(gracz.x, gracz.y, 'X');
                cout << "Bohater zginal" << "\n";
                system("PAUSE");
                exit(0);
            }
            }

            return;
        }
    }
}

bool Mapa::czyIstniejePrzeciwnik(int x, int y) {
    // Sprawdź, czy pozycja nie wychodzi poza granice mapy
    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }

    // Sprawdź, czy na danej pozycji jest przeciwnik
    for (const Przeciwnik& p : przeciwnicy) {
        if (p.x == x && p.y == y) {
            return true;
        }
    }

    return false;
}

bool Mapa::czyPolePuste(int x, int y) {
    // Sprawdź, czy pozycja nie wychodzi poza granice mapy
    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return false;
    }

    // Sprawdź, czy na danej pozycji nie ma już innego obiektu
    if (mapa[y][x].symbol != '.' ) {
        return false;
    }

    return true;
}


void Mapa::testujWalkiWielokrotnie(int iloscTestow) {
    srand(static_cast<unsigned>(time(nullptr)));


        std::cout << "Choose an enemy:" << std::endl;
        std::cout << "1. Ogr" << std::endl;
        std::cout << "2. Goblin" << std::endl;
        std::cout << "3. Szczur" << std::endl;
        std::cout << "4. Zombi" << std::endl;
        std::cout << "5. Zywiolak" << std::endl;

        int choice;
        std::cin >> choice;
        int ileObrazen, zyciePrzedGracz, zyciePrzedPrzeciwnik;
        int atakRoll;
        Przeciwnik* przeciwnik = nullptr;
        int wygraneBohater = 0;
        int unikiPrzeciwnik = 0;
        int wygranePrzeciwnik = 0;
        int unikiGracz = 0;
        int krytGracz = 0;
        int krytPrzeciwnik = 0;
        // Przygotuj nowego przeciwnika dla każdej walki
        for (int i = 0; i < iloscTestow; ++i) {
            // Stwórz nowego gracza
            Gracz gracz;
            gracz.inicjalizajca(1, 50, 15, 10, 10, 10, 50);

            switch (choice) {
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
                    std::cout << "Invalid choice. Exiting combat testing mode." << std::endl;
                    return;
            }


            // Wyświetl początkowy stan walki
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
                // Wyświetl aktualny stan walki
                std::cout << "Stan walki:\n";                
                std::cout << "Bohater: " << gracz.dostanZycie() << " HP\n";
                std::cout << przeciwnik->nazwa << ": " << przeciwnik->zycie << " HP\n\n";


            }
            // Wyświetl wynik walki
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
        // Zwolnij pamięć zaalokowaną na obiekt przeciwnika
        delete przeciwnik;
    }

void Mapa::floodFill(int x, int y, char symbol) {
    // Sprawdź, czy pozycja nie wychodzi poza granice mapy
    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return;
    }

    // Jeśli pole jest dostępne i nie zostało jeszcze odwiedzone
    if (mapa[y][x].symbol == '.' || mapa[y][x].symbol == 'I' || czyIstniejePrzeciwnik(x, y)) {
        // Oznacz pole jako odwiedzone
        mapa[y][x].symbol = '^';

        // Przeprowadź rekurencyjne wywołania dla sąsiednich pól
        floodFill(x - 1, y, symbol); // lewo
        floodFill(x + 1, y, symbol); // prawo
        floodFill(x, y - 1, symbol); // góra
        floodFill(x, y + 1, symbol); // dół
    }
}

void Mapa::floodFillPrzejscie(int x, int y, int &maxKroki, int &maxX, int &maxY, int kroki) {
    // Sprawdź, czy pozycja nie wychodzi poza granice mapy
    if (x < 0 || x >= szerokoscMapy || y < 0 || y >= wysokoscMapy) {
        return;
    }

    // Sprawdź, czy pole jest dostępne i nie jest ścianą
    if (mapa[y][x].symbol != '.' && mapa[y][x].symbol != 'I' && !czyIstniejePrzeciwnik(x, y)) {
        return;
    }

    // Oznacz pole jako przejście
    mapa[y][x] = Przejscie();

    // Sprawdź, czy aktualna ścieżka jest najdalsza
    if (kroki > maxKroki) {
        maxKroki = kroki;
        maxX = x;
        maxY = y;
    }

    // Przeprowadź rekurencyjne wywołania dla sąsiednich pól
    floodFillPrzejscie(x - 1, y, maxKroki, maxX, maxY, kroki + 1); // lewo
    floodFillPrzejscie(x + 1, y, maxKroki, maxX, maxY, kroki + 1); // prawo
    floodFillPrzejscie(x, y - 1, maxKroki, maxX, maxY, kroki + 1); // góra
    floodFillPrzejscie(x, y + 1, maxKroki, maxX, maxY, kroki + 1); // dół
}

bool Mapa::sprawdzDostepnosc() {
    // Znajdź pozycję gracza na mapie
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

    // Wykonaj flood fill z pozycji gracza
    floodFill(x, y, '@');

    // Zresetuj oznaczenia pól
    for (int i = 0; i < wysokoscMapy; ++i) {
        for (int j = 0; j < szerokoscMapy; ++j) {
            if (mapa[i][j].symbol == '^') {
                mapa[i][j].symbol = '.';
            }
        }
    }

    // Znajdź najdalsze pole od gracza
    int maxKroki = 0, maxX = 0, maxY = 0;
    floodFillPrzejscie(x, y, maxKroki, maxX, maxY, 0);

    // Oznacz najdalsze pole jako przejście
    if (maxKroki > 0) {
        mapa[15][15].symbol = '!';
    }

    // Gracz może dotrzeć do każdego przedmiotu i przeciwnika
    return true;
}

bool Mapa::czyObszarPusty(int x, int y, int szerokosc, int wysokosc) {
    // Sprawdź, czy obszar nie wychodzi poza granice mapy
    if (x < 0 || x + szerokosc >= szerokoscMapy || y < 0 || y + wysokosc >= wysokoscMapy) {
        return false;
    }

    // Sprawdź, czy obszar nie koliduje z innymi obiektami
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
    cout<<"Poruszanie sie w/s/a/d Podnies przedmiot: f zniszcz przedmiot z plecaka: u" << endl;
    cout<<"Zaloz przedmiot z plecaka: e Sciagnij: r Test walki: l" << endl;
    for ( auto& row : mapa) {
        for (auto& pole : row) {
            cout << pole.symbol;
        }
        cout << endl;
    }

}
