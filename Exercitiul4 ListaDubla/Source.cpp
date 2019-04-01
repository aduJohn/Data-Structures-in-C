//4. Sa se scrie o functie recursive care afiseaza elementele unei liste duble in ambele sensuri in functie de optiune.
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
void traversareRecursiva(nodld* cap) {
	if (cap != NULL) {
		printf("\nStudentul: %d, %s, %5.2f ", cap->info->cod, cap->info->nume, cap->info->medie);
		traversareRecursiva(cap->next);
	}
}
void traversareRecursivaInversa(nodld* cap) {
	if (cap != NULL) {
		traversareRecursivaInversa(cap->next);
		printf("\nStudentul: %d, %s, %5.2f ", cap->info->cod, cap->info->nume, cap->info->medie);
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
	int n = 0;
	printf("\nCare este numarul de studenti cititi?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaDubla(&cap, &ultim);
	}
	printf("\nCare este optiunea?0=Traversare recursiva/1=Traversare recursiva inversa\n");
	int optiune = 0;
	scanf("%d", &optiune);
	if (optiune) {
		traversareRecursivaInversa(cap);
	}
	else {
		traversareRecursiva(cap);
	}
	dezalocareListaDubla(&cap, &ultim);
	system("pause");
	return 0;
}