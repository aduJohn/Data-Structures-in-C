//basic quadratic probing
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
#define DIM 101;
struct student {
	int cod;
	char* nume;
	float medie;
};
int functieHash(int dimensiuneTabela, int cheie) {
	return cheie % DIM;
}
//cand inserezi multe valori se va schimba dimensiunea si se pierde ordinea tabelei
student citireStudent() {
	student s;
	printf("\nCare este codul studentului?");
	scanf("%d", &s.cod);
	printf("\nCare este numele studentului?");
	char buffer[50];
	scanf("%s", buffer);
	s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(s.nume, buffer);
	printf("\nCare este media studentului");
	scanf("%f", &s.medie);
	return s;
}
void afisareMeniu() {
	printf("\n------------------------------\n");
	printf("\n1.Afisare tabela.");
	printf("\n2.Inserare element.");
	printf("\n3.Stergere element.");
	printf("\n0.Exit.");
	printf("\n------------------------------\n");
}
void inserare(student** tabelaStudenti, int* dimensiuneTabela,student s) {
	if ((*tabelaStudenti)[functieHash(*dimensiuneTabela, s.cod)].cod == -1) {
		(*tabelaStudenti)[functieHash(*dimensiuneTabela, s.cod)] = s;
	}
	else {
		int i = 0;
		int pozitie = functieHash(*dimensiuneTabela, s.cod);
		while (pozitie < *dimensiuneTabela && (*tabelaStudenti)[pozitie].cod != -1) {
			i++;
			pozitie = functieHash(*dimensiuneTabela, s.cod) + (i*i);
		}
		if (pozitie >= *dimensiuneTabela) {
			student* copie = *tabelaStudenti;
			*tabelaStudenti = (student*)malloc((pozitie + 1) * sizeof(student));
			for (int i = 0; i < *dimensiuneTabela; i++) {
				(*tabelaStudenti)[i] = copie[i];
			}
			for(int i=*dimensiuneTabela;i<pozitie+1;i++){
				(*tabelaStudenti)[i].cod = -1;
				(*tabelaStudenti)[i].medie = -1;
				(*tabelaStudenti)[i].nume = NULL;
			}
			*dimensiuneTabela = pozitie + 1;
			(*tabelaStudenti)[pozitie] = s;
			free(copie);
		}
		else {
			(*tabelaStudenti)[pozitie] = s;
		}
	}
}
void traversare(student* tabelaStudenti,int dimensiuneTabela) {
	for (int i = 0; i < dimensiuneTabela; i++) {
		if (tabelaStudenti[i].cod != -1) {
			printf("\nPozitie: %d", i);
			printf("\nStudentul %d, %s, %5.2f", tabelaStudenti[i].cod, tabelaStudenti[i].nume, tabelaStudenti[i].medie);
		}
	}
}
void stergere(student** tabelaStudenti,int dimensiuneTabela,int cod) {
	if ((*tabelaStudenti)[functieHash(dimensiuneTabela, cod)].cod == -1) {
		printf("\nNu exista nodul in tabela");
	}
	else {
		int i = functieHash(dimensiuneTabela, cod);
		int pas = 0;
		while (i < dimensiuneTabela&&(*tabelaStudenti)[i].cod != cod) {
			pas++;
			i = functieHash(dimensiuneTabela, cod) + (pas*pas);
		}
		if (i < dimensiuneTabela) {
			free((*tabelaStudenti)[i].nume);
			int ultimaPozitie = i;
			pas++;
			int pozitiaCurenta = functieHash(dimensiuneTabela, cod) +(pas*pas);
			while (pozitiaCurenta < dimensiuneTabela) {
				if (functieHash(dimensiuneTabela,cod)==functieHash(dimensiuneTabela,(*tabelaStudenti)[pozitiaCurenta].cod)) {
					(*tabelaStudenti)[ultimaPozitie] = (*tabelaStudenti)[pozitiaCurenta];
					ultimaPozitie = pozitiaCurenta;
				}
				pas++;
				pozitiaCurenta = functieHash(dimensiuneTabela, cod) + (pas*pas);
			}
			(*tabelaStudenti)[ultimaPozitie].cod = -1;
			(*tabelaStudenti)[ultimaPozitie].medie = -1;
			(*tabelaStudenti)[ultimaPozitie].nume = NULL;
		}
		else {
			printf("\nNu exista nodul in tabela");
		}
		
	}
}
void dezalocare(student** tabelaStudenti,int* dimensiuneTabela) {
	for (int i = 0; i < *dimensiuneTabela; i++) {
		if ((*tabelaStudenti)[i].nume != NULL) {
			free((*tabelaStudenti)[i].nume);
		}
	}
	*dimensiuneTabela = 0;
	free(*tabelaStudenti);
	*tabelaStudenti = NULL;
}
int main() {
	student* tabelaStudenti = NULL;
	int dimensiuneTabela = DIM;
	tabelaStudenti = (student*)malloc(dimensiuneTabela * sizeof(student));
	for (int i = 0; i < dimensiuneTabela; i++) {
		tabelaStudenti[i].medie = -1;
		tabelaStudenti[i].cod = -1;
		tabelaStudenti[i].nume = NULL;
	}
	int optiune = 0;
	int cod = 0;
	afisareMeniu();
	scanf("%d", &optiune);
	while (optiune) {
		system("cls");
		switch (optiune) {
		case 1:traversare(tabelaStudenti, dimensiuneTabela); break;
		case 2:
			student s = citireStudent();
			inserare(&tabelaStudenti, &dimensiuneTabela, s);
			break;
		case 3:
			printf("\nCare este codul elementului sters?");
			scanf("%d", &cod);
			stergere(&tabelaStudenti, dimensiuneTabela, cod);
			break;
		}
		afisareMeniu();
		scanf("%d", &optiune);
	}
	dezalocare(&tabelaStudenti, &dimensiuneTabela);
	return 0;
}