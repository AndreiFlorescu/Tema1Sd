#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initList(nod** cap) {
	*cap = (nod*)malloc(sizeof(nod));
	(*cap)->next = NULL;
	//(*cap)->prev = NULL;
	return;
}

void insertLast(nod** cap, int time, double val) {
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
    //new->prev = aux;
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

void deleteHead(nod** cap) {
    nod* new = (nod*)malloc(sizeof(nod));
    new = *cap;
    *cap = (*cap)->next;
    free(new); 
}

void printList(nod* cap) {
	printf("%d\n", length(cap));

    nod *aux = (nod*)malloc(sizeof(nod));
    aux = cap;
    while (aux != NULL) {
        printf("%d %.2lf\n", aux->time, aux->val);
        aux = aux->next;
    }
}

void freeList(nod** cap) {
	if (*cap == NULL) {
		return;
	}
	freeList(&((*cap)->next));
	free(*cap);
}