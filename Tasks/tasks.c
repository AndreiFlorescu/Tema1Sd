#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tasks.h"

#define k 5

void removeExcept(nod **cap) {
	double sum = 0;
	double avg, dev;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *st = (nod*)malloc(sizeof(nod));
	nod *dr = (nod*)malloc(sizeof(nod));
	nod *middle = (nod*)malloc(sizeof(nod));
	nod *aux = (nod*)malloc(sizeof(nod));
	st->next = *cap;
	dr = *cap;

	insertLast(&sol, (*cap)->time, (*cap)->val);
	insertLast(&sol, (*cap)->next->time, (*cap)->next->val);

	int i;
	for (i = 0; i < k - 1; ++i) {
		if (i == k / 2) {
			middle = dr;
		}
		sum += dr->val;
		dr = dr->next;
	}

	while (dr != NULL) {
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
		
		dev /= k;
		dev = (double)sqrt(dev);

		if (avg + dev >= middle->val && avg - dev <= middle->val) {
			insertLast(&sol, middle->time, middle->val);
		}

		middle = middle->next;
	}
	insertLast(&sol, middle->time, middle->val);
	insertLast(&sol, middle->next->time, middle->next->val);

	freeList(&(*cap));
	initList(&(*cap));
	*cap = sol;

	return;
}

void filterMed (nod **cap) {
	int flag;
	int i;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *st = (nod*)malloc(sizeof(nod));
	nod *dr = (nod*)malloc(sizeof(nod));
	nod *middle = (nod*)malloc(sizeof(nod));
	nod *aux = (nod*)malloc(sizeof(nod));
	
	st = *cap;
	dr = *cap;

	while (dr != NULL) {
		dr = st;
		nod *subList = NULL;
		for (i = 0; i < k; ++i) {
			insertLast(&subList, dr->time, dr->val);
			dr = dr->next;
		}
		st = st->next;

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

		insertLast(&sol, middle->time, middle->val);
		freeList(&subList);
	}

	freeList(&(*cap));
	initList(&(*cap));
	*cap = sol;

	return;
}

void filterAvg (nod **cap) {
	double sum = 0;
	double avg;

	// Lista in care salvam solutia
	nod *sol = NULL;

	nod *st = (nod*)malloc(sizeof(nod));
	nod *dr = (nod*)malloc(sizeof(nod));
	nod *middle = (nod*)malloc(sizeof(nod));
	st->next = *cap;
	dr = *cap;

	int i;
	for (i = 0; i < k - 1; ++i) {
		if (i == k / 2) {
			middle = dr;
		}
		sum += dr->val;
		dr = dr->next;
	}

	while (dr != NULL) {
		sum -= st->val;
		st = st->next;
		sum += dr->val;
		dr = dr->next;

		avg = sum / k;

		insertLast(&sol, middle->time, avg);
		
		middle = middle->next;
	}

	freeList(&(*cap));
	initList(&(*cap));
	*cap = sol;

	return;
}

void uniform (nod **cap) {
	nod *aux = (nod*)malloc(sizeof(nod));

	aux = *cap;
	while (aux->next != NULL) {
		if (aux->next->time - aux->time >= 100 && aux->next->time - aux->time <= 1000) {
			aux->next->time = (aux->next->time + aux->time) / 2;
			aux->next->val = (aux->next->val + aux->val) / 2;
		}
		aux = aux->next;
	}

	return;
}