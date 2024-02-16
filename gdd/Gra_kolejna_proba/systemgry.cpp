#include "systemgry.h"
#include <conio.h>
#include <iostream>
#include <fstream>
SystemGry::SystemGry()
{


}
void SystemGry::ini(Mapa &mapa){
    int x = rand() % (mapa.szerokoscMapy - 2) + 1;
    int y = rand() % (mapa.wysokoscMapy - 2) + 1;
    mapa.dodajGracza(x,y,gracz);
    mapa.dodajPrzedmiotyStartowe();
};
void SystemGry::zacznijGre(){
    bool skonczone = false;
    ini(mapa);

    ekran_poczatkowy();
    system("Pause");

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
void SystemGry::ekran_poczatkowy() {
    std::ifstream plik("D:\\Gra_kolejna_proba\\ini.txt");

    if (plik.is_open()) {
        std::string linia;
        while (std::getline(plik, linia)) {
            tekstEkranuPoczatkowego += linia + '\n';
        }

        plik.close();
    } else {
        tekstEkranuPoczatkowego = "Nie udalo się wczytac ekranu poczatkowego.\n";
    }


    std::cout << tekstEkranuPoczatkowego << std::endl;


}
