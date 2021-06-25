#ifndef STRUCT_H
#define STRUCT_H
#include<stdio.h>

//struktura do przechowywania informacji o obrazach PGM lub PPM
typedef struct{
	int wymx, wymy, odcienie;
	int **tablica;
} Obrazek;

#endif