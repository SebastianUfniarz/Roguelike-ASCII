#include "systemgry.h"
#include <conio.h>
#include <iostream>
SystemGry::SystemGry()
{


}
void SystemGry::ini(Mapa &mapa){
    int x = rand() % (mapa.szerokoscMapy - 2) + 1;
    int y = rand() % (mapa.wysokoscMapy - 2) + 1;
    mapa.dodajGracza(x,y,gracz);
    mapa.dodajPrzedmiot("Helm nowicujsza",0,3,0,0, HELM);
    mapa.dodajPrzedmiot("Pancerz nowicujsza",0,7,0,0, PANCERZ);
    mapa.dodajPrzedmiot("Drewniany miecz",5,0,0,0, MIECZ);
    mapa.dodajPrzedmiot("Pas zrecznosci",0,1,0,5, PAS);
    mapa.dodajPrzedmiot("Pierscien szczescia",0,0,3,0, PIERSCIEN);
    mapa.dodajPrzedmiot("Spodnie nowicujsza",0,4,0,1, SPODNIE);
    mapa.dodajPrzedmiot("Pierscien zrecznosci",0,0,0,3, PIERSCIEN);

};
void SystemGry::zacznijGre(){
    bool skonczone = false;
    ini(mapa);


    mapa.sprawdzDostepnosc();
    mapa.ustawSymbolNajdalszegoPola();
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
