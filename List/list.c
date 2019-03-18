#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initList(nod** cap) {
	*cap = (nod*)malloc(sizeof(nod));
	(*cap)->next = NULL;
	(*cap)->prev = NULL;
	return;
}

void insertLast(nod** cap, int time, float val) {
    if (*cap == NULL) {
        initList(&(*cap));
        (*cap)->time = time;
        (*cap)->val = val;
        return;
    }

    nod* aux = (nod*)malloc(sizeof(nod));
    aux = *cap;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    nod *new = (nod*)malloc(sizeof(nod));
    new->time = time;
    new->val = val;
    new->next = NULL;
    new->prev = aux;
    aux->next = new;
    return;
}

int length(nod* cap) {
    nod *aux = (nod*)malloc(sizeof(nod));
    aux = cap;

    if (cap == NULL) {
        return 0;
    }

    int len = 1;
    while (aux->next != NULL) {
        len++;
        aux = aux->next;
    }
    return len;
}

void printList(nod* cap) {
	printf("%d\n", length(cap));

    nod *aux = (nod*)malloc(sizeof(nod));
    aux = cap;
    while (aux != NULL) {
        printf("%d %.2f\n", aux->time, aux->val);
        aux = aux->next;
    }
}