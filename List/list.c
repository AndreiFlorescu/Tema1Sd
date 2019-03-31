#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Initializarea listei -------------------------------------------------------
void initList(nod** cap) {
	*cap = (nod*)malloc(sizeof(nod));
	(*cap)->next = NULL;
}

// Inserarea la sfarsit -------------------------------------------------------
void insertLast(nod** cap, int time, double val) {
    if (*cap == NULL) {         // Daca lista e nula o initializam
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

// Lungimea listei ------------------------------------------------------------
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

// Stergerea primului element al listei ---------------------------------------
void deleteHead(nod** cap) {
    nod* new = *cap;
    *cap = (*cap)->next;
    free(new); 
}

// Afisarea listei ------------------------------------------------------------
void printList(nod** cap) {
	printf("%d\n", length(&(*cap)));

    nod *aux = *cap;
    while (aux != NULL) {
        printf("%d %.2lf\n", aux->time, aux->val);
        aux = aux->next;
    }
}

// Inserarea unei liste intr-o lista ------------------------------------------
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

// Eliberarea memoriei --------------------------------------------------------
void freeList(nod** cap) {
    if (*cap == NULL) {         // Daca lista e nula nu avem ce elibera
		return;
	}
	freeList(&((*cap)->next));
	free(*cap);
}