#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tasks.h"

#define k 5

void removeExcept(nod **cap) {
	float sum = 0;
	float avg, dev;
	int len = lenght(*cap);
	int poz;
	nod *st = (nod*)malloc(sizeof(nod));
	nod *dr = (nod*)malloc(sizeof(nod));
	nod *middle = (nod*)malloc(sizeof(nod));
	nod *aux = (nod*)malloc(sizeof(nod));
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
	poz = k / 2;

	while (len - poz >= k / 2 + 1) {
		sum -= st->val;
		st = st->next;
		sum += dr->val;
		dr = dr->next;

		avg = sum / k;

		dev = 0;
		aux = st;
		while (aux->next != dr) {
			dev += (aux->val - avg) * (aux->val - avg);
			aux = aux->next;
		}
		dev /= k;
		dev = sqrt(dev);

		if (avg + dev < middle->val && avg - dev > middle->val) {
			// E bun
		} else {
			// Nu e bun
		}
	}
}
