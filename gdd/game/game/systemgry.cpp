#include "systemgry.h"
#include <iostream>
#include <conio.h>


SystemGry::SystemGry(string nazwaPlikuPoziomu)
{

    gracz.inicjalizajca(1,100,15,20,0);
    poziom.wczytaj(nazwaPlikuPoziomu, gracz);
    poziom.wyswietl();

    system("PAUSE");
}

void SystemGry::zacznijGre(){

    bool skonczone = false;

    while (!skonczone){
        poziom.wyswietl();        
        ruchGracza();
        poziom.aktualizujPotwory(gracz);
    }

};


void SystemGry::ruchGracza(){
    char komenda;

    while(true){
        komenda = _getch();
        cout << "Wprowadziles : " << komenda << endl;
        poziom.rusz(komenda, gracz);
        poziom.aktualizujPotwory(gracz);

    }

}
