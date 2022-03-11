/* Calmis Liviu - 311 CB */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#ifndef ARBORE_BINAR
#define ARBORE_BINAR
#define NrLitere (68)

typedef struct carte{
	char titlu[50];
	char autor[50];
	int rating;
	int pagini;
}TCarte;

typedef struct nod_trie1{
	int frunza;
	struct nod_trie1* copil[NrLitere];
	TCarte *info;
} T1Nod, *T1;

typedef struct nod_trie2{
	int frunza;
	struct nod_trie2 *copil[NrLitere];
	T1 info;
	
} T2Nod, *T2;

T1 ConstrNod1();
T2 ConstrNod2();
void afisare_T1(T1 arb, char *titlu, int niv, int autocomplete, FILE *g);
void afisare_T2(T2 arb, char *autor, char *pref, int niv, FILE *g);
void add_book_T1(T1 arb, char *titlu, TCarte *carte);
void add_book_T2(T2 arb, char *autor, TCarte *carte);
int search_book(T1 arb, char *titlu, FILE *g);
int list_author(T2 arb, char *autor, FILE *g);
void list_author_auto(T2 arb, char *pref, FILE *g);
T1 delete_book_T1(T1 arb, char *titlu, int niv);
T2 delete_book_T2(T2 arb, char *autor, char *titlu, int niv);
int search_by_author(T2 arb, char *autor, char *titlu, FILE *g);
void search_book_auto(T1 arb, char *pref, FILE *g);
int nodGol_T1(T1 arb);
int nodGol_T2(T2 arb);
char *search_author(T1 arb, char *titlu, FILE *g);

#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
