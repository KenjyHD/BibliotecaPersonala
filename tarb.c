/* Calmis Liviu - 311 CB */

#include "tarb.h"

static int nr = 0;

//Construire nod din arbore T1
T1 ConstrNod1()
{
	int i;
	T1 aux = (T1)malloc (sizeof(T1Nod));
	if(!aux) return NULL;
	aux->frunza = 0;
	if (!aux) return NULL;
		for(i = 0; i < NrLitere; i++){
			aux->copil[i] = NULL;
	}

	return aux;
}

//Construire nod din arbore T2
T2 ConstrNod2()
{
	int i;
	T2 aux = (T2)malloc (sizeof(T2Nod));
	if(!aux) return NULL;
	aux->frunza = 0;
	if (!aux) return NULL;
		for(i = 0; i < NrLitere; i++){
			aux->copil[i] = NULL;
	}

	return aux;
}

//Adaugare carte in arbore T1
void add_book_T1(T1 arb, char *titlu, TCarte *carte)
{
	int len = strlen(titlu);
	int niv;
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int i;
	T1 aux = arb;

	for(niv = 0; niv < len; niv++)
	{
		//Caut indexul aferent literei din alfabet
		for(i = 0; i < NrLitere; i++)
			if(alphabet[i] == titlu[niv]) break;

		if(!aux->copil[i]){
			aux->copil[i] = ConstrNod1();
		}
		
		aux = aux->copil[i];
	}
	aux->info = carte;
	aux->frunza = 1;
}

//Adaugare carte in arbore T2
void add_book_T2(T2 arb, char *autor, TCarte *carte)
{
	int len = strlen(autor);
	int niv;
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int i;
	T2 aux = arb;

	for(niv = 0; niv < len; niv++)
	{
		for(i = 0; i < NrLitere; i++)
			if(alphabet[i] == autor[niv]) break;

		if(!aux->copil[i]){
			aux->copil[i] = ConstrNod2();
		}
		aux = aux->copil[i];
	}

	if(!aux->info) aux->info = ConstrNod1();
	add_book_T1(aux->info, carte->titlu, carte);
	aux->frunza = 1;
}

//Afisare toate sau primele 3 chei din arbore T1
void afisare_T1(T1 arb, char *titlu, int niv, int autocomplete, FILE *g)
{
	//Daca autocomplete = 1 nr va fi incrementat dupa fiecare carte afisata
	if(nr < 3){
		char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
		if(arb->frunza){
			titlu[niv] = '\0';
			fprintf(g, "%s\n", arb->info->titlu);
			//Pentru autocompleta vom avea doar 3 carti afisate
			if (autocomplete) nr++;
		}

		int i;
		for(i = 0; i < NrLitere; i++){
			if(arb->copil[i])
			{
				titlu[niv] = alphabet[i];
				afisare_T1(arb->copil[i], titlu, niv + 1, autocomplete, g);
			}
		}
	}
}

//Afisare primele 3 chei din arborele T2 primit paramteru cu prefixul respectiv
void afisare_T2(T2 arb, char *autor, char *pref, int niv, FILE *g)
{
	//Vom avea doar 3 autori afisati
	if(nr < 3){
		char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
		if(arb->frunza){
			autor[niv] = '\0';
			fprintf(g, "%s%s\n", pref, autor);
			nr++;
		}

		int i;
		for(i = 0; i < NrLitere; i++){
			if(arb->copil[i])
			{
				autor[niv] = alphabet[i];
				afisare_T2(arb->copil[i], autor, pref, niv + 1, g);
			}
		}
	}
}

//Cauta cartea in arbore T1 si afiseaza informatii despre aceasta
int search_book(T1 arb, char *titlu, FILE *g)
{
	//Daca e prefix apeleaza search_book_auto
	if(titlu[strlen(titlu) - 1] == '~'){
		titlu[strlen(titlu) - 1] = '\0';
		search_book_auto(arb, titlu, g);
	}
	else{
		int len = strlen(titlu);
		int niv;
		char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
		int i;
		T1 aux = arb;

		for(niv = 0; niv < len; niv++)
		{
			for(i = 0; i < NrLitere; i++)
				if(alphabet[i] == titlu[niv]) break;
			if(!aux->copil[i]){
				fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", 
				titlu);
				return 0;
			}

			aux = aux->copil[i];
		}

		if(aux != NULL && aux->frunza){
			fprintf(g, "Informatii recomandare: %s, %s, %d, %d\n", 
			aux->info->titlu, aux->info->autor, 
			aux->info->rating, aux->info->pagini);
			return 1;
		}
		fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", 
		titlu);
		return 0;
	}
	return 1;
}

//Cauta autorul pentru cartea respectiva
char *search_author(T1 arb, char *titlu, FILE *g)
{
		int len = strlen(titlu);
		int niv;
		char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
		int i;
		T1 aux = arb;

		for(niv = 0; niv < len; niv++)
		{
			for(i = 0; i < NrLitere; i++)
				if(alphabet[i] == titlu[niv]) break;
			if(!aux->copil[i]){
				return NULL;
			}
			aux = aux->copil[i];
		}

		if(aux != NULL && aux->frunza){
			return aux->info->autor;
		}
		return NULL;
}

//Afiseaza cartile autorului respectiv sau primii 3 autori daca parametrul e 
//prefix
int list_author(T2 arb, char *autor, FILE *g)
{
	//Daca avem prefix apelam list_author_auto
	if(autor[strlen(autor) - 1] == '~'){
		autor[strlen(autor) - 1] = '\0';
		list_author_auto(arb, autor, g);
	}
	else{
		int len = strlen(autor);
		int niv;
		char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
		int i;
		T2 aux = arb;

		for(niv = 0; niv < len; niv++)
		{
			for(i = 0; i < NrLitere; i++)
				if(alphabet[i] == autor[niv]) break;
			if(!aux->copil[i]){
				fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", 
				autor);
				return 0;
			}

			aux = aux->copil[i];
		}

		if(aux != NULL && aux->frunza){
			char s[40];
			nr = 0;
			afisare_T1(aux->info, s, 0, 0, g);
			return 1;
		}
		fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", 
		autor);
		return 0;
	}
	return 1;
}

//Cauta cartea in arborele T1 aferent autorului si afiseaza informatii
//despre carte
int search_by_author(T2 arb, char *autor, char *titlu, FILE *g)
{
	int len = strlen(autor);
	int niv;
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int i;
	T2 aux = arb;

	for(niv = 0; niv < len; niv++)
	{
		for(i = 0; i < NrLitere; i++)
			if(alphabet[i] == autor[niv]) break;
		if(!aux->copil[i]){
			fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", 
			autor);
			return 0;
		}

		aux = aux->copil[i];
	}

	if(aux != NULL && aux->frunza){
		search_book(aux->info, titlu, g);
		return 1;
	}
	fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n", 
	autor);
	return 0;
}

//Parcurge arborele T1 pina la ultimul caracter al prefixului
void search_book_auto(T1 arb, char *pref, FILE *g)
{
	
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int len = strlen (pref);
	T1 aux = arb;
	int i, j;

	for (i = 0; i < len; i++){
		for(j = 0; j < NrLitere; j++)
			if(alphabet[j] == pref[i]) break;
			
		if(aux->copil[j]) aux = aux->copil[j];
		else{
			fprintf(g, "Nicio carte gasita.\n");
			return;
		}
	}
	char s[40];
	nr = 0;
	afisare_T1(aux, s, 0, 1, g);
}

//Parcurge arborele T2 pina la ultimul caracter al prefixului
void list_author_auto(T2 arb, char *pref, FILE *g)
{
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int len = strlen (pref);
	T2 aux = arb;
	int i, j;

	for (i = 0; i < len; i++){
		for(j = 0; j < NrLitere; j++)
			if(alphabet[j] == pref[i]) break;
		if(aux->copil[j]) aux = aux->copil[j];
		else{
			fprintf(g, "Niciun autor gasit.\n");
			return;
		}
	}
	char s[40];
	nr = 0;
	afisare_T2(aux, s, pref, 0, g);
}

//Verifica daca nodul T1 are noduri copii
int nodGol_T1(T1 arb)
{
	int i;
	for(i = 0; i < NrLitere; i++)
		if(arb->copil[i])
			return 0;
	return 1;
}

//Verifica daca nodul T2 are noduri copii
int nodGol_T2(T2 arb)
{
	int i;
	for(i = 0; i < NrLitere; i++)
		if(arb->copil[i])
			return 0;
	return 1;
}

//Cauta si elimina cartea din arbore T1
T1 delete_book_T1(T1 arb, char *key, int niv)
{
	int len = strlen(key);
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int i;

	if(!arb) return NULL;

	if(niv == len){
		if(arb->frunza){
			arb->frunza = 0;
		}
		//Daca nu sunt alte carti cu aceasta subcheie elimina nodul
		if(nodGol_T1(arb)){
			arb = NULL;
		}
			
		return arb;
	}
	

	for(i = 0; i < NrLitere; i++)
		if(alphabet[i] == key[niv]) break;
	//Parcurge recursiv calea
	arb->copil[i] = delete_book_T1(arb->copil[i], key, niv + 1);

	if(nodGol_T1(arb) && arb->frunza == 0)
		arb = NULL;

	return arb;
}

//Cauta si elimina cartea din arborele T1 aferent autorului
//Daca autorul nu va mai avea carti atunci este si el eliminat din arbore T2
T2 delete_book_T2(T2 arb, char *autor, char *titlu, int niv)
{
	int len = strlen(autor);
	char alphabet[] = 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
	int i;

	if(!arb) return NULL;

	if(niv == len){
		if(arb->frunza){
			//Elimina cartea din arborele T1 aferent autorului
			delete_book_T1(arb->info, titlu, 0);
			//Daca arborele aferent autorului e gol atunci vom elimina si 
			//autorul
			if(nodGol_T1(arb->info)){
				arb->frunza = 0;
				free(arb->info);
			}
		}
	
		if(nodGol_T2(arb) && arb->frunza == 0)
			arb = NULL;
			
		return arb;
	}
	

	for(i = 0; i < NrLitere; i++)
		if(alphabet[i] == autor[niv]) break;
	
	arb->copil[i] = delete_book_T2(arb->copil[i], autor, titlu, niv + 1);

	if(nodGol_T2(arb) && arb->frunza == 0)
		arb = NULL;

	return arb;
}