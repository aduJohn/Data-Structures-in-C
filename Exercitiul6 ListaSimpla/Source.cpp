//6. Gasirea elementului aflat pe pozitia i de la sfarsitul listei.#include <iostream>
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
nodls* gasireaElementului(nodls* cap,int poz) {
	int n = numarNoduriListaSimpla(cap);
	int i = 1;
	if (poz > n || poz < 1) {
		printf("\nNu exista pozitia in lista simpla");
	}
	else {
		nodls* temp = cap;
		while (i < n-poz+1) {
			temp = temp->next;
			i++;
		}
		return temp;
	}
	return NULL;
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
	printf("\n---------------------------\n");
	printf("Care este nodul pe care vrei sa il afisezi de la capat?");
	scanf("%d", &n);
	nodls* temp = gasireaElementului(cap, n);
	if (temp == NULL) {
		printf("Elementul nu s-a gasit");
	}
	else {
		printf("Elementul este: %d, %s, %5.2f, %5.2f", temp->info->cod, temp->info->nume, temp->info->pret, temp->info->cantitate);
	}
	dezalocareListaSimpla(&cap);
	system("pause");
	return 0;
}