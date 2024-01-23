#include "systemgry.h"
#include <conio.h>
#include <iostream>
SystemGry::SystemGry()
{


}
void SystemGry::ini(){
    mapa.dodajGracza(5,5, gracz);
    mapa.dodajPrzedmiot(9,6, "helm",10,15, HELM);
    mapa.dodajPrzedmiot(10,6, "pancerz boloni",20,30, PANCERZ);
    mapa.dodajPrzedmiot(12,6, "hel",5,5, HELM);
    mapa.dodajPrzedmiot(13,6, "heasd",5,5, HELM);
    mapa.dodajPrzedmiot(14,6, "hsd",5,5, HELM);
    mapa.dodajPrzedmiot(15,6, "sdm",5,5, HELM);
    mapa.dodajPrzedmiot(16,6, "hsdm",5,5, HELM);
    mapa.dodajPrzeciwnika(4,4,'G',"goblin",10,5,100,100);

};
void SystemGry::zacznijGre(){
    bool skonczone = false;
    ini();
    while (!skonczone) {
            mapa.wyswietl();
            ruchGracza();
            mapa.aktualizujPotwory(gracz, mapa);
        }

};
void SystemGry::ruchGracza() {
    char komenda;

    while (true) {

        cin>>komenda;
        mapa.przesunGracza(komenda, mapa, gracz);
        mapa.aktualizujPotwory(gracz, mapa);
        }
}
