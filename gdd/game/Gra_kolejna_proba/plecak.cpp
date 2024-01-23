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
        std::cout << "Plecak jest pełny!" << std::endl;
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
        std::cout << "Przedmiot usunięty z plecaka." << std::endl;
    } else {
        std::cout << "Nieprawidłowy indeks przedmiotu." << std::endl;
    }
}



void Plecak::zalozPrzedmiotZPlecaka(unsigned int indeks, Gracz &gracz) {
    if (indeks >= 0 && indeks < zawartosc.size()) {
        if (ekwipunek.size() < maksymalnaIloscPrzedmiotow) {

            // Sprawdź, czy istnieje już przedmiot danego typu w ekwipunku
            bool czyTypJuzJest = false;
            for (unsigned int i = 0 ; i < ekwipunek.size() ; i++) {
                if (zawartosc[indeks].typ == ekwipunek[i].typ) {
                    czyTypJuzJest = true;
                    break;
                }
            }

            if (!czyTypJuzJest) {
                ekwipunek.push_back(zawartosc[indeks]);
                gracz.zwiekszenieAtaku(ekwipunek.back().atak);
                gracz.zwiekszenieObrony(ekwipunek.back().obrona);
                usunPrzedmiot(indeks);



                std::cout << "Przeniesiono przedmiot z plecaka do ekwipunku." << std::endl;
            } else {
                std::cout << "Przedmiot danego typu już istnieje w ekwipunku." << std::endl;
            }
        } else {
            std::cout << "Ekwipunek jest pełny lub osiągnięto maksymalną ilość typów." << std::endl;
        }
    } else {
        std::cout << "Nieprawidłowy indeks przedmiotu w plecaku." << std::endl;
    }
}

void Plecak::sciagnijPrzedmiotZEkwipunku(unsigned int indeks, Gracz &gracz) {
    if (indeks >= 0 && indeks < ekwipunek.size()) {
        // Sprawdź, czy plecak gracza ma jeszcze miejsce
        if (zawartosc.size() < maksymalnaIloscPrzedmiotow) {
            // Utwórz tymczasowy wektor dla zakładanych przedmiotów
            std::vector<przedmiot> tempEkwipunek;

            // Kopiuj zakładany przedmiot i usuń go z ekwipunku gracza (usuwanie z końca)
            przedmiot zakladanyPrzedmiot = ekwipunek.back();
            ekwipunek.pop_back();

            // Spróbuj dodać zakładany przedmiot do tymczasowego ekwipunku
            tempEkwipunek.push_back(zakladanyPrzedmiot);

            // Sprawdź, czy typ zakładanego przedmiotu już istnieje w ekwipunku
            for (const auto &przedmiot : ekwipunek) {
                if (przedmiot.typ == zakladanyPrzedmiot.typ) {
                    // Jeżeli typ już istnieje, przywróć zakładany przedmiot do ekwipunku gracza
                    ekwipunek.push_back(zakladanyPrzedmiot);
                    tempEkwipunek.clear();  // Wyczyść tymczasowy wektor
                    std::cout << "Przedmiot danego typu już istnieje w ekwipunku." << std::endl;
                    break;
                }
            }

            // Jeżeli operacja powiodła się, zaktualizuj statystyki gracza
            if (tempEkwipunek.size() == 1) {
                gracz.zmniejszenieAtaku(tempEkwipunek[0].atak);
                gracz.zmniejszenieObrony(tempEkwipunek[0].obrona);

                // Dodaj przedmiot do plecaka gracza
                zawartosc.push_back(tempEkwipunek[0]);

                std::cout << "Przeniesiono przedmiot z ekwipunku do plecaka." << std::endl;
            }
        } else {
            std::cout << "Plecak gracza jest pełny!" << std::endl;
        }
    } else {
        std::cout << "Nieprawidłowy indeks przedmiotu w ekwipunku." << std::endl;
    }
}


void Plecak::wyswietlZawartoscEkwipunek() {
    std::cout << "Zawartosc ekwipunku:" << std::endl;
    for (size_t i = 0; i < ekwipunek.size(); ++i) {
        std::cout << i << ". " << ekwipunek[i].nazwa << std::endl;
    }
}
