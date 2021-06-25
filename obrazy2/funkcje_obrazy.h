#ifndef FUNKCJE_OBRAZY_H
#define FUNKCJE_OBRAZY_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "struct.h"
//Funkcje działają na strukturach przechowujących dane o obrazach w formacie PGM lub PPM
void negatyw(Obrazek*); //funkcja tworząca negatyw
void konturuj(Obrazek*); //funkcja tworząca kontur obrazka
int proguj(Obrazek*, float); //funkcja progująca obraz
int rozmyj(Obrazek*, int); //funkcja rozmywania obrazu
int zmiana_poziomow(Obrazek*, int, int); //funkcja zmieniająca poziom czerni i bieli

/*Warunki:
W funkcjach proguj() i rozmyj() nalezy zwrócić uwagę, czy próg i promień rozmycia zostały prawidłowo
wprowadzone przez użytkownika. Odpowiednio 0 <= prog <= 1, type(promien) == promien && promien > 0 
W funkcji zmiana_poziomow() nalezy sprawdzic, czy poziom bieli i czerni miesci sie w przedziale [0, l_odcieni]
poziom bieli musi miec wieksza wartosc niz poziom czerni.
*/

#endif
