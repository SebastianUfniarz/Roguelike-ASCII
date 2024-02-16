#include "gracz.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>
#include <fstream>
Gracz::Gracz()
{
    symbol = '@';
}

void Gracz::inicjalizajca(int poziom, int zycie, float atak, float obrona, float zrecznosc,float szczescie, int doswiadczenie) {
    this->poziom = poziom;
    this->zycie = zycieMax = zycie;
    this->atak = atak;
    this->zrecznosc = zrecznosc;
    this->obrona = obrona;
    this->szczescie = szczescie;
    this->doswiadczenie = doswiadczenie;
    bonusAtak = 0;
    bonusObrona = 0;
    bonusZrecznosc = 0;
    bonusSzczescie = 0;
}

void Gracz::przywrocZycie() {
    int przywracaneZycie = 20 + (poziom * 2);
    zycie += przywracaneZycie;


    if (zycie > zycieMax) {
        zycie = zycieMax;
    }

    std::cout << "Przywrocono " << przywracaneZycie << " punktow zycia." << std::endl;
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

    while (this->doswiadczenie > 50 * poziom) {
        cout << "Nowy poziom! " << "\n";
        this->doswiadczenie -= 50 * poziom;
        this->atak += 15;
        this->obrona += 5;
        this->poziom++;
        this->zycie += 10;
        this->zycieMax += 10;
    }
};
void Gracz::wyswietlInfo()  {
    cout << "Poziom: " << poziom << endl;
    cout << "Zycie: " << zycie << endl;
}

void Gracz::Pomoc()  {
    cout <<  "Poruszanie sie 'w/s/a/d'" << endl;
    cout << "Podnies przedmiot: 'f'" << endl;
    cout << "Zniszcz przedmiot z plecaka: 'u' " << endl;
    cout << "Zaloz przedmiot z plecaka do ekwpiunku: 'e'" << endl;
    cout << "Sciagnij przedmiot z ekwipunku do plecaka: 'r' " << endl;
    cout << "Wyswietlenie statystyk przedmiotow w plecaku i ekwpunku: 'q'" << endl;
    cout << "Wyswietlenie statystyk bohatera: 'p'" << endl;
    cout << "Uzycie mikstury uzdrawiajacej: 'b'" << endl;
}


void Gracz::wyswietlStatystyki()  {
    cout << "Statystyki bohatera:" << endl;
    cout << "Poziom: " << poziom << endl;
    cout << "Zycie: " << zycie << endl;
    cout << "Zycie Max: " << zycieMax << endl;
    cout << "Atak: " << atak << endl;
    cout << "Obrona: " << obrona << endl;
    cout << "Zrecznosc: " << zrecznosc << endl;
    cout << "Szczescie: " << szczescie << endl;
    cout << "Doswiadczenie: " << doswiadczenie << endl;

}

void Gracz::ekran_koncowy() {
    std::ifstream plik("D:\\Gra_kolejna_proba\\end.txt");

    if (plik.is_open()) {
        std::string linia;
        while (std::getline(plik, linia)) {
            tekstEkranuKoncowego += linia + '\n';
        }

        plik.close();
    } else {
        tekstEkranuKoncowego = "Nie udalo się wczytac ekranu poczatkowego.\n";
    }


    std::cout << tekstEkranuKoncowego << std::endl;


}
