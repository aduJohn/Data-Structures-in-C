//basic linear probing
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct student {
	int cod;
	char* nume;
	float medie;
};
void afisareMeniu() {
	printf("\n------------------------------\n");
	printf("\n1.Afisare tabela.");
	printf("\n2.Cautare element.");
	printf("\n3.Inserare element.");
	printf("\n4.Stergere element.");
	printf("\n0.Exit.");
	printf("\nINFO: Nu adaugati sau stergeti elemente care au codul -1!!!!!");
	printf("\n------------------------------\n");
}
student citireStudent() {
	student s;
	printf("\nCare este codul studentului?");
	scanf("%d", &s.cod);
	printf("\nCare este numele studentului?");
	char buffer[50];
	scanf("%s", buffer);
	s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(s.nume, buffer);
	printf("\nCare este media studentului?");
	scanf("%f", &s.medie);
	return s;
}
int functieHash(int dimensiuneHash,int cheie) {
	return cheie%dimensiuneHash;
}
void inserare(student** tabelaStudenti,int* dimensiuneTabela,student s) {
	if ((*tabelaStudenti)[functieHash(*dimensiuneTabela, s.cod)].cod==-1) {
		(*tabelaStudenti)[functieHash(*dimensiuneTabela, s.cod)] = s;
	}
	else {
		int i = functieHash(*dimensiuneTabela, s.cod) + 1;
		while (i < *dimensiuneTabela && (*tabelaStudenti)[i].cod != -1) {
			i++;
		}
		if (i == *dimensiuneTabela) {
			student* copieTabela = *tabelaStudenti;
			(*dimensiuneTabela)++;
			*tabelaStudenti = (student*)malloc(*dimensiuneTabela * sizeof(student));
			for (int j = 0; j < *dimensiuneTabela - 1; j++) {
				(*tabelaStudenti)[i] = copieTabela[i];
			}
			(*tabelaStudenti)[*dimensiuneTabela - 1] = s;
			free(copieTabela);
		}
		else {
			(*tabelaStudenti)[i] = s;
		}
	}
}
void cautare(student* tabelaStudenti,int dimensiuneTabela,int cheie) {
	if (tabelaStudenti[functieHash(dimensiuneTabela, cheie)].cod == -1) {
		printf("\nNu exista element pe pozitia aleasa din tabela!");
	}
	else {
		int i = functieHash(dimensiuneTabela, cheie);			
		while (i < dimensiuneTabela&&tabelaStudenti[i].cod != cheie) {
			i++;
		}
		if (i < dimensiuneTabela) {
			printf("\nStudentul: %d, %s, %f", tabelaStudenti[i].cod, tabelaStudenti[i].nume, tabelaStudenti[i].medie);
		}
		else {
			printf("\nNu exista element pe pozitia aleasa din tabela!");
		}
	}
}
void afisare(student* tabelaStudenti,int dimensiuneTabela) {
	for (int i = 0; i < dimensiuneTabela; i++) {
		if (tabelaStudenti[i].cod != -1) {
			printf("\nStudentul: %d, %s, %f", tabelaStudenti[i].cod, tabelaStudenti[i].nume, tabelaStudenti[i].medie);
		}
	}
}
void stergere(student** tabelaStudenti,int dimensiuneTabela,int cheie) {
	if ((*tabelaStudenti)[functieHash(dimensiuneTabela,cheie)].cod==-1) {
		printf("\nNu exista nici un element pe pozitia din tabela!");
	}
	else {
		int i = functieHash(dimensiuneTabela, cheie);
		while (i < dimensiuneTabela && (*tabelaStudenti)[i].cod != cheie) {
			i++;
		}
		if (i<dimensiuneTabela) {
			free((*tabelaStudenti)[i].nume);
			int ultimaPozitie = i;
			int pozitieCurenta = ultimaPozitie + 1;
			while (pozitieCurenta < dimensiuneTabela) {
				if (functieHash(dimensiuneTabela, (*tabelaStudenti)[pozitieCurenta].cod) == functieHash(dimensiuneTabela, cheie)) {
					(*tabelaStudenti)[ultimaPozitie] = (*tabelaStudenti)[pozitieCurenta];
					ultimaPozitie = pozitieCurenta;
				}
				pozitieCurenta++;
			}
			(*tabelaStudenti)[ultimaPozitie].cod = -1;
			(*tabelaStudenti)[ultimaPozitie].medie = -1;
		}
		else {
			printf("\nNu exista nici un element pe pozitia din tabela!");
		}
	}
}
void dezalocare(student** tabelaStudenti, int* dimensiuneTabela) {
	for (int i = 0; i < *dimensiuneTabela; i++) {
		if ((*tabelaStudenti)[i].cod != -1) {
			free((*tabelaStudenti)[i].nume);
		}
	}
	*dimensiuneTabela = 0;
	free(*tabelaStudenti);
}
int main() {
	student* tabelaStudenti;
	int dimensiuneTabela;
	printf("\nCare este dimensiunea tabelei Hash?");
	scanf("%d", &dimensiuneTabela);
	tabelaStudenti = (student*)malloc(dimensiuneTabela * sizeof(student));
	for (int i = 0; i < dimensiuneTabela; i++) {
		tabelaStudenti[i].medie = -1;
		tabelaStudenti[i].cod = -1;
		tabelaStudenti[i].nume = NULL;
	}
	int optiune=0;
	int cod=0;
	afisareMeniu();
	scanf("%d", &optiune);
	while (optiune) {
		system("cls");
		switch (optiune) {
		case 1:afisare(tabelaStudenti, dimensiuneTabela); break;
		case 2:
			printf("\nCare este codul ales?");
			scanf("%d", &cod);
			cautare(tabelaStudenti, dimensiuneTabela, cod);
		break;
		case 3:
			student s = citireStudent();
			inserare(&tabelaStudenti, &dimensiuneTabela, s);
		break;
		case 4:
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