#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define LIMSIZE 128
using namespace std;
struct Comanda {
	int cod;
	char* client;
	int numar;
	float suma;
};
struct coada {
	Comanda* info;
	coada* next;
};
void inserareCoada(coada** cap, coada** spate, Comanda* comanda) {
	coada* nou = (coada*)malloc(sizeof(coada));
	nou->next = NULL;
	nou->info = comanda;
	if (*cap == NULL) {
		*cap = nou;
		*spate = nou;
	}
	else {
		coada* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
		*spate = nou;
	}
}
void citireFisier(coada** cap, coada** spate, char* fisier) {
	char* token, fis_buf[LIMSIZE];
	FILE* f;
	f = fopen(fisier, "r");
	while (fgets(fis_buf, sizeof(fis_buf), f)) {
		Comanda* comanda = (Comanda*)malloc(sizeof(Comanda));
		token = strtok(fis_buf, ",");
		comanda->cod = atoi(token);
		token = strtok(NULL, ",");
		comanda->client = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(comanda->client, token);
		token = strtok(NULL, ",");
		comanda->numar = atoi(token);
		token = strtok(NULL, ",");
		comanda->suma = atof(token);
		inserareCoada(cap, spate, comanda);
	}
	fclose(f);
}
void traversareCoada(coada* cap) {
	coada* temp = cap;
	printf("\nSe afiseaza elementele cozii:\n");
	while (temp) {
		printf("\nCod client: %d, Nume client: %s, Numar produse: %d, Suma: %5.2f;", temp->info->cod, temp->info->client, temp->info->numar, temp->info->suma);
		temp = temp->next;
	}
}
Comanda* vectorComenzi(coada* cap,int* numar) {
	*numar = 0;
	coada* temp = cap;
	while (temp) {
		if(temp->info->suma>100){ (*numar)++; }
		temp = temp->next;
	}
	Comanda* vector = (Comanda*)malloc(*numar * sizeof(Comanda));
	temp = cap;
	int i = 0;
	while (temp) {
		if (temp->info->suma > 100) {
			vector[i].cod = temp->info->cod;
			vector[i].numar = temp->info->numar;
			vector[i].suma = temp->info->suma;
			vector[i].client = (char*)malloc((strlen(temp->info->client) + 1) * sizeof(char));
			strcpy(vector[i].client, temp->info->client);
			i++;
		}
		temp = temp->next;
	}
	return vector;
}
void dezalocareCoada(coada** cap,coada** spate) {
	coada* temp = *cap;
	while (temp) {
		coada* temp2 = temp;
		temp = temp->next;
		free(temp2->info->client);
		free(temp2);
	}
	*cap = NULL;
	*spate = NULL;
}
Comanda* extragereCoada(coada** cap,coada** spate) {
	if ((*cap)->next == NULL) {
		Comanda* comanda = (*cap)->info;
		free(*cap);
		*cap = NULL;
		*spate = NULL;
		return comanda;
	}
	else {
		Comanda* comanda = (*cap)->info;
		coada* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		return comanda;
	}
}
int main() {
	coada* cap = NULL;
	coada* spate = NULL;
	char fisier[] = "comenzi.txt";
	citireFisier(&cap, &spate, fisier);
	traversareCoada(cap);
	printf("Comanda extrasa:\n");
	Comanda* comanda_extrasa = extragereCoada(&cap, &spate);
	printf("\nCod client: %d, Nume client: %s, Numar produse: %d, Suma: %5.2f;", comanda_extrasa->cod, comanda_extrasa->client, comanda_extrasa->numar, comanda_extrasa->suma);
	free(comanda_extrasa->client);
	free(comanda_extrasa);
	printf("Restul cozii:\n");
	traversareCoada(cap);
	printf("\nAfisare vectorului de comenzi:\n");
	int numar = 0;
	Comanda* vector = vectorComenzi(cap, &numar);
	for (int i = 0; i < numar; i++) {
		printf("\nCod client: %d, Nume client: %s, Numar produse: %d, Suma: %5.2f;",vector[i].cod, vector[i].client, vector[i].numar,vector[i].suma);
	}
	for (int i = 0; i < numar - 1; i++) {
		for (int j = i + 1; j < numar; j++) {
			if (vector[i].numar < vector[j].numar) {
				Comanda aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}
	printf("\nAfisare vectorului de comenzi sortat:\n");
	for (int i = 0; i < numar; i++) {
		printf("\nCod client: %d, Nume client: %s, Numar produse: %d, Suma: %5.2f;", vector[i].cod, vector[i].client, vector[i].numar, vector[i].suma);
	}
	dezalocareCoada(&cap, &spate);
	getchar();
	getchar();
	return 0;
}
