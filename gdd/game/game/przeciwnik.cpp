#include "przeciwnik.h"
#include <random>
#include <ctime>

Przeciwnik::Przeciwnik(string nazwa, char pole, int atak, int obrona, int zrecznosc, int szczescie, int zycie, int wartoscDoswiadczenia) {
    this->nazwa = nazwa;
    this->pole = pole;
    this->zycie = zycie;
    this->atak = atak;
    this->obrona = obrona;
    this->zrecznosc = zrecznosc;
    this->szczescie = szczescie;
    this->wartoscDoswiadczenia = wartoscDoswiadczenia;
}

void Przeciwnik::ustawPozycje(int x, int y) {
    this->x = x;
    this->y = y;
}

void Przeciwnik::dostanPozycje(int &x, int &y) {
    x = this->x;
    y = this->y;
}

int Przeciwnik::obrazenia() {

    static default_random_engine generator(time(NULL));
    uniform_int_distribution<int> atakRoll(0, this->atak);

    return atakRoll(generator);

};


int Przeciwnik::dostanObrazenia(int obrazenia) {

    obrazenia-=this->obrona;

    if(obrazenia > 0 ) {
        this->zycie-=obrazenia;

        if(this->zycie <= 0 ){
            return this->wartoscDoswiadczenia;
        }

    }
    return 0;
}

bool Przeciwnik::unik(Przeciwnik &przeciwnik) {

    int maxSzansaUnik = 50;
    int BazowaSzansaUniku = 2;
    int SzansaUniku = min(przeciwnik.zrecznosc, maxSzansaUnik);

    if (przeciwnik.zrecznosc > 5) {
        int dodatkowaSzansa = (przeciwnik.zrecznosc - 5) * BazowaSzansaUniku;
        SzansaUniku += dodatkowaSzansa;
    }

    int losowaWartosc = rand() % 100 + 1;

    return losowaWartosc <= SzansaUniku;
}

bool Przeciwnik::ciosKrytyczny(Przeciwnik &przeciwnik) {
    int bazowaSzansaKrytka = 10;
    int bazowaSzansaKrytkaZwiekszenie = 2;
    int szansaKrytyczna = przeciwnik.szczescie + bazowaSzansaKrytka;
    if (przeciwnik.szczescie > 5) {
        int dodatkowaSzansa = przeciwnik.szczescie * bazowaSzansaKrytkaZwiekszenie;
        szansaKrytyczna += dodatkowaSzansa;
    }
    int losowaWartosc = rand() % 100 + 1;
    return losowaWartosc <= szansaKrytyczna;
}


char Przeciwnik::dostanRuch(int graczX,int graczY) {
    static default_random_engine generator(time(NULL));
    uniform_int_distribution<int> ruchRoll(0, 6);

    int odlegloscOdGracza, dx = this->x - graczX, dy = this->y - graczY, adx = abs(dx), ady = abs(dy);

    odlegloscOdGracza = adx + ady;

    if (odlegloscOdGracza <= 5) {

        if(adx > ady) {
            if(dx > 0){
                return 'a';
            }
            else{
                return 'd';
            }
        }
        else {
            if(dy > 0){
                return 'w';
            }
            else{
                return 's';
            }
        }

    }

    int losowyRuch = ruchRoll(generator);

    switch(losowyRuch){
    case 0:
        return 'a';
    case 1:
        return 'w';
    case 2:
        return 's';
    case 3:
        return 'd';
    default:
        return '.';
    }

}
