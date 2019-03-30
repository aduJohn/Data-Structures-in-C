//4. Stergerea unei liste simplu inlantuite.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
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
	printf("\nCare este codul produsului?");
	scanf("%d", &p->cod);
	printf("\nCare este numele produsului?");
	char buffer[50];
	scanf("%s", buffer);
	p->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p->nume, buffer);
	printf("\nCare este pretul produsului?");
	scanf("%f", &p->pret);
	printf("\nCare este cantitatea produsului?");
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
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		printf("\nProdusul: %d, %s, %5.2f, %5.2f", temp->info->cod, temp->info->nume, temp->info->pret, temp->info->cantitate);
		temp = temp->next;
	}
}
void dezalocareListaSimpla(nodls** cap) {
	nodls* temp = *cap;
	while (temp) {
		nodls* temp2 = temp;
		temp = temp->next;
		free(temp2->info->nume);
		free(temp2);
	}
	*cap = NULL;
}
int main() {
	nodls* cap = NULL;
	printf("\nCare este numarul de produse?");
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap);
	}
	printf("\nAfisarea listei inainte de stergere:");
	printf("\n--------------------------\n");
	traversareListaSimpla(cap);
	dezalocareListaSimpla(&cap);
	if (cap == NULL) {
		printf("\n--------------------\n");
		printf("\nLista a fost stearsa");
	}
	system("pause");
	return 0;
}