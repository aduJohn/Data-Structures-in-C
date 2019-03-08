#include <iostream>
#include <stdint.h>
#include <malloc.h>
using namespace std;

struct Produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};
struct Nod {
	Produs info;
	Nod* next;
};
Nod* adaugare(Nod* cap,Produs* p) {
	Nod* nodls = (Nod*)malloc(sizeof(Nod));
	nodls->info.cantitate = p->cantitate;
	nodls->info.cod = p->cod;
	nodls->info.pret = p->pret;
	nodls->info.denumire = (char*)malloc((strlen(p->denumire) + 1) * sizeof(char));
	strcpy(nodls->info.denumire, p->denumire);
	nodls->next = NULL;
	if (cap == NULL) {
		cap = nodls;
	}
	else {
		Nod* temp = cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodls;
	}
	return cap;
}
void traversare(Nod* cap) {
	Nod* temp = cap;
	while (temp !=NULL) {
		printf("\nProdusul: Cod: %d, Denumire: %s, Pret: %5.2f, Cantitate: %5.2f ", temp->info.cod, temp->info.denumire, temp->info.pret, temp->info.cantitate);
		temp = temp->next;
	}
}
void dezalocare(Nod* cap) {
	Nod* temp = cap;
	while (temp!= NULL) {
		free(temp->info.denumire);
		Nod* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}

}
int main() {
	Produs* p = NULL;
	Nod* cap = NULL;
	int n;
	char buff[50];
	printf("Care produse intra in lista?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		p = (Produs*)malloc(sizeof(Produs));
		printf("Care este codul produsului %d ?",i+1);
		scanf("%d", &p->cod);
		printf("Care este denumire produsului %d ?", i + 1);
		scanf("%s", buff);
		p->denumire = (char*)malloc((strlen(buff) + 1) * sizeof(char));
		strcpy(p->denumire, buff);
		printf("Care este pretul produsului %d ?", i + 1);
		scanf("%f", &p->pret);
		printf("Care este cantitatea produsului %d ?", i + 1);
		scanf("%f", &p->cantitate);
		cap=adaugare(cap, p);
		free(p->denumire);
		free(p);
	}
	traversare(cap);
	dezalocare(cap);
	system("pause");
	return 0;
}