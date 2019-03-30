//1. Interschimbarea a doua elemente prin modificarea legaturilor.
#include <iostream>
#include <malloc.h>
#include <stdio.h>
using namespace std;
struct produs {
	int cod;
	char* nume;
	float pret;
	float cantitate;
};
struct nodls {
	produs* info;
	nodls* next;
};
produs* citireProdus() {
	produs* p = (produs*)malloc(sizeof(produs));
	printf("\n Care este codul produsului?");
	scanf("%d", &p->cod);
	printf("\nCare este numele produsului?");
	char buff[50];
	scanf("%s", buff);
	p->nume = (char*)malloc((strlen(buff) + 1) * sizeof(char));
	strcpy(p->nume, buff);
	printf("\n Care este pretul produsului?");
	scanf("%f", &p->pret);
	printf("\n Care este cantitatea produsului?");
	scanf("%f", &p->cantitate);
	return p;
}
void inserareListaSimpla(nodls** cap) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = citireProdus();
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodls* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}
void interschimbareListaSimpla(nodls** cap, int n1, int n2) {
	int i = 0;
	nodls* temp = *cap;
	while ((n1 - 1) != i) {
		temp = temp->next;
		i++;
	}
	nodls* temp1 = temp;
	produs* p1 = temp1->info;
	i = 0;
	temp = *cap;
	while ((n2 - 1) != i) {
		temp = temp->next;
		i++;
	}
	nodls* temp2 = temp;
	produs* p2 = temp2->info;
	temp1->info = p2;
	temp2->info = p1;
}
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	while (temp != NULL) {
		printf("\nProdusul: %d, %s, %5.2f, %5.2f", temp->info->cod, temp->info->nume, temp->info->pret, temp->info->cantitate);
		temp = temp->next;
	}
}
void dezalocareListaSimpla(nodls** cap) {
	nodls* temp = *cap;
	while (temp != NULL) {
		nodls* temp2 = temp;
		temp = temp->next;
		free(temp2->info->nume);
		free(temp2);
	}
	*cap = NULL;
}
int main() {
	nodls* cap = NULL;
	int n = 0;
	printf("\nCare este numarul de produse?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap);
	}
	printf("\n--------------------\n");
	printf("Traversarea inainte de inversare");
	traversareListaSimpla(cap);
	printf("\n-----------------------\n");
	printf("\nCare sunt pozitiile pe care vrei sa le modifici?");
	int i, j;
	scanf("%d", &i);
	scanf("%d", &j);
	interschimbareListaSimpla(&cap, i, j);
	printf("\n--------------------\n");
	printf("Traversarea dupa inversare");
	traversareListaSimpla(cap);
	dezalocareListaSimpla(&cap);
	system("pause");
	return 0;
}