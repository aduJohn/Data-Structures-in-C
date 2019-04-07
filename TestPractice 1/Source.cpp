//10:44
//11:56 STOP + 10(min pauza)
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define DIM 200;
using namespace std;
struct Fisier {
	char* denumire;
	char* path;
	char* extensie;
	unsigned int dimensiune;
};
struct nodls {
	Fisier* info;
	nodls* next;
};
struct hashT {
	nodls** vect;
	int size;
};
int functieHash(int dimensiuneTabela,char* cheie) {
	int suma = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		suma += cheie[i] % dimensiuneTabela;
	}
	return suma%dimensiuneTabela;
}
Fisier* citireFisier() {
	Fisier* file = (Fisier*)malloc(sizeof(Fisier));
	char buffer[50];
	printf("\nCare este denumire fisierului?");
	scanf("%s", buffer);
	file->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->denumire, buffer);
	printf("\nCare este denumire calea fisierului?");
	scanf("%s", buffer);
	file->path = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->path, buffer);
	printf("\nCare este extensia fisierului?");
	scanf("%s", buffer);
	file->extensie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->extensie, buffer);
	printf("\nCare este dimensiunea fisierului?");
	scanf("%d", &file->dimensiune);
	return file;

}
void inserareListaSimpla(nodls** cap,Fisier* file) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = file;
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
		printf("\n\tFisier:");
		printf("\n\tDenumire: %s", temp->info->denumire);
		printf("\n\tCale: %s", temp->info->path);
		printf("\n\tExtensie: %s", temp->info->extensie);
		printf("\n\tDimensiune: %d", temp->info->dimensiune);
		temp = temp->next;
	}
}
void dezalocareListaSimpla(nodls** cap) {
	nodls* temp = *cap;
	while (temp) {
		nodls* temp2 = temp;
		temp = temp->next;
		free(temp2->info->denumire);
		free(temp2->info->extensie);
		free(temp2->info->path);
		free(temp2);
	}
	*cap = NULL;
}
Fisier* cautareHashTable(hashT tabelaHash, char* cheie) {
	nodls* temp = tabelaHash.vect[functieHash(tabelaHash.size, cheie)];
	while (temp != NULL && strcmp(temp->info->denumire, cheie) != 0) {
		temp = temp->next;
	}
	if (temp) {
		return temp->info;
	}
	else {
		return NULL;
	}
}
void traversareHashTable(hashT tabelaHash) {
	for (int i = 0; i < tabelaHash.size; i++) {
		if (tabelaHash.vect[i] != NULL) {
			printf("\nPozitia %d", i);
			traversareListaSimpla(tabelaHash.vect[i]);
		}
	}
}
void modificareHashTable(hashT tabelaHash, char* cheie, char* extensieNoua) {
	Fisier* fileTemp = cautareHashTable(tabelaHash, cheie);
	if (fileTemp) {
		free(fileTemp->extensie);
		fileTemp->extensie = (char*)malloc((strlen(extensieNoua) + 1) * sizeof(char));
		strcpy(fileTemp->extensie, extensieNoua);
		traversareHashTable(tabelaHash);
	}
	else {
		printf("\nNu s-a identificat cheie ceruta");
	}
}
void inserareHashTable(hashT tabelaHash) {
	Fisier* file = citireFisier();
	int hashCode = functieHash(tabelaHash.size, file->denumire);
	inserareListaSimpla(&tabelaHash.vect[hashCode], file);
}
void dezalocareHashTable(hashT tabelaHash) {
	for (int i = 0; i < tabelaHash.size; i++) {
		if (tabelaHash.vect[i] != NULL) {
			dezalocareListaSimpla(&tabelaHash.vect[i]);
		}
	}
}
int main() {
	hashT tabela;
	tabela.size = DIM;
	tabela.vect = (nodls**)malloc(sizeof(nodls*)*tabela.size);
	for (int i = 0; i < tabela.size; i++) {
		tabela.vect[i] = NULL;
	}
	//CERINTA II
	printf("\nCerinta II\n");
	printf("\nCare sunt cele 5 fisiere?");
	for (int i = 0; i < 5; i++) {
		inserareHashTable(tabela);
	}
	//CERINTA III
	printf("\nCerinta III\n");
	traversareHashTable(tabela);
	//CERINTA IV
	printf("\nCerinta IV\n");
	printf("\nCare este fisierul cautat dupa denumire?");
	char buffer[50];
	scanf("%s", buffer);
	Fisier* file = cautareHashTable(tabela,buffer);
	if (file) {
		printf("\n\tFisier:");
		printf("\n\tDenumire: %s", file->denumire);
		printf("\n\tCale: %s", file->path);
		printf("\n\tExtensie: %s", file->extensie);
		printf("\n\tDimensiune: %d", file->dimensiune);
	}
	else {
		printf("\nFisierul nu exista");
	}
	file = NULL;
	//CERINTA V
	printf("\nCerinta V\n");
	printf("\nCare este fisierul modificat dupa denumire?");
	scanf("%s", buffer);
	printf("\nCare este noua extensie?");
	char altBuffer[50];
	scanf("%s", altBuffer);
	modificareHashTable(tabela, buffer, altBuffer);
	dezalocareHashTable(tabela);
	system("pause");
	return 0;
}