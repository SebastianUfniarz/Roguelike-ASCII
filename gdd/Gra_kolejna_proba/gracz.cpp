#include "gracz.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
Gracz::Gracz()
{
    symbol = '@';
}

void Gracz::inicjalizajca(int poziom, int zycie, float atak, float obrona, float zrecznosc,float szczescie, int doswiadczenie) {
    this->poziom = poziom;
    this->zycie = zycie;
    this->atak = atak;
    this->zrecznosc = zrecznosc;
    this->obrona = obrona;
    this->szczescie = szczescie;
    this->doswiadczenie = doswiadczenie;
    bonusAtak = 0;
    bonusObrona = 0;
    bonusZrecznosc = 0;
    bonusSzczescie = 0;
    maxZycie = this->zycie;
}


void Gracz::zwiekszenieAtaku(int bonusowyAtak) {

    this->atak+=bonusowyAtak;

};
void Gracz::zwiekszenieObrony(int bonusowaObrona) {

    this->obrona+=bonusowaObrona;

};
void Gracz::zwiekszenieZrecznosc(int bonusZrecznosc) {

    this->zrecznosc+=bonusZrecznosc;

};
void Gracz::zwiekszenieSzczescie(int bonusSzczescie) {

    this->szczescie+=bonusSzczescie;

};
void Gracz::zmniejszenieAtaku(int bonusowyAtak) {

    this->atak-=bonusowyAtak;

};
void Gracz::zmniejszenieZrecznosc(int bonusZrecznosc) {

    this->zrecznosc-=bonusZrecznosc;

};
void Gracz::zmniejszenieSzczescie(int bonusSzczescie) {

    this->szczescie-=bonusSzczescie;

};
void Gracz::zmniejszenieObrony(int bonusowaObrona) {

    this->obrona-=bonusowaObrona;

};
void Gracz::ulecz(int ile, int zycieAktualne) {
   this->zycie - zycieAktualne ;
   this->zycie+=ile;

};
float Gracz::obrazenia() {

    return this->atak;
};

bool Gracz::szansaUniuku(float zrecznosc) {
    int szansa = zrecznosc;

    if (szansa >= 100) {
        return true;
    }
    szansa = floor(szansa);
    int randomValue = rand() % 100;

    return randomValue < szansa;
};

bool Gracz::szansaKryta(float szczescie) {
    int szansa = szczescie;

    if (szansa >= 100) {
        return true;
    }
    szansa = floor(szansa);
    int randomValue = rand() % 100;

    return randomValue < szansa;
}

int Gracz::dostanObrazenia(float obrazenia) {

    float obrazenia_red;
    obrazenia_red = obrazenia * (obrazenia / (obrazenia + this->obrona));
    obrazenia = floor(obrazenia_red);   
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

void Gracz::wyswietlStatystyki()  {
    cout << "Statystyki bohatera:" << endl;
    cout << "Poziom: " << poziom << endl;
    cout << "Zycie: " << zycie << endl;
    cout << "Atak: " << atak << endl;
    cout << "Obrona: " << obrona << endl;
    cout << "Zrecznosc: " << zrecznosc << endl;
    cout << "Szczescie: " << szczescie << endl;
    cout << "Doswiadczenie: " << doswiadczenie << endl;
}
