//3. Copierea unei liste simplu inlantuite.
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
	scanf("%s",buffer);
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
void copiereListaSimpla(nodls* cap, nodls** copie) {
	nodls* temp = cap;
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = (produs*)malloc(sizeof(produs));
	nou->info->cod = temp->info->cod;
	nou->info->cantitate = temp->info->cantitate;
	nou->info->pret = temp->info->pret;
	nou->info->nume = (char*)malloc((strlen(temp->info->nume) + 1) * sizeof(char));
	nou->next = NULL;
	strcpy(nou->info->nume, temp->info->nume);
	*copie = nou;
	nodls* temp2 = *copie;
	temp = temp->next;
	while (temp) {
		nou = (nodls*)malloc(sizeof(nodls));
		nou->info = (produs*)malloc(sizeof(produs));
		nou->info->cod = temp->info->cod;
		nou->info->cantitate = temp->info->cantitate;
		nou->info->pret = temp->info->pret;
		nou->info->nume = (char*)malloc((strlen(temp->info->nume) + 1) * sizeof(char));
		strcpy(nou->info->nume, temp->info->nume);
		nou->next = NULL;
		temp2->next = nou;
		temp2 = temp2->next;
		temp = temp->next;
	}
}
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		printf("Produsul: %d, %s, %5.2f, %5.2f", temp->info->cod, temp->info->nume, temp->info->pret, temp->info->cantitate);
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
	nodls* copie = NULL;
	printf("\nCare este numarul de produse?");
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap);
	}
	printf("\n---------------------\n");
	printf("\nTraversare lista originala");
	traversareListaSimpla(cap);
	printf("\n----------------------\n");
	copiereListaSimpla(cap, &copie);
	printf("\nTraversare lista copiata");
	traversareListaSimpla(copie);
	dezalocareListaSimpla(&cap);
	dezalocareListaSimpla(&copie);
	system("pause");
	return 0;
}