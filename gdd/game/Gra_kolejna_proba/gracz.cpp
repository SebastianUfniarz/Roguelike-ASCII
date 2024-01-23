#include "gracz.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
Gracz::Gracz()
{
    symbol = '@';
}

void Gracz::inicjalizajca(int poziom, int zycie, float atak, float obrona, int doswiadczenie) {
    this->poziom = poziom;
    this->zycie = zycie;
    this->atak = atak;
    this->obrona = obrona;
    this->doswiadczenie = doswiadczenie;
    bonusAtak = 0;
    bonusObrona = 0;
}


void Gracz::zwiekszenieAtaku(int bonusowyAtak) {

    this->atak+=bonusowyAtak;

};

void Gracz::zwiekszenieObrony(int bonusowaObrona) {

    this->obrona+=bonusowaObrona;

};
void Gracz::zmniejszenieAtaku(int bonusowyAtak) {

    this->atak-=bonusowyAtak;

};

void Gracz::zmniejszenieObrony(int bonusowaObrona) {

    this->obrona-=bonusowaObrona;

};
float Gracz::obrazenia() {

    return this->atak;
};

int Gracz::dostanObrazenia(float obrazenia) {

    float obrazenia_red;
    obrazenia_red = obrazenia * (obrazenia / (obrazenia + this->obrona));
    obrazenia = floor(obrazenia_red);
    cout<<"Obrazenia: " << obrazenia_red << " " << obrazenia << " " << this->atak <<" " << this->obrona;
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
    cout << "Doswiadczenie: " << doswiadczenie << endl;
}
