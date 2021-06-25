#include "wejwyj.h"
#define DL_LINII 1024
#define MAX 1024
int czytaj(FILE *plik_we, Obrazek *obraz_wej) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien być P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  //tu gdzie jeszcze musi by konwersja do szaroci dla ppm

  int (obraz_wej->tablica)[wymx];
  obraz_wej = (int(*)[wymx]) malloc(wymx*wymy*sizeof(int));

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */
  
  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",obraz_wej->wymx,obraz_wej->wymy,obraz_wej->odcienie)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obraz_wej->wymy;i++) {
    for (j=0;j<obraz_wej->wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_wej->tablica[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return obraz_wej->wymx*obraz_wej->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int zapisz(FILE *plik_we, Obrazek *obraz_wej) {
  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if(plik_we == NULL) {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");    //komunikat o bledzie
    return 0; //funkcja zwraca 0, jezeli nie podano uchwytu do pliku
  }
  fprintf(plik_we, "P2 ");
  /* Wpisanie wymiarow obrazu i liczby odcieni szarosci */
  fprintf(plik_we, "%d %d %d ", obraz_wej->wymx, obraz_wej->wymy, obraz_wej->odcienie);
  /* Wczytanie obrazu i zapisanie w tablicy obraz_pgm*/
  for(int i = 0;i < obraz_wej->wymy;i++) {
    for(int j = 0;j < obraz_wej->wymx;j++) {
      fprintf(plik_we, "%d ", obraz_wej->tablica[i][j]);
    }
  }
  return *wymx**wymy;
}