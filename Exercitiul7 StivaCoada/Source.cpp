//7. Să se scrie funcţia de conversie a unei stive în listă simplu înlănţuită.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct student {
	int cod;
	char* nume;
};
struct nodls {
	student* info;
	nodls* next;
};
struct nodStiva {
	student* info;
	nodStiva* next;
};
student* citireStudent() {
	student* s = (student*)malloc(sizeof(student));
	printf("\nCare este codul elevului?");
	scanf("%d", &s->cod);
	printf("\nCare este numele elevului?");
	char buffer[50];
	scanf("%s", buffer);
	s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(s->nume, buffer);
	return s;
}
void pushStiva(nodStiva** cap,student* s) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info = s;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodStiva* temp = *cap;
		*cap = nou;
		nou->next = temp;
	}
}
int popStiva(nodStiva** cap,student** s) {
	if (*cap != NULL) {
		nodStiva* temp = *cap;
		*cap = (*cap)->next;
		*s = temp->info;
		free(temp);
		return 1;
	}
	else {
		return -1;
	}
}
void inserareListaSimpla(nodls** cap, student* s) {
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
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	printf("\nAfisare lista simpla");
	while (temp) {
		printf("\n%d %s", temp->info->cod, temp->info->nume);
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
}
void traversareStiva(nodStiva* cap) {
	nodStiva* temp = cap;
	printf("\nAfisare stiva:");
	while (temp) {
		printf("\n%d %s", temp->info->cod, temp->info->nume);
		temp = temp->next;
	}
}
void dezalocareStiva(nodStiva** cap) {
	student* s = NULL;;
	while (popStiva(cap, &s) == 1){
		free(s->nume);
		free(s);
	}
}
int main() {
	nodStiva* capStiva = NULL;
	nodls* listaFinala = NULL;
	nodStiva* stivaTemporala = NULL;
	int ok = 1;
	student* s;
	while (ok) {
	    s = citireStudent();
		pushStiva(&capStiva,s);
		printf("\nVrei sa inserezi in stiva?1=DA/0=NU");
		scanf("%d", &ok);
	}
	traversareStiva(capStiva);
	s = NULL;
	while (popStiva(&capStiva, &s) == 1) {
		pushStiva(&stivaTemporala, s);
	}
	traversareStiva(stivaTemporala);
	s = NULL;
	while (popStiva(&stivaTemporala, &s) == 1) {
		inserareListaSimpla(&listaFinala, s);
	}
	traversareStiva(capStiva);
	traversareStiva(stivaTemporala);
	traversareListaSimpla(listaFinala);
	dezalocareListaSimpla(&listaFinala);
	dezalocareStiva(&capStiva);
	dezalocareStiva(&stivaTemporala);
	system("pause");
	return 0;
}