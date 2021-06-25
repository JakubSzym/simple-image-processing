#include "funkcje_obrazy.h"
#include "constants.h"
//Funkcja tworzaca negatyw obrazu wejsciowego
void negatyw(Obrazek *obraz_wej){
  for(int i = 0;i < obraz_wej->wymy;i++){    
    for(int j = 0;j < obraz_wej->wymx;j++){
      obraz_wej->tablica[i][j] =  obraz_wej->odcienie - obraz_wej->tablica[i][j];      //zmiana wartosci danego elementu zgodnie ze wzorem
    }
  }
}

//funkcja konturajca
void konturuj(Obrazek *obraz_wej){
  for(int i = 0;i < obraz_wej->wymy;i++){
    for(int j = 0;j < obraz_wej->wymx;j++){
      if((i+1)<obraz_wej->wymy && (j+1)<obraz_wej->wymx){
        obraz_wej->tablica[i][j] = abs(obraz_wej->tablica[i+1][j] - obraz_wej->tablica[i][j]) + abs(obraz_wej->tablica[i][j+1] - obraz_wej->tablica[i][j]); //zmiana wartosci danego elementu zgodnie ze wzorem
      }
    }
  }
}

//funkcja progujaca
int proguj(Obrazek *obraz_wej, float prog){
  if(prog < 0 || prog > 1){
    fprintf(stderr, "funkcje_obrazy.c proguj(): Error %d: prog powinien byc liczba z przedzialu [0,1]", B_NIEPRAWIDLOWAWARTOSC);
    return B_NIEPRAWIDLOWAWARTOSC;
  }
  for(int i = 0;i < obraz_wej->wymy;i++){ 
    for(int j = 0;j < obraz_wej->wymx;j++){
      if(obraz_wej->tablica[i][j] > (int)(obraz_wej->odcienie * prog))   //jesli wartosc elementu jest wieksza od pewnego progu, to element przyjmuje wartosc maksymalna
        obraz_wej->tablica[i][j] = obraz_wej->odcienie;
      else
        obraz_wej->tablica[i][j] = 0;                        //jesli wartosc elementu jest mniejsza od pewnego progu, to element przyjmuje wartosc 0
    }
  }
  return W_OK;
}

//funkcja rozmywajaca
int rozmyj(Obrazek *obraz_wej, int promien){
  //sprawdzenie warunkow
  if (promien < 0){
    fprintf(stderr, "funkcje_obrazy.c rozmyj(): Error %d: promien rozmycia to liczba naturalna dodatnia\n", B_NIEPRAWIDLOWAWARTOSC);
    return B_NIEPRAWIDLOWAWARTOSC;
  }
  //wlasciwe dzialanie
  int suma;                                      //zmienna pomocnicza - suma wartosci kolejnych elementow
  for(int i = 0; i < obraz_wej->wymy;i++){
    for(int j = 0; j < obraz_wej->wymx;j++){
      suma = 0;                                  //wyzerowanie zmiennej suma po zakonczeniu operacji na danym elemencie
      for(int k = 0; k < (2 * promien + 1);k++){
	if((i-promien+k)>0 && (i-promien+k)<obraz_wej->wymy){
	  suma += obraz_wej->tablica[i-promien+k][j];            //dodanie do sumy k-tego elementu z sasiedztwa danego elementu
	}
      }
      obraz_wej->tablica[i][j] = (int)(suma / (2 * promien + 1));    //wartosc wyjsciowa danego elementu
    }
  }
  return W_OK;
}

//funkcja zmieniająca poziom czerni i bieli
int zmiana_poziomow(Obrazek *obraz_wej, int biel, int czern){
  //sprawdzenie warunkow
  if(biel > czern){
    if(biel < 0 || biel > obraz_wej->odcienie){
      fprintf(stderr, "funkcje_obrazy.c zmiana_poziomow(): Error %d: Poziom bieli powinien byc pomiedzy 0, a liczba odcieni\n", B_NIEPRAWIDLOWAWARTOSC);
      return B_NIEPRAWIDLOWAWARTOSC;
    }
    if(czern < 0 || czern > obraz_wej->odcienie){
      fprintf(stderr, "funkcje_obrazy.c zmiana_poziomow(): Error %d: Poziom czerni powinien byc pomiedzy 0, a liczba odcieni\n", B_NIEPRAWIDLOWAWARTOSC);
      return B_NIEPRAWIDLOWAWARTOSC;
    }
  }
  else{
    fprintf(stderr, "funkcje_obrazy.c zmiana_poziomow(): Error %d: Poziom bieli powinien byc wiekszy od poziomu czerni\n", B_NIEPRAWIDLOWAWARTOSC);
    return B_NIEPRAWIDLOWAWARTOSC;
  }
  //wlasciwe dzialanie
  for(int i = 0; i < obraz_wej->wymy; i++){
    for(int j = 0; j < obraz_wej->wymx; j++){
      if(obraz_wej->tablica[i][j] <= czern) //do elementów o wartosci mniejszej lub równej czerni jest przypisywana wartość 0
	obraz_wej->tablica[i][j] = 0;
      else if(obraz_wej->tablica[i][j] > czern && obraz_wej->tablica[i][j] < biel) //do elementów o wartości pomiędzy bielą a czernią jest przypisywana wartość wg wzoru
	obraz_wej->tablica[i][j] = (obraz_wej->tablica[i][j] - czern) * (obraz_wej->odcienie/(biel - czern));
      else if(obraz_wej->tablica[i][j] >= biel) //do elementów o wartości większej lub równej bieli jest przypisywana wartość maksymalna
	obraz_wej->tablica[i][j] = obraz_wej->odcienie;
    }
  }
  return W_OK;
}
