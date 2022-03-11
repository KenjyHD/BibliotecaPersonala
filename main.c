/* Calmis Liviu - 311 CB */

#include "tarb.h"

int main (int argc, char *argv[])
{
	T1 arb_T1 = ConstrNod1();
	T2 arb_T2 = ConstrNod2();
	char *line = NULL;
	size_t len = 0;
	FILE *f, *g;
	TCarte *carte;

	f = fopen(argv[1], "r");
	g = fopen(argv[2], "w");
	// Citire fisier .in
	while (getline(&line, &len, f) != -1){
		carte = malloc(sizeof(TCarte));
		if(!carte) return -1;
		char *comm = strtok(line, " ");
		
		//Comanda add_book
		if(strcmp(comm, "add_book") == 0){
			char *titlu = strtok(NULL, ":");
			strcpy(carte->titlu, titlu);
			char *autor = strtok(NULL, ":");
			strcpy(carte->autor, autor);
			char *rating = strtok(NULL, ":");
			int rate = atoi(rating);
			carte->rating = rate;
			char *nr_pagini = strtok(NULL, "\n");
			int nr = atoi(nr_pagini);
			carte->pagini = nr;
			
			add_book_T1(arb_T1, titlu, carte);
			add_book_T2(arb_T2, autor, carte);
			
		}

		//Comanda search_book
		if(strcmp(comm, "search_book") == 0){
			char *titlu = strtok(NULL, "\n");

			search_book(arb_T1, titlu, g);
		}

		//Comanda list_author
		if(strcmp(comm, "list_author") == 0){
			char *autor = strtok(NULL, "\n");

			list_author(arb_T2, autor, g);
		}

		//Comanda search_by_author
		if(strcmp(comm, "search_by_author") == 0){
			char *autor = strtok(NULL, ":");
			char *titlu = strtok(NULL, "\n");

			//Daca in comanda a fost dat doar autorul apelez fn list_author
			if(autor[strlen(autor) - 1] == '\n'){
				autor[strlen(autor) - 1] = '\0';
				list_author(arb_T2, autor, g);
			}
			else
				search_by_author(arb_T2, autor, titlu, g);
		}
		//Comanda delete_book
		if(strcmp(comm, "delete_book") == 0){
			char *titlu = strtok(NULL, "\n");

			//Caut autorul cartii
			char *autor = search_author(arb_T1, titlu, g);
			//Daca nu-l gasesc atunci cartea nu a fost adaugata
			if(autor){
				delete_book_T1(arb_T1, titlu, 0);
				delete_book_T2(arb_T2, autor, titlu, 0);
			}
			else 
				fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", 
				titlu);
		}
	}
	return 0;
}
