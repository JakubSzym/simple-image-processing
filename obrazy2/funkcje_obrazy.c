#include "funkcje_obrazy2.h"

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
      *tab = abs(obraz_wej->tablica[i+1][j] - obraz-wej->tablica[i][j]) + abs(obraz_wej->tablica[i][j+1] - tablica[i][j]); //zmiana wartosci danego elementu zgodnie ze wzorem
    }
  }
}

//funkcja progujaca
void proguj(Obrazek *obraz_wej, float prog){
  for(int i = 0;i < *wymy;i++){ 
     for(int j = 0;j < *wymx;j++){
       if(obraz_wej->tablica[i][j] > (int)(obraz_wej->odcienie * prog))   //jesli wartosc elementu jest wieksza od pewnego progu, to element przyjmuje wartosc maksymalna
	 obraz_wej->tablica[i][j] = obraz_wej->odcienie
       else
	 obraz_wej->tablica[i][j] = 0                        //jesli wartosc elementu jest mniejsza od pewnego progu, to element przyjmuje wartosc 0

     }
  }
}

//funkcja rozmywajaca
void rozmyj(Obrazek *obraz_wej, int promien){
  int suma;                                      //zmienna pomocnicza - suma wartosci kolejnych elementow
  for(int i = 0;i < obraz_wej->wymy;i++){
    for(int j = 0;j < obraz_wej->wymx;j++){
      suma = 0;                                  //wyzerowanie zmiennej suma po zakonczeniu operacji na danym elemencie
      for(int k = 0;k < (2 * promien + 1);k++){
	suma += obraz_wej->tablica[i-promien+k][j];            //dodanie do sumy k-tego elementu z sasiedztwa danego elementu
      }
      obraz_wej->tablica[i][j]= (int)(suma / (2 * promien + 1));    //wartosc wyjsciowa danego elementu
    }
  }
}

//funkcja zmieniająca poziom czerni i bieli
void zmiana_poziomow(Obrazek *obraz_wej, int biel, int czern){
  for(int i = 0; i < obraz_wej->wymy; i++){
    for(int j = 0; j < obraz_wej->wymx; j++){
      if(obraz_wej->tablica[i][j] <= czern)
	obraz_wej->tablica[i][j] = 0;
      else if(obraz_wej->tablica[i][j] > czern && obraz_wej->tablica[i][j] < biel)
	obraz_wej->tablica[i][j] = (obraz_wej->tablica[i][j] - obraz_wej->odcienie) * (obraz_wej->odcienie/(biel - czern));
      else if(obraz_wej->tablica[i][j] >= biel)
	obraz_wej->tablica[i][j] = obraz_wej->odcienie;
    }
  }
}
