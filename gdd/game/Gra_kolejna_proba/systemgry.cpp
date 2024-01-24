#include "systemgry.h"
#include <conio.h>
#include <iostream>
SystemGry::SystemGry()
{


}
void SystemGry::ini(){
    mapa.dodajGracza(5,5, gracz);
    mapa.dodajPrzedmiot(9,6, "Helm nowicujsza",0,3,0,0, HELM);
    mapa.dodajPrzedmiot(10,6, "Pancerz nowicujsza",0,7,0,0, PANCERZ);
    mapa.dodajPrzedmiot(12,6, "Drewniany miecz",5,0,0,0, MIECZ);
    mapa.dodajPrzedmiot(13,6, "Pas zrecznosci",0,1,0,5, PAS);
    mapa.dodajPrzedmiot(14,6, "Pierscien szczescia",0,0,3,0, PIERSCIEN);
    mapa.dodajPrzedmiot(15,6, "Spodnie nowicujsza",0,4,0,1, SPODNIE);
    mapa.dodajPrzedmiot(16,6, "Pierscien zrecznosci",0,0,0,3, PIERSCIEN);
    mapa.dodajPrzeciwnika(4,4,'G',"goblin",10,5,50,15,10,100);

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
