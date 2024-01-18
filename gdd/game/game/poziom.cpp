#include "poziom.h"
#include "przeciwnik.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>



void czyscMape() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

Poziom::Poziom()
{

}

void Poziom::wczytaj(string nazwaPliku, Gracz &gracz) {

    // wczytanie poziomu
    ifstream plik;

    plik.open(nazwaPliku);
    if(plik.fail()){
        perror(nazwaPliku.c_str());
        system("PAUSE");
        exit(1);
    }

    string linia;

    while(getline(plik, linia)){
        mapa.push_back(linia);
    }

    plik.close();

    //............................................//

    char pole;
    for(unsigned int i = 0; i < mapa.size(); i++) {
        for(unsigned int j = 0; j < mapa[i].size(); j++) {
            pole = mapa[i][j];

            switch(pole){
                case '@':
                    gracz.ustawPozycje(j, i);
                break;
                case 'S': // wąż
                przeciwnicy.push_back(Przeciwnik("Waz", pole, 1, 5, 20, 50));
                przeciwnicy.back().ustawPozycje(j, i);
                break;
                case 'g':
                przeciwnicy.push_back(Przeciwnik("Goblin", pole, 2, 10, 10, 100));
                przeciwnicy.back().ustawPozycje(j, i);
                break;
            }

        }
    }

}


void Poziom::wyswietl() {

    czyscMape();
    cout << "Komendy poruszania sie to w/a/s/d"<<endl;
    for(unsigned int i = 0; i < mapa.size(); i++) {
        printf("%s\n", mapa[i].c_str());
    }

    printf("\n");

}


void Poziom::rusz(char komenda, Gracz &gracz) {

    int graczX, graczY;

    gracz.dostanPozycje(graczX, graczY);


    switch(komenda){
    case 'w':
    case 'W':
        przetworzRuchGracza(gracz, graczX, graczY - 1);
        break;
    case 's':
    case 'S':
        przetworzRuchGracza(gracz, graczX, graczY + 1);
        break;
    case 'a':
    case 'A':
        przetworzRuchGracza(gracz, graczX - 1, graczY);
        break;
    case 'd':
    case 'D':
        przetworzRuchGracza(gracz, graczX + 1, graczY);
        break;
    default:
        cout << "Nieprawidlowy ruch" << endl;
        system("PAUSE");
        break;
    }
    wyswietl();
}
char Poziom::dostanPole(int x, int y){
    return mapa[y][x];

}

void Poziom::ustawPole(int x, int y, char pole){
    mapa[y][x] = pole;
}

void Poziom::przetworzRuchGracza(Gracz &gracz, int miejsceX, int miejsceY) {
    int graczX, graczY;

    gracz.dostanPozycje(graczX, graczY);

    char poleRuchu = dostanPole(miejsceX, miejsceY);


    switch (poleRuchu) {

        case '#':
        cout << "Wszedles w sciane: " << "\n";
        system("PAUSE");
        break;

        case '.':
        gracz.ustawPozycje(miejsceX, miejsceY);
        ustawPole(graczX, graczY, '.');
        ustawPole(miejsceX, miejsceY, '@');

        break;

        default:

        atak(gracz, miejsceX, miejsceY);
        system("PAUSE");
        break;
    }

}
void Poziom::przetworzRuchPrzeciwnika(Gracz &gracz, int przeciwnikIndex, int miejsceX, int miejsceY) {
    int graczX, graczY, przeciwnikX, przeciwnikY;

    gracz.dostanPozycje(graczX, graczY);
    przeciwnicy[przeciwnikIndex].dostanPozycje(przeciwnikX, przeciwnikY);

    char poleRuchu = dostanPole(miejsceX, miejsceY);


    switch (poleRuchu) {
        case '.':
        przeciwnicy[przeciwnikIndex].ustawPozycje(miejsceX, miejsceY);
        ustawPole(przeciwnikX, przeciwnikY, '.');
        ustawPole(miejsceX, miejsceY, przeciwnicy[przeciwnikIndex].dostanSymbol());
        wyswietl();
        case '@':
        atak(gracz, przeciwnikX, przeciwnikY);
        system("PAUSE");
        break;
        case '#':
        break;
        default:
        break;
    }
}



void Poziom::aktualizujPotwory(Gracz &gracz) {
    char aiRuch;
    int graczX, graczY, przeciwnikX, przeciwnikY;

    gracz.dostanPozycje(graczX, graczY);

    for(unsigned int i = 0; i < przeciwnicy.size(); i++){
        aiRuch = przeciwnicy[i].dostanRuch(graczX, graczY);
        przeciwnicy[i].dostanPozycje(przeciwnikX, przeciwnikY);


        switch(aiRuch){
        case 'w':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX, przeciwnikY - 1);
            break;
        case 's':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX, przeciwnikY + 1);
            break;
        case 'a':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX - 1, przeciwnikY);
            break;
        case 'd':
            przetworzRuchPrzeciwnika(gracz,i, przeciwnikX + 1, przeciwnikY);
            break;
      }

    }

}

void Poziom::atak(Gracz &gracz, int celX, int celY){

    string nazwaPrzeciwnika;
    int przeciwnikX, przeciwnikY, ileObrazen, atakRoll, graczX, graczY;

    gracz.dostanPozycje(graczX,graczY);

    for(unsigned int i = 0; i < przeciwnicy.size(); i++) {

        przeciwnicy[i].dostanPozycje(przeciwnikX, przeciwnikY);
        nazwaPrzeciwnika = przeciwnicy[i].dostanNazwe();

        if (celX == przeciwnikX && celY == przeciwnikY ){
            // tura gracza
            atakRoll = gracz.obrazenia();
            cout << "Bohater zaatakowal " << nazwaPrzeciwnika <<" zadajac: "<< atakRoll << " obrazen" << "\n";
            ileObrazen = przeciwnicy[i].dostanObrazenia(atakRoll);

            if (ileObrazen != 0){
                ustawPole(celX,celY,'.');
                cout << nazwaPrzeciwnika << " zginal" << "\n";

                przeciwnicy[i] = przeciwnicy.back();
                przeciwnicy.pop_back();
                i--;


                system("PAUSE");
                gracz.dostanDoswiadczenie(ileObrazen);
                return;
            }

            // Tura przeciwnika
            atakRoll = przeciwnicy[i].obrazenia();
            cout << nazwaPrzeciwnika << " zaatakowal gracza zadajac: " << atakRoll << " obrazen" << "\n";
            ileObrazen = gracz.dostanObrazenia(atakRoll);

            if (ileObrazen != 0){
                ustawPole(graczX,graczY,'X');
                cout << "Bohater zginal" << "\n";
                system("PAUSE");
                exit(0);
            }

            return;
        }

    }

}
