/* Headerul care contine structutile folosite */

#ifndef DEFTYPES
#define DEFTYPES

typedef struct nod {
	double val;
	int time;
	struct nod *next;
	//struct nod *prev;
} nod;

#endif