#include "przeciwnik.h"
#include <random>
Przeciwnik::Przeciwnik()
{

}

float Przeciwnik::obrazenia() {

    return this->atak;

};

void Przeciwnik::wyswietlStatystyki(){

    cout << "Statystyki: "<< nazwa << endl;
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
    uniform_real_distribution<float> szansaJedzeniaRoll(0.0, 1.0);
    int odlegloscOdGracza, dx = x - gracz.x, dy = y - gracz.y, adx = abs(dx), ady = abs(dy);

    odlegloscOdGracza = adx + ady;


    if (nazwa == "Goblin" && zycie< zycieMax/1.5) {
        if (adx > ady) {
            if (dx > 0) {
                return 'd';
            } else {
                return 'a';
            }
        } else {
            if (dy > 0) {
                return 's';
            } else {
                return 'w';
            }
        }
    }
    else if (nazwa == "Goblin" && odlegloscOdGracza <= 5 ) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 'd';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }
    if (nazwa == "Szczur" && szansaJedzeniaRoll(generator) <= 0.1 && !gracz.wTrakcieWalki) {
        cout<<"Szczur zjadl zwloki"<<endl;
            zycie+=1;
            zrecznosc += 1;
            szczescie += 1;
            atak += 1;
            obrona += 1;
    }
    else if (nazwa == "Szczur" && odlegloscOdGracza <= 5 ) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 'd';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }
    if (nazwa == "Ogr" && (static_cast<float>(zycie) / zycieMax) < 0.28) {
        cout<<"Ogr stal sie wsciekly zadaje podowojne obrazenia"<<endl;
        atak *= 2;

    } else if (nazwa == "Ogr" && odlegloscOdGracza <= 5) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 'd';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }
    if (nazwa == "Zombi" && odlegloscOdGracza <= 10) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 'd';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }
    else if (nazwa == "Lodowy Zywiolak" && odlegloscOdGracza <= 5 && czyNeutralny == false) {
        if (adx > ady) {
            if (dx > 0) {
                return 'a';
            } else {
                return 'd';
            }
        } else {
            if (dy > 0) {
                return 'w';
            } else {
                return 's';
            }
        }
    }
    else {

        int losowyRuch = ruchRoll(generator);

        switch (losowyRuch) {
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
}
