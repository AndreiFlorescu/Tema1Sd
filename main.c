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
#include "Tasks/tasks.h"

int main (int argc, char *argv[]) {
	int N;	// numarul de puncte

// Declaram lista de puncte ---------------------------------------------------
	nod *cap = NULL;

// Declaram optiunile ---------------------------------------------------------
	char *option[] = {"--e1", "--e2", "--e3", "--u", "--c"};
	// Nu am folosit o lista pentru a salva optiunile pentru ca este neelegant

// Realizam citirea datelor ---------------------------------------------------
	readInput(&cap, &N);
	
// Rezolvam cerintele date ca argument ----------------------------------------
	int i, j;
	int query;
	for (i = 1; i < argc; ++i) {
		query = 5;
		for (j = 0; j < 5; ++j) {
			if (strcmp(argv[i], option[j]) == 0) {
				query = j;
				break;
			}
		}
		switch (query) {
			case 0:						// --e1
				removeExcept(&cap);
				break;
			case 1:						// --e2
				filterMed(&cap);
				break;
			case 2:						// --e3
				filterAvg(&cap);
				break;
			case 3:						// --u
				uniform(&cap);
				break;
			case 4:						// --c
				dataComplet(&cap);
				break;
			case 5:						// --st
				stats(&cap, argv[1]);
				freeList(&cap);
				return 0;
				break;
			default:
				break;
		}
	}

// Afisam lista de puncte finala ----------------------------------------------
	printOutput(&cap);

// Eliberam memoria -----------------------------------------------------------
	freeList(&cap);

	return 0;
}