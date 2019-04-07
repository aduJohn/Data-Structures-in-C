//~50min
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#define DIM 101;
using namespace std;
struct Moneda {
	char moneda[4];
	char* denumire;
	char* emitent;
	int sold;
};
struct hashTable {
	Moneda** vect;
	int* sizeTabela;
};
int functieHash(char* cheie) {
	int suma = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		suma += cheie[i] % DIM;
	}
	return suma % DIM;
}
Moneda* citireMoneda() {
	Moneda* moneda = (Moneda*)malloc(sizeof(Moneda));
	printf("\nCare este abrevierea monedei?");
	scanf("%s", moneda->moneda);
	printf("\nCare este denumirea monedei?");
	char buffer[50];
	scanf("%s", buffer);
	moneda->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(moneda->denumire, buffer);
	printf("\nCare este emitentul monedei?");
	scanf("%s", buffer);
	moneda->emitent = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(moneda->emitent, buffer);
	printf("\nCare este soldul monedei?");
	scanf("%d", &moneda->sold);
	return moneda;
}
void inserareTabelaHash(hashTable tabela,Moneda* moneda) {
	if (tabela.vect[functieHash(moneda->denumire)] == NULL) {
		tabela.vect[functieHash(moneda->denumire)] = moneda;
	}
	else {
		int i = functieHash(moneda->denumire) + 1;
		while (i<*tabela.sizeTabela&&tabela.vect[i]!=NULL) {
			i++;
		}
		if (i < *tabela.sizeTabela) {
			tabela.vect[i] = moneda;
		}
		else {
			Moneda** copie = tabela.vect;
			tabela.vect = (Moneda**)malloc((*tabela.sizeTabela+1)*sizeof(Moneda*));
			for (int i = 0; i < *tabela.sizeTabela; i++) {
				tabela.vect[i] = copie[i];
			}
			tabela.vect[*tabela.sizeTabela] = moneda;
			(*tabela.sizeTabela)++;
		}
	}
}
void traversareTabelaHash(hashTable tabela) {
	printf("\nAfisare tabela Hash:");
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		if (tabela.vect[i] != NULL) {
			printf("\nPozitia %d", i);
			printf("\n\tMoneda %s %s %s %d", tabela.vect[i]->denumire, tabela.vect[i]->moneda, tabela.vect[i]->emitent, tabela.vect[i]->sold);
		}
	}
}
Moneda** cautareMoneda(hashTable tabela,int sold) {
	Moneda** copie = (Moneda**)malloc(*tabela.sizeTabela * sizeof(Moneda*));
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		copie[i] = NULL;
	}
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		if (tabela.vect[i] != NULL&&tabela.vect[i]->sold>sold) {
			copie[i] = tabela.vect[i];
		}
	}
	return copie;
}
void modificareMonede(hashTable tabela,char* cheie) {
	int i = functieHash(cheie);
	while (i<*tabela.sizeTabela&&strcmp(tabela.vect[i]->denumire, cheie) != 0) {
		i++;
	}
	if (i < *tabela.sizeTabela) {
		printf("\nCare este soldul nou introdus?");
		int soldNou;
		scanf("%d", &soldNou);
		tabela.vect[i]->sold = soldNou;
	}
	else {
		printf("\nCheie nu exista in tabela de dispersie");
	}
	printf("\nTraversare tabelei de dispersie dupa introducerea cheii:\n");
	traversareTabelaHash(tabela);
}
void dezalocareTabelaHash(hashTable tabela) {
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		if (tabela.vect[i] != NULL) {
			free(tabela.vect[i]->denumire);
			free(tabela.vect[i]->emitent);
			free(tabela.vect[i]);
		}
	}
	free(tabela.sizeTabela);
	free(tabela.vect);
}
int main() {
	hashTable tabela;
	tabela.sizeTabela = (int*)malloc(sizeof(int));
	*tabela.sizeTabela = DIM;
	tabela.vect = (Moneda**)malloc(*tabela.sizeTabela*sizeof(Moneda*));
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		tabela.vect[i] = NULL;
	}
	//CERINTA II
	printf("\nCerinta II\n");
	for (int i = 0; i < 5; i++) {
		Moneda* dummy = citireMoneda();
		inserareTabelaHash(tabela, dummy);
	}
	//CERINTA III
	printf("\nCerinta III\n");
	traversareTabelaHash(tabela);
	//CERINTA IV
	printf("\nCerinta IV\n");
	printf("\nCare este soldul pentru care se face filtrarea monedelor?");
	int soldNou = 0;
	scanf("%d", &soldNou);
	Moneda** monedeFiltrate = cautareMoneda(tabela, soldNou);
	printf("\nMonedele filtrate dupa sold:\n");
	for (int i = 0; i < *tabela.sizeTabela; i++) {
		if (monedeFiltrate[i] != NULL) {
			printf("\nPozitia %d", i);
			printf("\n\tMoneda %s %s %s %d", monedeFiltrate[i]->denumire, monedeFiltrate[i]->moneda, monedeFiltrate[i]->emitent, monedeFiltrate[i]->sold);
		}
	}
	free(monedeFiltrate);
	//CERINTA V
	printf("\nCerinta V\n");
	printf("\nCare este cheie pentru moneda careia vrei sa ii schimbi soldul?");
	char cheie[50];
	scanf("%s", cheie);
	modificareMonede(tabela, cheie);
	printf("\nFINAL\n");
	dezalocareTabelaHash(tabela);
	system("pause");
	return 0;
}