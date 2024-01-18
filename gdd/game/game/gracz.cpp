#include "gracz.h"
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

Gracz::Gracz(){
    this->x = 0;
    this->y = 0;
}

void Gracz::inicjalizajca(int poziom, int zycie, int atak, int obrona, int doswiadczenie) {
    this->poziom = poziom;
    this->zycie = zycie;
    this->atak = atak;
    this->obrona = obrona;
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
