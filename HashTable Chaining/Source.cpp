//Hash Table Chaining
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct student {
	int cod;
	char* nume;
	float medie;
};
struct nodls {
	student* info;
	nodls* next;
};
struct hashTable {
	nodls** tabela;
	int size;
};
student* citireStudent() {
	student* s = (student*)malloc(sizeof(student));
	printf("\nCare este codul studentului?");
	scanf("%d", &s->cod);
	printf("\nCare este numele studentului?");
	char buffer[50];
	scanf("%s", buffer);
	s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(s->nume, buffer);
	printf("\nCare este media studentului?");
	scanf("%f", &s->medie);
	return s;
}
int functiaHash(hashTable tabela,int cheie) {
	return cheie % tabela.size;
}
void inserareListaSimpla(nodls** cap,student* s) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = s;
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
void stergereListaSimpla(nodls** cap,int cod) {
	if (*cap != NULL) {
		if((*cap)->info->cod==cod){
			nodls* temp = *cap;
			*cap = (*cap)->next;
			free(temp->info->nume);
			free(temp->info);
			free(temp);
		}
		else {
			nodls* temp = *cap;
			bool ok=true;
			while (temp->next&&ok) {
				if (temp->next->info->cod == cod) {
					ok = false;
				}
				else {
					temp = temp->next;
				}
			}
			if (temp->next != NULL) {
				nodls* temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2->info->nume);
				free(temp2);
			}
			else {
				printf("\nNu exista codul in lista");
			}
		}
	}
	else {
		printf("\nNu exista codul in lista");
	}
}
void traversareListaSimpla(nodls* cap,int cheie) {
	if (cap != NULL) {
		printf("\nSe afiseaza lista cu cheia %d\n", cheie);
		nodls* temp = cap;
		while (temp) {
			printf("\nStudentul %d, %s, %5.2f ", temp->info->cod, temp->info->nume, temp->info->medie);
			temp = temp->next;
		}
	}
	else {
		printf("\nNu exista nici un nod in lista cu cheia %d\n", cheie);
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
	hashTable* tab = (hashTable*)malloc(sizeof(hashTable));
	printf("\nCare este numarul de linii din tabela hash?");
	int numarLinii;
	scanf("%d", &numarLinii);
	tab->size = numarLinii;
	tab->tabela = (nodls**)malloc(tab->size * sizeof(nodls*));
	for (int i = 0; i < tab->size; i++) {
		tab->tabela[i] = NULL;
	}
	int ok = 1;
	while (ok) {
		student* s = citireStudent();
		inserareListaSimpla(&tab->tabela[functiaHash(*tab, s->cod)], s);
		printf("\nContinuati inserarea?");
		scanf("%d", &ok);
	}
	printf("\nAfisare dupa inserare");
	for (int i = 0; i < tab->size; i++) {
		if (tab->tabela[i] != NULL) {
			traversareListaSimpla(tab->tabela[i],i);
		}
	}
	printf("\n---------------------------\n");
	ok = 1;
	while (ok) {
		printf("\nCare este studentul dupa cod pe care vreti sa il stergeti?");
		scanf("%d", &ok);
		stergereListaSimpla(&tab->tabela[functiaHash(*tab, ok)], ok);
		traversareListaSimpla(tab->tabela[functiaHash(*tab,ok)],functiaHash(*tab,ok));
		printf("\nContinui stergerea?");
		scanf("%d", &ok);
	}
	for (int i = 0; i<tab->size; i++) {
		dezalocareListaSimpla(&tab->tabela[i]);
	}
	system("pause");
	return 0;
}