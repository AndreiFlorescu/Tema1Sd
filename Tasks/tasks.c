#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "tasks.h"

#define k 5
#define kCompl 3

// Cerinta 1.1 --e1 -----------------------------------------------------------
void removeExcept(nod **cap) {
	double sum = 0;
	double avg, dev;
	int i;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *temp = (nod*)malloc(sizeof(nod));
	nod *st = temp;
	nod *dr = *cap;
	nod *middle;
	nod *aux;
	st->next = *cap;
	st->val = 0;
	dr = *cap;

	// Primele 2 elemente raman nesichimbate
	aux = *cap;
	for (i = 0; i < k / 2; ++i) {
		insertLast(&sol, aux->time, aux->val);
		aux = aux->next;
	}

	// Calculam prima parte a sumei din fereastra
	for (i = 0; i < k - 1; ++i) {
		if (i == k / 2) {
			middle = dr;
		}
		sum += dr->val;
		dr = dr->next;
	}

	while (dr != NULL) {
		// Calculam suma punctelor din fereastra
		sum -= st->val;
		st = st->next;
		sum += dr->val;
		dr = dr->next;

		avg = sum / k;

		dev = 0;
		aux = st;
		while (aux != dr) {
			dev += (aux->val - avg) * (aux->val - avg);
			aux = aux->next;
		}
		
		// Calculam deviatia
		dev /= k;
		dev = sqrt(dev);

		// Daca punctul respecta conditia este adaugat
		if (avg + dev >= middle->val && avg - dev <= middle->val) {
			insertLast(&sol, middle->time, middle->val);
		}

		middle = middle->next;
	}

	// Ultimele 2 elemente raman neschimbate
	for (i = 0; i < k / 2; ++i) {
		insertLast(&sol, middle->time, middle->val);
		middle = middle->next;
	}

	// Eliberam memoria
	free(temp);
	freeList(&(*cap));

	// Lista cap devine lista solutie
	*cap = sol;
}

// Cerinta 1.2.1 --e2 ---------------------------------------------------------
void filterMed (nod **cap) {
	int flag;
	int i;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *st = *cap;
	nod *dr = *cap;
	nod *middle;
	nod *aux;

	while (dr != NULL) {
		dr = st;
		nod *subList = NULL;
		// Generam sublista
		for (i = 0; i < k; ++i) {
			insertLast(&subList, dr->time, dr->val);
			dr = dr->next;
		}
		st = st->next;

		// Sortam elementele sublistei
		flag = 0;
		while (flag == 0) {
			flag = 1;
			aux = subList;
			for (i = 0; i < k - 1; ++i) {
				if (aux->val > aux->next->val) {
					double auxVal = aux->val;
					aux->val = aux->next->val;
					aux->next->val = auxVal;
					flag = 0;
				}
				aux = aux->next;
			}
		}

		middle = subList;
		for (i = 0; i < k / 2; ++i) {
			middle = middle->next;
		}

		// Adaugam elementul median al ferestrei curente
		insertLast(&sol, middle->time, middle->val);
		freeList(&subList);
	}

	// Eliberam memoria
	freeList(&(*cap));

	// Lista cap devine lista solutie
	*cap = sol;
}

// Cerinta 1.2.2 --e3 ---------------------------------------------------------
void filterAvg (nod **cap) {
	double sum = 0;
	double avg;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *st = (nod*)malloc(sizeof(nod));
	nod *temp = st;
	nod *dr = *cap;
	nod *middle;
	st->next = *cap;
	st->val = 0;
	dr = *cap;

	// Calculam prima parte a sumei din fereastra
	int i;
	for (i = 0; i < k - 1; ++i) {
		if (i == k / 2) {
			middle = dr;
		}
		sum += dr->val;
		dr = dr->next;
	}

	while (dr != NULL) {
		// Calculam suma punctelor din fereastra
		sum -= st->val;
		st = st->next;
		sum += dr->val;
		dr = dr->next;

		// Calculam media
		avg = sum / k;

		// Inseram media
		insertLast(&sol, middle->time, avg);
		
		middle = middle->next;
	}

	// Eliberam memoria
	free(temp);
	freeList(&(*cap));

	// Lista cap devine lista solutie
	*cap = sol;
}

// Cerinta 1.3 --u ------------------------------------------------------------
void uniform (nod **cap) {
	nod *aux = *cap;

	while (aux->next != NULL) {
		// Verificam daca diferenta de timp se afla in intervalul [0.1, 1] s
		if (aux->next->time - aux->time >= 100 && 
			aux->next->time - aux->time <= 1000) {
			
			// Calculam valoarea noua a punctului
			aux->next->time = (aux->next->time + aux->time) / 2;
			aux->next->val = (aux->next->val + aux->val) / 2;
		}
		aux = aux->next;
	}
}

// Cerinta 1.4 --c ------------------------------------------------------------
void dataComplet (nod **cap) {
	nod *aux;
	nod *left, *right;
	nod *leftAux, *rightAux;
	nod *compl = NULL;
	int i;
	int time;
	int len;
	double C;
	double omega;
	double coef1, coef2;
	double value;
	double numit = 0;

	// Listele care salveaza coeficientii omega
	nod *omega1 = NULL;
	nod *omega2 = NULL;
	nod *it1, *it2;

	aux = *cap;
	left = *cap;
	for (i = 0; i < kCompl - 1; ++i) {
		aux = aux->next;	
	}	

	// Calcularea lui omega
	for (i = 0; i < kCompl; ++i) {
		numit += ((double)i / (kCompl - 1)) * ((double)i / (kCompl - 1)) * 0.9 + 0.1;
	}

	for (i = 0; i < kCompl; ++i) {
		omega = ((double)i / (kCompl - 1)) * ((double)i / (kCompl - 1)) * 0.9 + 0.1;
		omega /= numit;	
		insertLast(&omega1, 0, omega);
		omega = ((double)(kCompl - 1 - i) / (kCompl - 1)) * ((double)(kCompl - 1 - i) / (kCompl - 1)) * 0.9 + 0.1;
		omega /= numit;
		insertLast(&omega2, 0, omega);
	}

	while (aux->next != NULL) {
		len = 0;
		
		// Verificam diferenta de timp
		if (aux->next->time - aux->time > 1000) {
			right = aux->next;
			time = aux->time + 200;
			compl = NULL;

			// Calcularea coeficientilor
			leftAux = left;
			rightAux = right;
			it1 = omega1;
			it2 = omega2;
			coef1 = 0;
			coef2 = 0;
			for (i = 0; i < kCompl; ++i) {
				coef1 += leftAux->val * it1->val;
				coef2 += rightAux->val * it2->val;

				leftAux = leftAux->next;
				rightAux = rightAux->next;
				it1 = it1->next;
				it2 = it2->next;
			}

			// Calcularea valorii noului punct
			while (time < aux->next->time) {
				C = (double)(time - aux->time) / (right->time - aux->time);
				value = (1 - C) * coef1 + C * coef2;

				insertLast(&compl, time, value);
				time += 200;
			}

			// Inserearea listei noi in mijlocul celei initiale
			len = length(&compl);
			insertList(&(*cap), aux, &compl);

		}
		for (i = 0; i < len - 1; ++i) {
			left = left->next;
			aux = aux->next;
		}
		left = left->next;
		aux = aux->next;
	}

	// Eliberarea memoriei
	freeList(&omega1);
	freeList(&omega2);
}

// Cerinta 1.5 Bonus --st -----------------------------------------------------
void stats (nod **cap, char *query) {
	int len = strlen(query);
	int step = 0;
	int i;

	// Aflarea lungimii intervalului
	for (i = 4; i < len; ++i) {
		step *= 10;
		step += query[i] - '0';
	}

	len = length(&(*cap));
	nod *aux;

	// Sortarea listei
	int flag = 0;
	while (flag == 0) {
		flag = 1;
		aux = *cap;
		for (i = 0; i < len - 1; ++i) {
			if (aux->val > aux->next->val) {
				double auxVal = aux->val;
				int auxTime = aux->time;

				aux->val = aux->next->val;
				aux->time = aux->next->time;

				aux->next->val = auxVal;
				aux->next->time = auxTime;

				flag = 0;
			}
			aux = aux->next;
		}
	}

	int st;
	int cntr;
	aux = *cap;
	// Calcularea numerelor de puncte din fiecare interval
	while (aux != NULL) {
		st = ((int)aux->val / step) * step;
		if (aux->val < 0) {
			st -= step;
		}
		
		cntr = 0;
		while (aux != NULL && aux->val < st + step) {
			cntr++;
			aux = aux->next;
		}

		// Afisarea intervalului si a numarului de puncte din acesta
		printf("[%d, %d] %d\n", st, st + step, cntr);
	}
}