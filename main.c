/*----------------------------------
	Subiect:	Tema 1  
	Autor:		Andrei Florescu
	Grupa:		315 CC
----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities/defTypes.h"
#include "Interface/interface.h"

int main (int argc, char *argv[]) {
	int N;	// numarul de puncte

// Declaram lista de puncte ---------------------------------------------------
	nod *cap = NULL;

// Declaram optiunile ---------------------------------------------------------
	char *option[] = {"e1", "e2", "e3", "u", "c"};
	// Nu am folosit o lista pentru a salva optiunile pentru ca este neelegant

// Realizam citirea datelor ---------------------------------------------------
	readInput(&cap, &N);

// Rezolvam cerintele date ca argument ----------------------------------------
	int i, j;
	int query;
	for (i = 0; i < argc; ++i) {
		query = -1;
		for (j = 0; j < 5; ++j) {
			if (strcmp(argv[i], option[j]) == 0) {
				query = j;
				break;
			}
		}
		switch (query) {
			case 0:
				removeExcept(&cap);
				break;
			default:
				// printf("[Eroare]: Comanda inexistenta!\n");
				// return 1;
				break;
		}
	}

// Afisam lista de puncte finala ----------------------------------------------
	printOutput(cap);

	return 0;
}