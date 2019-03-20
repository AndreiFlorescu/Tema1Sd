#include <stdio.h>
#include "interface.h"

void readInput(nod **cap, int *N) {
	scanf("%d", N);
	int i;
	int time;
	double val;
	for (i = 0; i < *N; ++i) {
		scanf("%d %lf", &time, &val);
		insertLast(&(*cap), time, val);
	}

	return;
}

void printOutput(nod *cap) {
	printList(cap);
	return;
}