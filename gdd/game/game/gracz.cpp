#include "gracz.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

Gracz::Gracz(){
    this->x = 0;
    this->y = 0;
}

void Gracz::inicjalizajca(int poziom, int zycie, int atak, int obrona, int zrecznosc, int doswiadczenie, int szczescie) {
    this->poziom = poziom;
    this->zycie = zycie;
    this->atak = atak;
    this->obrona = obrona;
    this->zrecznosc = zrecznosc;
    this->szczescie = szczescie;
    this->doswiadczenie = doswiadczenie;
}

void Gracz::ustawPozycje(int x, int y) {
    this->x = x;
    this->y = y;
}

void Gracz::dostanPozycje(int &x, int &y) {
    x = this->x;
    y = this->y;
}

int Gracz::obrazenia() {

    static default_random_engine generator(time(NULL));
    uniform_int_distribution<int> atakRoll(0, atak);

    return atakRoll(generator);

};

int Gracz::dostanObrazenia(int obrazenia) {

    obrazenia-= this->obrona;

    if(obrazenia > 0 ) {
        this->zycie-=obrazenia;

        if(this->zycie <= 0 ){
            return 1;
        }

    }
    return 0;
}

void Gracz::dostanDoswiadczenie(int doswiadczenie) {

    this->doswiadczenie+=doswiadczenie;

    while (this->doswiadczenie > 50) {
        cout << "Nowy poziom! " << "\n";
        this->doswiadczenie -= 50;
        this->atak += 10;
        this->obrona += 5;
        this->poziom++;
        this->zycie += 10;
        system("PAUSE");
    }
};


bool Gracz::unik(Gracz &gracz) {

    int maxSzansaUnik = 50;
    int BazowaSzansaUniku = 2;
    int SzansaUniku = min(gracz.zrecznosc, maxSzansaUnik);

    if (gracz.zrecznosc > 5) {
        int dodatkowaSzansa = (gracz.zrecznosc - 5) * BazowaSzansaUniku;
        SzansaUniku += dodatkowaSzansa;
    }

    int losowaWartosc = rand() % 100 + 1;

    return losowaWartosc <= SzansaUniku;
}

bool Gracz::ciosKrytyczny(Gracz &gracz) {
    int bazowaSzansaKrytka = 10;
    int bazowaSzansaKrytkaZwiekszenie = 2;
    int szansaKrytyczna = gracz.szczescie + bazowaSzansaKrytka;
    if (gracz.szczescie > 5) {
        int dodatkowaSzansa = gracz.szczescie * bazowaSzansaKrytkaZwiekszenie;
        szansaKrytyczna += dodatkowaSzansa;
    }
    int losowaWartosc = rand() % 100 + 1;
    return losowaWartosc <= szansaKrytyczna;
}

void Gracz::wyswietlStatystyki(){
    cout << "Zycie: "<< this->zycie << "\n";
}
