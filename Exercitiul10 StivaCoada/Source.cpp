//10. Scrieţi funcţia pentru ştergerea tuturor elementelor dintr-o coadă alocată dinamic.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodCoada {
	int element;
	nodCoada* next;
};
void adaugareCoada(nodCoada** cap,nodCoada** ultim,int valoare) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->element = valoare;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodCoada* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
		*ultim = nou;
	}
}
void stergereRecursiva(nodCoada** cap,nodCoada** ultim) {
	if (*cap != NULL) {
		printf("%d ", (*cap)->element);
		nodCoada* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		stergereRecursiva(cap, ultim);
	}
	else {
		*ultim = NULL;
	}
}
int main() {
	nodCoada* cap = NULL;
	nodCoada* ultim = NULL;
	int ok = 1;
	while (ok) {
		printf("\nCare este elementul inserat?");
		scanf("%d", &ok);
		adaugareCoada(&cap, &ultim, ok);
		printf("\nContinuati inserarea?1=DA/0=NU");
		scanf("%d", &ok);
	}
	stergereRecursiva(&cap, &ultim);
	system("pause");
	return 0;
}