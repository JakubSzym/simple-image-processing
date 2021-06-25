#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1024
typedef struct{
  int wymx, wymy, odcienie;
  int void *tablica;
} Obrazek;

int czytaj(FILE*, Obrazek*);
int zapisz(FILE*, Obrazek*);\
void wyswietl(char*)