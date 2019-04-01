//1. Scrieţi funcţia pentru conversia unei liste duble în listă simplă.
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
struct nodld {
	student* info;
	nodld* next;
	nodld* prev;
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
	printf("\nCare este media elevului?");
	scanf("%f", &s->medie);
	return s;
}
void inserareListaDubla(nodld** cap,nodld** ultim) {
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info = (student*)malloc(sizeof(student));
	nou->info = citireStudent();
	nou->next = NULL;
	nou->prev = NULL;
	if (*cap == NULL) {
		*cap = nou;
		*ultim = nou;
	}
	else {
		nodld* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		*ultim = nou;
		temp->next = *ultim;
		(*ultim)->prev = temp;
	}
}
void stergerePrimulNodListaDubla(nodld** cap,nodld** ultim) {
	if (*cap != NULL) {
		if (*cap == *ultim) {
			free((*cap)->info->nume);
			free((*cap)->info);
			free(*cap);
			*cap = NULL;
			*ultim = NULL;
		}
		else {
			nodld* temp = *cap;
			*cap = temp->next;
			free(temp->info->nume);
			free(temp);
			(*cap)->prev = NULL;
		}
	}
}
nodls* conversieListaDubla(nodld** cap, nodld** ultim) {
	nodls* capLS = NULL;
	if (*cap != NULL) {
		nodls* nou = (nodls*)malloc(sizeof(nodls));
		nou->info = (student*)malloc(sizeof(student));
		nou->info->cod = (*cap)->info->cod;
		nou->info->nume = (char*)malloc((strlen((*cap)->info->nume) + 1) * sizeof(char));
		strcpy(nou->info->nume, (*cap)->info->nume);
		nou->info->medie = (*cap)->info->medie;
		nou->next = NULL;
		capLS = nou;
		stergerePrimulNodListaDubla(cap, ultim);
		nodls* tempLS = capLS;
		while (*cap) {
			nou = (nodls*)malloc(sizeof(nodls));
			nou->info = (student*)malloc(sizeof(student));
			nou->info->cod = (*cap)->info->cod;
			nou->info->nume = (char*)malloc((strlen((*cap)->info->nume) + 1) * sizeof(char));
			strcpy(nou->info->nume, (*cap)->info->nume);
			nou->info->medie = (*cap)->info->medie;
			nou->next = NULL;
			tempLS->next=nou;
			tempLS = tempLS->next;
			stergerePrimulNodListaDubla(cap, ultim);
		}
	}
	return capLS;
}
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		printf("\nStudentul: %d, %s, %5.2f ", temp->info->cod, temp->info->nume, temp->info->medie);
		temp = temp->next;
	}
}
void traversare(nodld* cap) {
	nodld* temp = cap;
	while (temp) {
		printf("\nStudentul: %d, %s, %5.2f ", temp->info->cod, temp->info->nume, temp->info->medie);
		temp = temp->next;
	}
}
void traversareInversa(nodld* ultim) {
	nodld* temp = ultim;
	while (temp) {
		printf("\nStudentul: %d, %s, %5.2f ", temp->info->cod, temp->info->nume, temp->info->medie);
		temp = temp->prev;
	}
}
void dezalocareListaDubla(nodld** cap,nodld** ultim) {
	nodld* temp = *cap;
	while (temp) {
		nodld* temp2 = temp;
		temp = temp->next;
		free(temp2->info->nume);
		free(temp2->info);
		free(temp2);
	}
	*cap = NULL;
	*ultim = NULL;
}
int main() {
	nodld* cap = NULL;
	nodld* ultim = NULL;
	int n = 0;
	printf("\nCare este numarul de studenti cititi?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaDubla(&cap, &ultim);
	}
	printf("\n------------------------------\n");
	traversare(cap);
	printf("\n---------------------------------\n");
	traversareInversa(ultim);
	printf("\n----------------------------\n");
	nodls* capLS = conversieListaDubla(&cap, &ultim);
	printf("\n------------------------------\n");
	printf("\nLista simpla:");
	traversareListaSimpla(capLS);
	if (cap == NULL) {
		printf("\n--------------------------\n");
		printf("\nLista dubla a fost stearsa");
	}
	dezalocareListaDubla(&cap, &ultim);
	system("pause");
	return 0;
}