#include "struct.h"
#include "constants.h"
#include "funkcje_obrazy.h"
#include "wejwyj.h"

typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int w_promienia, poziom_bieli, poziom_czerni, kolor;  /* wartosc progu dla opcji progowanie  i promienia rozmycia dla opcji rozmycie*/
  float w_progu;
  char *nazwa_we, *nazwa_wy; //nazwy plikow
}Opcje;

int main(int argc, char **argv){
  char tabOpcji[argc-1];
  int index = 0, promien, biel, czern, odczytano = 0, zapisano = 0;
  float prog;
  Opcje wybor;
  Obrazek obraz;
  wybor.kolor = 0;
  if(argc == 1){
    fprintf(stderr, "main.c: Error %d: Brak danych wejsciowych.\n Aby zobaczyc opcje, wpisz -h po nazwie programu.\n", B_BRAKPLIKU);
    exit(1);
  }
  for(int i=1; i<argc; i++){
    if(argv[i][0] == '-'){
      if(argv[i][1] == 'i' || argv[i][1] == 'o' || argv[i][1] == 'p' || argv[i][1] == 'n' || argv[i][1] == 'k' || argv[i][1] == 'r' || argv[i][1] == 'd' || argv[i][1] == 'z' ||argv[i][1] == 'h'){
	tabOpcji[index] = argv[i][1];
	index++;
      }
      else
	fprintf(stderr, "main.c: Error %d: Nie rozpoznano opcji\n", B_NIEPOPRAWNAOPCJA);
    }
    switch(argv[i][1]){
      case 'i':{
        if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	  wybor.nazwa_we = argv[i];
	  if (strcmp(wybor.nazwa_we,"-")==0) /* gdy nazwa jest "-"        */
	    wybor.plik_we=stdin;            /* ustwiamy wejscie na stdin */
	  else                               /* otwieramy wskazany plik   */
	    wybor.plik_we=fopen(wybor.nazwa_we,"r");
	}
	else 
	  fprintf(stderr, "main.c: Error %d: Nie podano nazwy pliku\n", B_BRAKNAZWY); /* blad: brak nazwy pliku */
	break;
      }
      case 'o':{                 /* opcja z nazwa pliku wyjsciowego */
	if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
    	  wybor.nazwa_wy = argv[i];
	  if (strcmp(wybor.nazwa_wy,"-")==0)/* gdy nazwa jest "-"         */
	    wybor.plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	  else                              /* otwieramy wskazany plik    */
	    wybor.plik_wy=fopen(wybor.nazwa_wy,"w");
	} 
	else 
	  fprintf(stderr, "main.c: Error %d: Nie podano nazwy pliku\n", B_BRAKNAZWY);                   /* blad: brak nazwy pliku */
	break;
      }
      case 'p':{
	if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	  if (sscanf(argv[i],"%f",&prog)==1)
	    wybor.w_progu=prog;
	  else
	    fprintf(stderr, "main.c: Error %d: Niepoprawna wartosc progu\n", B_NIEPRAWIDLOWAWARTOSC);         /* blad: niepoprawna wartosc progu */
        }
	else 
	  fprintf(stderr, "main.c: Error %d: Nie podano wartosci progu\n", B_BRAKWARTOSCI);             /* blad: brak wartosci progu */
        break;
      }
      case 'r':{
        if(++i<argc){ //wczytujemy kolejny argument jako wartść promienia rozmycia
	  if (sscanf(argv[i], "%d", &promien)==1)
	    wybor.w_promienia=promien;
	  else
	    fprintf(stderr, "main.c Error %d: Niepoprawna wartosc promienia\n", B_NIEPRAWIDLOWAWARTOSC); //błąd: niepoprawna wartość promienia
	}
	else
	  fprintf(stderr, "main.c Error %d: Nie podano wartosci promienia\n",B_BRAKWARTOSCI); //błąd: brak wartości promienia
	break;
      }
      case 'z':{
	++i;
	if(i+1<argc){
	  if(sscanf(argv[i], "%d", &biel) == 1 && sscanf(argv[++i] , "%d", &czern) == 1){
	    wybor.poziom_bieli = biel;
	    wybor.poziom_czerni = czern;
	  }
	  else
	    fprintf(stderr, "main.c: Error %d: Niepoprawna wartosc poziomu bieli lub czerni", B_NIEPRAWIDLOWAWARTOSC); //niepoprawna wartość poziomu bieli lub czerni
        }
	else
	  fprintf(stderr, "main.c: Error %d: Nie podano poziomu bieli i/lub czerni\n",B_BRAKWARTOSCI); //brak jednego lub dwóch argumentów
        break;
      }
    }
  }
  for(int i=0;i<argc-1;i++){
    switch(tabOpcji[i]){
      case 'i':{
	//wczytywanie
        odczytano = czytaj(wybor.plik_we, &obraz, &(wybor.kolor));
	if(odczytano)
	  printf("Wczytano plik\n");
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'i' : Error %d: Nie udalo sie wczytac pliku\n", B_BLADWCZYTYWANIA);
        break;
      }
      case 'o':{
	//zapisywanie
        zapisano = zapisz(wybor.plik_wy, &obraz);
	if(zapisano)
	  printf("Zapisano plik\n");
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'o' : Error %d: Nie udalo sie zapisac pliku\n", B_BLADZAPISU);
        break;
      }
      case 'd':{
	if(odczytano){
	  if(wybor.plik_we != NULL && wybor.plik_wy != NULL){
	    wyswietl(wybor.nazwa_wy);
	    wyswietl(wybor.nazwa_we);
	  }
	  else if(wybor.plik_we != NULL)
	    wyswietl(wybor.nazwa_we);
	}
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'd': Error %d: Nie udalo sie odczytac lub nie wczytano pliku\n", B_BLADWCZYTYWANIA);
        break;
      }
      case 'n':{
	//tworzenie negatywu
        if(odczytano){
	  if(wybor.kolor){
	    obraz.tablica = konwertuj(&obraz);
	    wybor.kolor = 0;
	  }
	  negatyw(&obraz);
	}
        else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'n': Error %d: Nie udalo sie odczytac lub nie wczytano pliku\n", B_BLADWCZYTYWANIA);
        break;
      }
      case 'p':{
	//progowanie
	if(wybor.w_progu > 0 && wybor.w_progu < 1){
	  if(odczytano){
	    if(wybor.kolor){
	      obraz.tablica = konwertuj(&obraz);
	      wybor.kolor = 0;
	    }
	    proguj(&obraz, wybor.w_progu);
	  }
	  else
	    fprintf(stderr, "main.c switch(tabOpcji) case 'p': Error %d: Nie udalo sie odczytac lub nie wczytano pliku\n", B_BLADWCZYTYWANIA);
	}
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'p': Error %d: Niepoprawna wartosc progu - powinien byc w przedziale [0,1]\n", B_NIEPRAWIDLOWAWARTOSC);
	break;
      }
      case 'k':{
	 //konturowanie
         if(odczytano){
	   if(wybor.kolor){
	     obraz.tablica = konwertuj(&obraz);
	     wybor.kolor = 0;
	   }
	   konturuj(&obraz);
	 }
	 else
	   fprintf(stderr, "main.c switch(tabOpcji) case 'k': Error %d: Nie udalo sie odczytac lub nie wczytano pliku\n", B_BLADWCZYTYWANIA);
         break;
      }
      case 'r':{
	//rozmywanie
        if(wybor.w_promienia > 0){
	  if(odczytano){
	    if(wybor.kolor){
	      obraz.tablica = konwertuj(&obraz);
	      wybor.kolor = 0;
	    }
	    rozmyj(&obraz, wybor.w_promienia);
	  }
	  else
	    fprintf(stderr, "main.c switch(tabOpcji) case 'r': Error %d: Nie udalo sie odczytac lub nie wczytano pliku\n", B_BLADWCZYTYWANIA);
	  }
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'r': Niepoprawna wartosc promienia - powinien byc liczba naturalna dodatnia\n", B_NIEPRAWIDLOWAWARTOSC);
	break;
      }
      case 'z':{
	//zmiana poziomow czerni i bieli
        if(odczytano){
	  if(wybor.kolor){
	    obraz.tablica = konwertuj(&obraz);
	    wybor.kolor = 0;
	  }
	  if(wybor.poziom_bieli >= 0 && wybor.poziom_bieli <= obraz.odcienie && wybor.poziom_czerni >= 0 && wybor.poziom_czerni <= obraz.odcienie)
	    zmiana_poziomow(&obraz, wybor.poziom_bieli, wybor.poziom_czerni);
	  else
	    fprintf(stderr, "main.c switch(tabOpcji) case 'z': Error %d: Niepoprawna wartosc poziomu czerni lub bieli - powinien byc w przedziale [0, l_odcieni]\n", B_NIEPRAWIDLOWAWARTOSC);
	}
	else
	  fprintf(stderr, "main.c switch(tabOpcji) case 'z': Error %d: Nie udalo sie odczytac pliku\n", B_BLADWCZYTYWANIA);
        break;
      }
      case 'h':{
	//wyswietlenie manuala do obslugi programu
	printf("\nWczytanie:\n program [-i nazwa_pliku]");
	printf("\nZapisywanie:\n program [-o nazwa_pliku]");
        printf("\nUwaga: Aby skorzystac z ponizszych opcji nalezy wczytac plik.");
	printf("\nWyswietlenie:\n[-d]");
	printf("\nNegatyw:\n[-n]");
	printf("\nProgowanie:\n[-p prog]");
	printf("\nKonturowanie:\n[-k]");
	printf("\nRozmywanie:\n[-r promien]");
	printf("\nZmiana poziomow:\n[-z biel czern]");
	printf("\nOpcje:\n program [-h]");
	printf("\npromien > 0 \nprog > 0 && prog < 1 \nbiel >= 0 && biel <= l_odcieni, czern >= 0 && czern <= l_odcieni\n");
	break;
      }
    }
  }
  for(int i=0; i<obraz.wymy; i++){
    free(obraz.tablica[i]);
  }
  free(obraz.tablica);
  return 0;
  }