#include "przeciwnik.h"
#include <random>
#include <ctime>

Przeciwnik::Przeciwnik(string nazwa, char pole, int atak, int obrona, int zycie, int wartoscDoswiadczenia) {
    this->nazwa = nazwa;
    this->pole = pole;
    this->atak = atak;
    this->obrona = obrona;
    this->zycie = zycie;
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
