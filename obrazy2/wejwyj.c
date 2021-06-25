#include "struct.h"
#include "constants.h"
#include "wejwyj.h"

//funkcja konwersji do szarosci dla obrazow PPM
int** konwertuj(Obrazek *obraz_wej){
  //utworzenie tablicy dynamicznej
  int **nowa_tablica;
  nowa_tablica = (int**)malloc((obraz_wej->wymy)*sizeof(int*));
  for(int i=0; i<(obraz_wej->wymy); i++){
    nowa_tablica[i] = (int*)malloc(obraz_wej->wymx*sizeof(int));
  }
  for(int i=0; i<obraz_wej->wymy; i++){
    for(int j=0; j<3*obraz_wej->wymx; j+=3){
      nowa_tablica[i][j/3] = (int)((obraz_wej->tablica[i][j] + obraz_wej->tablica[i][j+1] + obraz_wej->tablica[i][j+2])/3);	//konwertowanie do szarosci - srednia z trzech wartosci
    }
  }
  return nowa_tablica;
}
//funkcja wczytywania
int czytaj(FILE *plik_we, Obrazek *obraz_wej, int *kolorowy) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawidowy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"wejwyj.c czytaj(): Error %d: Nie podano uchwytu do pliku\n", B_BRAKPLIKU);
    return 0;
  }

  /* Sprawdzenie "numeru magicznego" - powinien by P2 lub P3 */
  fgets(buf,DL_LINII,plik_we);   /* Wczytanie pierwszej linii pliku do bufora */
   if(buf[0] == 'P'){
     if(buf[1] == '2'){
       *kolorowy = 0; //obraz jest czarno-bialy
       printf("Rozpoznano format PGM\n");
     }
    else if(buf[1] == '3'){
      *kolorowy = 1; //obraz jest kolorowy
      printf("Rozpoznano format PPM\n");
    }
    else{
      fprintf(stderr, "wejwyj.c czytaj(): Error %d: Nieprawidlowy format pliku\n", B_ZLYFORMAT);
      return 0;
    }
  }
  else{
    fprintf(stderr, "wejwyj.c czytaj(): Error %d: Nie rozpoznano formatu pliku\n", B_ZLYFORMAT);
    return 0;
  }
   
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
  if (fscanf(plik_we,"%d %d %d",&(obraz_wej->wymx),&(obraz_wej->wymy),&(obraz_wej->odcienie))!=3) {
    fprintf(stderr,"wejwyj.c czytaj(): Error %d: Brak wymiarow obrazu lub liczby stopni szarosci\n",B_BRAKWARTOSCI);
    return 0;
  }

  //sprawdzenie poprawnosci wymiarow
  if(obraz_wej->wymx <=0 || obraz_wej->wymy <= 0){
	fprintf(stderr, "wejwyj.c czytaj(): Error %d: Niedodatnie wymiary obrazu\n", B_NIEPRAWIDLOWAWARTOSC);
	return 0;
  }
  //jezeli kolorowy:
  if(*kolorowy == 0){
    //utworzenie tablicy dynamicznej
    obraz_wej->tablica = (int**)malloc(obraz_wej->wymy*sizeof(int*));
    for(i = 0; i < obraz_wej->wymy; i++){
      obraz_wej->tablica[i] = (int*)malloc(obraz_wej->wymx*sizeof(int));
    } 
   
 
    /* Pobranie obrazu i zapisanie w tablicy obraz_wej->tablica*/
    for (i = 0;i < obraz_wej->wymy; i++) {
      for (j = 0;j < obraz_wej->wymx; j++) {
	if (fscanf(plik_we,"%d",&(obraz_wej->tablica[i][j])) != 1) {
	  fprintf(stderr,"wejwyj.c czytaj(): Error %d: Niewlasciwe wymiary obrazu\n", B_NIEPRAWIDLOWAWARTOSC);
	  return 0;
	}
      }
    }
  }
  //jezeli czarno-bialy:
  if(*kolorowy == 1){
    //utworzenie tablicy dynamicznej
    obraz_wej->tablica = (int**)malloc(obraz_wej->wymy*sizeof(int*));
    for(i = 0; i < obraz_wej->wymy; i++){
      obraz_wej->tablica[i] = (int*)malloc(3*obraz_wej->wymx*sizeof(int));
    }
   
 
    /* Pobranie obrazu i zapisanie w tablicy obraz_wej->tablica*/
    for (i = 0;i < obraz_wej->wymy; i++) {
      for (j = 0;j < 3*obraz_wej->wymx; j++) {
	if (fscanf(plik_we,"%d",&(obraz_wej->tablica[i][j])) != 1) {
	  fprintf(stderr,"wejwyj.c czytaj(): Error %d: Niewlasciwe wymiary obrazu\n", B_NIEPRAWIDLOWAWARTOSC);
	  return 0;
	}
      }
    }
  }
  return obraz_wej->wymx*obraz_wej->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int zapisz(FILE *plik_we, Obrazek *obraz_wej) {
  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if(plik_we == NULL) {
    fprintf(stderr, "wejwyj.c zapisz(): Error %d: Nie podano uchwytu do pliku\n", B_BRAKPLIKU);    //komunikat o bledzie
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
  return obraz_wej->wymx*obraz_wej->wymy;
}

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}
