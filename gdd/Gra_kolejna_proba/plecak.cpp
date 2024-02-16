#include "gracz.h"
#include "przedmiot.h"
#include "plecak.h"
#include <iostream>

Plecak::Plecak() {

}

void Plecak::dodajPrzedmiot(przedmiot& przedmiot) {
    if (zawartosc.size() < maksymalnaIloscPrzedmiotow) {
        zawartosc.push_back(przedmiot);
    } else {
        std::cout << "Plecak jest pelny!" << std::endl;
        system("PAUSE");
    }
}

void Plecak::wyswietlZawartosc() {
    std::cout << "Zawartosc plecaka:" << std::endl;
    int i = 0;
    for (auto& przedmiot : zawartosc) {
        std::cout << i << ". " << przedmiot.nazwa << std::endl;
        i++;
    }
}

void Plecak::usunPrzedmiot(unsigned int indeks) {
    if (indeks >= 0 && indeks < zawartosc.size()) {
        zawartosc.erase(zawartosc.begin() + indeks);
        std::cout << "Wybrany przedmiot z plecaka zostal zniszczony." << std::endl;
    } else {
        std::cout << "Nieprawidlowy indeks przedmiotu." << std::endl;
        system("PAUSE");
    }
}



void Plecak::zalozPrzedmiotZPlecaka(unsigned int indeks, Gracz &gracz) {
    if (indeks >= 0 && indeks < zawartosc.size()) {
        if (ekwipunek.size() < maksymalnaIloscPrzedmiotow) {

            bool czyTypJuzJest = false;
            for (unsigned int i = 0; i < ekwipunek.size(); i++) {
                if (zawartosc[indeks].typ == ekwipunek[i].typ) {
                    czyTypJuzJest = true;
                    break;
                }
            }

            if (!czyTypJuzJest && zawartosc[indeks].typ != MIKSTURA_UZDROWIENIA) {
                ekwipunek.push_back(zawartosc[indeks]);
                gracz.zwiekszenieAtaku(ekwipunek.back().atak);
                gracz.zwiekszenieObrony(ekwipunek.back().obrona);
                gracz.zwiekszenieSzczescie(ekwipunek.back().szczescie);
                gracz.zwiekszenieZrecznosc(ekwipunek.back().zrecznosc);
                usunPrzedmiot(indeks);

                std::cout << "Przeniesiono przedmiot z plecaka do ekwipunku." << std::endl;
            } else if (zawartosc[indeks].typ == MIKSTURA_UZDROWIENIA) {
                std::cout << "Nie mozna zalozyc mikstury uzdrawiajacej do ekwipunku." << std::endl;
                system("Pause");
            } else {
                std::cout << "Przedmiot danego typu już istnieje w ekwipunku." << std::endl;
                system("PAUSE");
            }
        } else {
            std::cout << "Ekwipunek jest pełny" << std::endl;
            system("PAUSE");
        }
    } else {
        std::cout << "Nieprawidłowy przedmiot." << std::endl;
        system("PAUSE");
    }
}

void Plecak::sciagnijPrzedmiotZEkwipunku(unsigned int indeks, Gracz &gracz) {
    if (indeks < ekwipunek.size()) {
        if (zawartosc.size() < maksymalnaIloscPrzedmiotow) {
            przedmiot zakladanyPrzedmiot = ekwipunek[indeks];
            ekwipunek.erase(ekwipunek.begin() + indeks);

            gracz.zmniejszenieAtaku(zakladanyPrzedmiot.atak);
            gracz.zmniejszenieObrony(zakladanyPrzedmiot.obrona);
            gracz.zmniejszenieSzczescie(zakladanyPrzedmiot.szczescie);
            gracz.zmniejszenieZrecznosc(zakladanyPrzedmiot.zrecznosc);


            zawartosc.push_back(zakladanyPrzedmiot);

            std::cout << "Przeniesiono przedmiot z ekwipunku do plecaka." << std::endl;
        } else {
            std::cout << "Plecak gracza jest pelny!" << std::endl;
            system("PAUSE");
        }
    } else {
        std::cout << "Nieprawidlowy indeks przedmiotu w ekwipunku." << std::endl;
        system("PAUSE");
    }
}

void Plecak::wyswietlPlecakIEkwipunek() {
    std::cout << "Zawartosc plecaka:" << std::endl;
    for (size_t i = 0; i < zawartosc.size(); ++i) {
        std::cout << i << ". " << zawartosc[i].nazwa << " (Typ: " << typToString(zawartosc[i].typ)
                  << ", Atak: " << zawartosc[i].atak << ", Obrona: " << zawartosc[i].obrona
                  << ", Szczescie: " << zawartosc[i].szczescie << ", Zrecznosc: " << zawartosc[i].zrecznosc << ")" << std::endl;
    }

    std::cout << "\nZawartosc ekwipunku:" << std::endl;
    for (size_t i = 0; i < ekwipunek.size(); ++i) {
        std::cout << i << ". " << ekwipunek[i].nazwa << " (Typ: " << typToString(ekwipunek[i].typ)
                  << ", Atak: " << ekwipunek[i].atak << ", Obrona: " << ekwipunek[i].obrona
                  << ", Szczescie: " << ekwipunek[i].szczescie << ", Zrecznosc: " << ekwipunek[i].zrecznosc << ")" << std::endl;
    }
}
void Plecak::wyswietlZawartoscEkwipunek() {
    std::cout << "Zawartosc ekwipunku:" << std::endl;
    for (size_t i = 0; i < ekwipunek.size(); ++i) {
        std::cout << i << ". " << ekwipunek[i].nazwa << std::endl;
    }
}
