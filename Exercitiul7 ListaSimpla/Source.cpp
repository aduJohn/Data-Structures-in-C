//7. Stabilirea simetriei unei liste.
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
int numarNoduriListaSimpla(nodls* cap) {
	int i = 0;
	nodls* temp = cap;
	while (temp) {
		i++;
		temp = temp->next;
	}
	return i;
}
nodls* elementulDePePozitia(nodls* cap, int poz) {
	nodls* temp = cap;
	int i = 1;
	while (temp) {
		if (i == poz) {
			return temp;
		}
		temp = temp->next;
		i++;
	}
	return NULL;
}
bool verificareSimetrie(nodls* cap) {
	printf("\n-------------------------\n");
	printf("\nVerificare dupa cod\n");
	int n = numarNoduriListaSimpla(cap);
	bool ok = true;
	nodls* temp = cap;
	for (int i = 0; i < n / 2; i++) {
		if (temp->info->cod != elementulDePePozitia(cap, n - i)->info->cod) {
			ok = false;
		}
		temp = temp->next;
	}
	return ok;
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
	printf("\nAfisarea listei inainte de sortare:");
	printf("\n--------------------------\n");
	traversareListaSimpla(cap);
	printf("\n-----------------------------\n");
	if (verificareSimetrie(cap)) {
		printf("\nLista simpla inlantuita este simetrica");
	}
	else {
		printf("\nLista simpla inlantuita nu este simetrica");
	}
	system("pause");
	return 0;
}