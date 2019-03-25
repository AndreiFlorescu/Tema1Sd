#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "tasks.h"

#define k 5
#define kCompl 3

void removeExcept(nod **cap) {
	double sum = 0;
	double avg, dev;

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
		dev = sqrt(dev);

		if (avg + dev >= middle->val && avg - dev <= middle->val) {
			insertLast(&sol, middle->time, middle->val);
		}

		middle = middle->next;
	}
	insertLast(&sol, middle->time, middle->val);
	insertLast(&sol, middle->next->time, middle->next->val);

	free(temp);
	freeList(&(*cap));
	*cap = sol;
}

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
	*cap = sol;
}

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

	free(temp);
	freeList(&(*cap));
	*cap = sol;
}

void uniform (nod **cap) {
	nod *aux = *cap;

	while (aux->next != NULL) {
		if (aux->next->time - aux->time >= 100 && aux->next->time - aux->time <= 1000) {
			aux->next->time = (aux->next->time + aux->time) / 2;
			aux->next->val = (aux->next->val + aux->val) / 2;
		}
		aux = aux->next;
	}
}

void dataComplet (nod **cap) {
	nod *aux;
	nod *left, *right;
	nod *leftAux, *rightAux;
	nod *compl = NULL;
	int i;
	int time;
	int len;
	double C;
	double omega[kCompl];
	double coef1, coef2;
	double value;

	aux = *cap;
	left = *cap;
	for (i = 0; i < kCompl - 1; ++i) {
		aux = aux->next;	
	}

	while (aux->next != NULL) {
		len = 0;
		if (aux->next->time - aux->time > 1000) {
			right = aux->next;
			time = aux->time + 200;
			double numit = 0;
			compl = NULL;

			for (i = 0; i < kCompl; ++i) {
				numit += ((double)i / (kCompl - 1)) * ((double)i / (kCompl - 1)) * 0.9 + 0.1;
			}

			for (i = 0; i < kCompl; ++i) {
				omega[i] = ((double)i / (kCompl - 1)) * ((double)i / (kCompl - 1)) * 0.9 + 0.1;
				omega[i] /= numit;	
			}

			leftAux = left;
			rightAux = right;
			coef1 = 0;
			coef2 = 0;
			for (i = 0; i < kCompl; ++i) {
				coef1 += leftAux->val * omega[i];
				coef2 += rightAux->val * omega[kCompl - 1 - i];

				leftAux = leftAux->next;
				rightAux = rightAux->next;
			}

			while (time < aux->next->time) {
				C = (double)(time - aux->time) / (right->time - aux->time);
				value = (1 - C) * coef1 + C * coef2;

				insertLast(&compl, time, value);
				time += 200;
			}

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
}

void stats (nod **cap, char *query) {
	int len = strlen(query);
	int step = 0;
	int i;
	for (i = 4; i < len; ++i) {
		step *= 10;
		step += query[i] - '0';
	}

	len = length(&(*cap));
	nod *aux;

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
		printf("[%d, %d] %d\n", st, st + step, cntr);
	}
}