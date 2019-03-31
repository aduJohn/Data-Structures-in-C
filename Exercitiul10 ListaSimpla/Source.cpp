#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct produs {
	int cod;
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
	printf("\nCare este pretul produsului?");
	scanf("%f", &p->pret);
	printf("\nCare este cantitatea produsului?");
	scanf("%f", &p->cantitate);
	return p;
}
float valoareTotala(nodls* cap) {
	nodls* temp = cap;
	float val = 0;
	while (temp) {
		val += temp->info->cantitate*temp->info->pret;
		temp = temp->next;
	}
	return val;
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
		printf("\nProdusul: %d, %5.2f, %5.2f", temp->info->cod,temp->info->pret, temp->info->cantitate);
		temp = temp->next;
	}
}
void dezalocareListaSimpla(nodls** cap) {
	nodls* temp = *cap;
	while (temp) {
		nodls* temp2 = temp;
		temp = temp->next;
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
	printf("\n-------------------------\n");
	printf("\nValoarea total a produselor este: %5.2f", valoareTotala(cap));
	system("pause");
	return 0;
}