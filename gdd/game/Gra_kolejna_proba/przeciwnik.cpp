#include "przeciwnik.h"
#include <random>
Przeciwnik::Przeciwnik()
{

}

float Przeciwnik::obrazenia() {

    return this->atak;

};

void Przeciwnik::wyswietlStatystyki(){

    cout << "Statystyki goblina:" << endl;
    cout << "Zycie: " << zycie << endl;
    cout << "Atak: " << atak << endl;
    cout << "Obrona: " << obrona << endl;
    cout << "Doswiadczenie: " << wartoscDoswiadczenia << endl;
}

bool Przeciwnik::szansaUniuku(float zrecznosc) {

    int szansa = zrecznosc;

    if (szansa >= 100) {
        return true;
    }
    szansa = floor(szansa);
    int randomValue = rand() % 100;

    return randomValue < szansa;

};


bool Przeciwnik::szansaKryta(float szczescie) {
    int szansa = szczescie;

    if (szansa >= 100) {
        return true;
    }
    szansa = floor(szansa);
    int randomValue = rand() % 100;

    return randomValue < szansa;
}


int Przeciwnik::dostanObrazenia(float obrazenia) {
    float obrazenia_red;
    obrazenia_red = obrazenia * (obrazenia / (obrazenia + this->obrona));
    obrazenia = floor(obrazenia_red);
    cout<<"Obrazenia: " << obrazenia_red << " " << obrazenia << " " << this->atak <<" " << this->obrona;
    if(obrazenia > 0 ) {
        this->zycie-=obrazenia;

        if(this->zycie <= 0 ){
            return this->wartoscDoswiadczenia;
        }

    }
    return 0;
}

char Przeciwnik::dostanRuch(Gracz &gracz) {
    static default_random_engine generator(time(NULL));
    uniform_int_distribution<int> ruchRoll(0, 6);

    int odlegloscOdGracza, dx = x - gracz.x, dy = y - gracz.y, adx = abs(dx), ady = abs(dy);

    odlegloscOdGracza = adx + ady;

    if (odlegloscOdGracza <= 2) {

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
