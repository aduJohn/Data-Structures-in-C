//4.Să se descrie modul de organizare a unei cozi alocate ca vector şi să se scrie funcţia de adăugare a unui element.
//5.Să se descrie modul de organizare a unei cozi alocate ca vector şi să se scrie funcţia de ştergere a unui element.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct elementCoada {
	int valoare;
};
void adaugareCoadaVector(elementCoada** cap,int* n) {
	printf("\nCare este elementul inserat?");
	int ceva;
	scanf("%d", &ceva);
	if (*cap != NULL) {
		elementCoada* copie = *cap;
		(*n)++;
		*cap = (elementCoada*)malloc(*n * sizeof(elementCoada));
		for (int i = 0; i < (*n) - 1; i++) {
			(*cap + i)->valoare = (copie + i)->valoare;
		}
		(*cap + (*n) - 1)->valoare = ceva;
		free(copie);
	}
	else {
		*cap = (elementCoada*)malloc(sizeof(elementCoada));
		(*n)++;
		(*cap)->valoare = ceva;
	}
}
void stergereCoadaVector(elementCoada** cap,int* n) {
	if (*cap != NULL) {
		(*n)--;
		if (*n == 0) {
			*cap = NULL;
		}
		else {
			elementCoada* copie = *cap;
			*cap = (elementCoada*)malloc(*n * sizeof(elementCoada));
			for (int i = 0; i < *n; i++) {
				(*cap + i)->valoare = (copie + i + 1)->valoare;
			}
			free(copie);
		}
	}
}
void traversareCoadaVector(elementCoada* cap,int n) {
	printf("\nAfisare coada:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", (cap + i)->valoare);
	}
}
void dezalocareCoadaVector(elementCoada** cap,int* n) {
	free(*cap);
	(*n) = 0;
}
int main() {
	elementCoada* cap = NULL;
	int numarElementeCoada = 0;
	int ok = 1;
	while (ok) {
		adaugareCoadaVector(&cap, &numarElementeCoada);
		printf("\nContinuati inserarea?1=DA/0=NU");
		scanf("%d", &ok);
	}
	traversareCoadaVector(cap, numarElementeCoada);
	printf("\nStergeti?1=DA/0=NU");
	scanf("%d", &ok);
	while (ok) {
		stergereCoadaVector(&cap, &numarElementeCoada);
		traversareCoadaVector(cap, numarElementeCoada);
		printf("\nContinuati stergerea?1=DA/0=NU");
		scanf("%d", &ok);
		if (numarElementeCoada == 0) {
			ok = 0;
		}
	}
	traversareCoadaVector(cap, numarElementeCoada);
	dezalocareCoadaVector(&cap, &numarElementeCoada);
	system("pause");
	return 0;
}