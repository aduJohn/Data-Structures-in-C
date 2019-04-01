//3. Fiind dată o listă dublă rezultată din adunarea a două matrice rare scrieţi funcţia pentru normalizare.
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
void inserareListaDubla(nodld** cap, int i, int j, int val, int n, int m) {
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
void traversareListaDubla(nodld* cap) {
	nodld* temp = cap;
	printf("\n------------------------\n");
	printf("Matricea are %d linii si %d coloane", temp->nrLinii, temp->nrColoane);
	while (temp) {
		printf("\nNodul [%d][%d]=%d", temp->linie, temp->coloana, temp->valoare);
		temp = temp->next;
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
	nodld* cap = NULL;
	int n = 0;
	printf("\nCare este numarul de linii?");
	scanf("%d", &n);
	int m = 0;
	printf("\nCare este numarul de coloana?");
	scanf("%d", &m);
	int val = 0;
	printf("\nInserati matricea rara adunata\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("\n[%d][%d]=",i,j);
			scanf("%d", &val);
			if (val != 0) {
				inserareListaDubla(&cap, i, j, val, n, m);
			}
		}
	}
	printf("\n---------------------------\n");
	traversareListaDubla(cap);
	dezalocareListaDubla(&cap);
	system("pause");
	return 0;
}