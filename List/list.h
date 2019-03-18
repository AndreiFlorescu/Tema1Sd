#ifndef LIST
#define LIST

#include "../Utilities/defTypes.h"

void initList(nod** cap);
void insertLast(nod** cap, int time, float val);
int length(nod* cap);
void printList(nod* cap);

#endif