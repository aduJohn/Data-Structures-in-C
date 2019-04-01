//5. Scrieti functia nerecursiva care efectueaza copierea unei liste, cu eliminarea elementelor ce au ca informatie utila o valoare mai mica decat un nivel specificat de parametru.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct student {
	int cod;
	char* nume;
	float medie;
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
void inserareListaDubla(nodld** cap, nodld** ultim) {
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
void copiereListaDubla(nodld* cap,nodld** copie,nodld** copieu) {
	printf("\nCare este codul minim?");
	int codul = 0;
	scanf("%d", &codul);
	nodld* temp = cap;
	while (temp) {
		if (temp->info->cod >= codul) {
			nodld* nou = (nodld*)malloc(sizeof(nodld));
			nou->info = (student*)malloc(sizeof(student));
			nou->info->cod = temp->info->cod;
			nou->info->nume = (char*)malloc((strlen(temp->info->nume) + 1) * sizeof(char));
			strcpy(nou->info->nume, temp->info->nume);
			nou->info->medie = temp->info->medie;
			nou->next = NULL;
			nou->prev = NULL;
			if (*copie == NULL) {
				*copie = nou;
				*copieu = nou;
			}
			else {
				nodld* temp1 = *copie;
				while (temp1->next) {
					temp1 = temp1->next;
				}
				*copieu = nou;
				temp1->next = *copieu;
				(*copieu)->prev = temp1;
			}
		}
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
void dezalocareListaDubla(nodld** cap, nodld** ultim) {
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
	nodld* copie=NULL;
	nodld* copieu=NULL;
	int n = 0;
	printf("\nCare este numarul de studenti cititi?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaDubla(&cap, &ultim);
	}
	printf("\n------------------------------\n");
	traversare(cap);
	printf("\n------------------------------\n");
	copiereListaDubla(cap, &copie,&copieu);
	printf("\n--------------------------------\n");
	traversare(copie);
	printf("\n--------------------------------\n");
	traversareInversa(copieu);
	dezalocareListaDubla(&copie, &copieu);
	dezalocareListaDubla(&cap, &ultim);
	system("pause");
	return 0;
}