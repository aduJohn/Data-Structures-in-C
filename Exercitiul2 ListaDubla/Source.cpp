//2. Sa se scrie functia pentru adunarea a doua matrice rare memorate ca liste duble.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodld {
	int linie;
	int coloana;
	int valoare;
	int nrLinii;
	int nrColoane;
	nodld* next;
	nodld* prev;
};
void inserareListaDubla(nodld** cap, int i, int j, int val,int n,int m) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->coloana = j;
	nou->linie = i;
	nou->valoare = val;
	nou->nrLinii = n;
	nou->nrColoane = m;
	nou->next = NULL;
	nou->prev = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodld* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
	}
}
void citireMatriceRara(nodld** cap) {
	printf("\nCare este numarul de linii?");
	int n = 0;
	scanf("%d", &n);
	printf("\nCare este numarul de coloane");
	int m = 0;
	int val;
	scanf("%d", &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &val);
			if (val != 0) {
				inserareListaDubla(cap, i, j, val, n, m);
			}
		}
	}
}
int gasireElement(nodld* cap, int i, int j) {
	nodld* temp = cap;
	while (temp) {
		if (temp->linie == i && temp->coloana == j) {
			return temp->valoare;
		}
		temp = temp->next;
	}
	return 0;
}
void afisareMatriceListaDubla(nodld* cap) {
	int n = cap->nrLinii;
	int m = cap->nrColoane;
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", gasireElement(cap, i, j));
		}
		printf("\n");
	}
}
void traversareListaDubla(nodld* cap) {
	nodld* temp = cap;
	printf("\n------------------------\n");
	printf("Matricea are %d linii si %d coloane", temp->nrLinii, temp->nrColoane);
	while (temp) {
		printf("\nNodul [%d][%d]=%d", temp->linie, temp->coloana, temp->valoare);
		temp = temp->next;
	}
}
nodld* sumaMatriceRara(nodld* cap1, nodld* cap2) {
	nodld* suma = NULL;
	if (cap1->nrColoane == cap2->nrColoane&&cap1->nrLinii == cap2->nrLinii) {
		for (int i = 0; i < cap1->nrLinii; i++) {
			for (int j = 0; j < cap2->nrColoane; j++) {
				if (gasireElement(cap1, i, j) + gasireElement(cap2, i, j) != 0) {
					inserareListaDubla(&suma, i, j, gasireElement(cap1, i, j) + gasireElement(cap2, i, j), cap1->nrLinii, cap1->nrColoane);
				}
			}
		}
		printf("\nSuma a fost efectuata cu succes:\n");
		afisareMatriceListaDubla(suma);
		return suma;
	}
	else {
		printf("\nSuma nu s-a putut efectua...");
		return NULL;
	}
}
void dezalocareListaDubla(nodld** cap) {
	nodld* temp = *cap;
	while (temp) {
		nodld* temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	*cap = NULL;
}
int main() {
	nodld* cap1 = NULL;
	nodld* cap2 = NULL;
	citireMatriceRara(&cap1);
	printf("\n");
	traversareListaDubla(cap1);
	printf("\n");
	afisareMatriceListaDubla(cap1);
	printf("\n");
	citireMatriceRara(&cap2);
	printf("\n");
	traversareListaDubla(cap2);
	printf("\n");
	afisareMatriceListaDubla(cap2);
	printf("\n----------------------------\n");
	nodld* suma = sumaMatriceRara(cap1, cap2);
	dezalocareListaDubla(&cap1);
	dezalocareListaDubla(&cap2);
	dezalocareListaDubla(&suma);
	system("pause");
	return 0;
}