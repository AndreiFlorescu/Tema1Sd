#ifndef LIST
#define LIST

#include "../Utilities/defTypes.h"

void initList(nod** cap);
void insertLast(nod** cap, int time, double val);
int length(nod** cap);
void deleteHead(nod** cap);
void printList(nod** cap);
void insertList (nod** cap, nod* poz, nod** cap2);
void freeList(nod** cap);

#endif