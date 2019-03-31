/* Headerul care contine functiile pentru rezolvarea cerintelor */

#ifndef TASKS
#define TASKS

#include "../Utilities/defTypes.h"
#include "../List/list.h"

void removeExcept(nod **cap);
void filterMed (nod **cap);
void filterAvg (nod **cap);
void uniform (nod **cap);
void dataComplet (nod **cap);
void stats (nod **cap, char *);

#endif