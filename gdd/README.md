# Gra Rougelike Sebastian Ufniarz



## Opis gry 
Gra jest typowym roguelike'em z kilkoma nowymi elementami, które zazwyczaj nie występują, aby lekko urozmaicić rozgrywkę, ale nie chcę tutaj wchodzić w szczegóły. Znajdują się one poniżej.


## Legenda
1. Postacie
1. Rozgrywka
1. Cel
1. Walka
1. Przedmioty i wzmocnienia
1. Postęp i Wyzwania
1. Przegrywanie
1. Lokalizacje



## 1. Postacie i potwory 

### Goblin:

Cechy: Mała, zwinna istota.

Opis: Goblin jest szybki i zręczny, co sprawia, że trudno go unikać. Jego atak jest średnio silny, ale ma ograniczoną obronę. Przeciwnik dość wytrzymały.

### Ogr:

Cechy: Potężny i silny wojownik.

Opis: Ogr to potężny przeciwnik o wysokim ataku, jednak jego obrona jest niska. Pomimo tego, ma dużo życia, co sprawia, że jest groźnym przeciwnikiem wymagającym skoncentrowanego ataku.

### Szczur:

Cechy: Mały, ale zwinny.

Opis: Szczur jest niewielkim przeciwnikiem, ale zręczność i szczęście sprawiają, że jest trudny do uniknięcia i zada czasem obrażenia krytyczne. Ma niższe życie, co rekompensuje wrogość.

### Zombi:

Cechy: Powolny, ale silny.

Opis: Zombi cechuje się dużym atakiem, ale niską zręcznością i szczęściem. Jego obrona jest minimalna, ale ma umiejętność utrzymania się przy życiu z powodu wysokiej ilości życia.

#### Żywiołak Lodowy:

Cechy: Potężna istota lodu.

Opis: Żywiołak Lodowy to potężny przeciwnik o bardzo wysokim ataku i obronie. Jest jednak mniej zwinny niż inne istoty. Posiada dużo życia i jest jednym z najtrudniejszych przeciwników, wymagającym strategicznego podejścia.

Każdy przeciwnik w grze charakteryzuje się unikalnym zestawem cech, co sprawia, że każda walka jest inna i wymaga od gracza dostosowania taktyki do specyfiki danego przeciwnika.



## 2. Rozgrywka

Rozgrywka w tej grze jest typowa dla gier typu Roguelike, co oznacza, że jest oparta na turowości, zróżnicowanym ekwipunku. Wartościowy ekwipunek jest kluczowy dla sukcesu w przetrwaniu i pokonaniu zagrożeń, które czyhają na bohatera. Gracz porusza się po losowo wygenerowanych poziomach.


## 3. Cel

Celem głównym gry jest pokonanie spaczonego Boga. 


## 4. Walka
### Statystyki postaci:

#### Poziom Gracza:
poziom: Określa aktualny poziom postaci. Zdobywanie doświadczenia powoduje awans na wyższe poziomy, co skutkuje zwiększeniem umiejętności gracza.

#### Stan Zdrowia:
Zycie: Ilość punktów życia postaci. Zmniejsza się w wyniku otrzymywanych obrażeń. Postac przegrywa, gdy ilość życia spadnie do zera.

#### Statystyki Ofensywne:
atak: Mierzy siłę ataku postaci. Im wyższa ta wartość, tym większe obrażenia zadaje przeciwnikom w walce.

#### Statystyki Defensywne:
obrona: Wartość obrony postaci, która redukuje otrzymywane obrażenia od przeciwników.

#### Zręczność i Szczęście:
zrecznosc: Wpływa na szansę uniku przed atakami przeciwników.
szczescie: Wpływa na szansę zadania obrażeń krytycznych przeciwnikom.

#### Doświadczenie:
doswiadczenie: Ilość zdobytego doświadczenia. Po osiągnięciu określonego poziomu doświadczenia, gracz awansuje na wyższy poziom, co zwiększa jego umiejętności.


## Walka:
#### Atak Postaci:
Gracz, przeciwnicy posiadają statystyki, takie jak siła ataku, zręczność, szczęście, które wpływają na skuteczność ich ataków.
W przypadku ataku, losowane są obrażenia w oparciu o statystyki gracza badź przeciwnika, a następnie przekazywane przeciwnikowi lub graczowi.

#### Uniki:
Przeciwnicy jak i bohaterowie posiadają zdolność do unikania ataków, zależną od ich zręczności.
Mechanizm uników oparty jest na losowaniu liczby w zakresie od 0 do 99, a wynik decyduje o powodzeniu uniku.

#### Ciosy Krytyczne:
Zarówno gracz, jak i przeciwnicy mają szansę zadania ciosu krytycznego.
Szansa na cios krytyczny zależy od statystyki szczęścia.
W przypadku sukcesu, obrażenia są zwiększone, co może wpłynąć na wynik walki.

#### Zdrowie i Śmierć:
Każdy uczestnik walki (gracz i przeciwnik) ma określoną pulę zdrowia.
Obrażenia zadane podczas ataków zmniejszają tę pulę.
Jeśli zdrowie spadnie do zera, postać umiera.
Po śmierci przeciwnika, gracz otrzymuje punkty doświadczenia.

## 5. Przedmioty i wzmocnienia

### Klasy przedmiotów:

HELM: Ochrona przed obrażeniami.

PANCERZ, REKAWICE: Zapewnia dodatkową ochronę ciała, redukując obrażenia od ataków przeciwników.

SPODNIE: Zwiększają ruchliwość postaci i chronią przed obrażeniami.

MIECZ: Narzędzie do ataku, wpływające na atak rażenia w walce i lekko na zręczność.

TOPOR: Narzędzie do ataku, wpływające na bardzo na atak rażenia w walce.

PIERŚCIEN: Bonusy do statystyk takich jak zręczność, szczęście.

BUTY: Bonus do zręczności, obrony.

AMULET: Różne bonusy.

PAS: Zwiększa zręczność postaci i wpływa na szanse unikania ataków.
Statystyki przedmiotów:

Gracze mogą zdobywać przedmioty podczas eksploracji mapy.

#### Balansowanie i strategia:

Gracze muszą równoważyć swoje statystyki, decydując, czy chcą być bardziej ofensywni, defensywni czy zdolni do unikania ataków.
Zmiana zestawu przedmiotów może dostosować postać do różnych sytuacji, co wymaga elastycznej strategii.

## 6. Postęp i Wyzwania

Rozwijanie postaci jest klasyczne, polegające na zdobywaniu doświadczenia za każdego pokonanego przeciwnika, co umożliwia zdobywanie poziomów postaci oraz związanych z nimi statystyk.

Jednym z kluczowych wyzwań będzie zarządzanie zasobami, zwłaszcza punktami życia, bo mikstury życia nie są łatwo dostępne. 

Każde piętro będzie stanowi coraz większe wyzwanie, z przeciwnikami posiadającymi większą ilość zdrowia, wyższą siłę ataku.

## 7. Przegrywanie

Przegrywanie w grze następuje w momencie, gdy życie postaci spadnie do zera, co skutkuje rozpoczęciem gry od samego początku. 


## 8. Lokalizacje

Lokalizacja jest jedna czyli wieża, jedynie zmieniają się w niej poziomy. 


