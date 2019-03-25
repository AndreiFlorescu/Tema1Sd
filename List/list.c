#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initList(nod** cap) {
	*cap = (nod*)malloc(sizeof(nod));
	(*cap)->next = NULL;
}

void insertLast(nod** cap, int time, double val) {
    if (*cap == NULL) {
        initList(&(*cap));
        (*cap)->time = time;
        (*cap)->val = val;
        return;
    }

    nod* aux = *cap;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    nod *new = (nod*)malloc(sizeof(nod));
    new->time = time;
    new->val = val;
    new->next = NULL;
    aux->next = new;
}

int length(nod** cap) {
    if (*cap == NULL) {
        return 0;
    }

    nod *aux = *cap;

    int len = 1;
    while (aux->next != NULL) {
        len++;
        aux = aux->next;
    }
    return len;
}

void deleteHead(nod** cap) {
    nod* new = *cap;
    *cap = (*cap)->next;
    free(new); 
}

void printList(nod** cap) {
	printf("%d\n", length(&(*cap)));

    nod *aux = *cap;
    while (aux != NULL) {
        printf("%d %.2lf\n", aux->time, aux->val);
        aux = aux->next;
    }
}

void insertList (nod** cap, nod* poz, nod** cap2) {
    nod* aux1 = *cap;
    nod* aux2 = *cap2;

    while (aux1 != poz) {
        aux1 = aux1->next;
    }
    while (aux2->next != NULL) {
        aux2 = aux2->next;
    }

    aux2->next = aux1->next;
    aux1->next = *cap2;
}

void freeList(nod** cap) {
    if (*cap == NULL) {
		return;
	}
	freeList(&((*cap)->next));
	free(*cap);
}