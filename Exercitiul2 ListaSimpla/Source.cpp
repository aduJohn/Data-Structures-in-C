//2. Concatenarea a doua liste simplu inlantuite.
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
void inserareListaSimpla(nodls** cap) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = citireStudent();
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
		printf("\nStudentul: %d, %s, %5.2f", temp->info->cod, temp->info->nume, temp->info->medie);
		temp = temp->next;
	}
}
void concatenareListaSimpla(nodls* cap1, nodls** cap2) {
	nodls* temp = cap1;
	while (temp->next) {
		temp = temp->next;
	}
	temp->next = *cap2;
	*cap2 = cap1;
	printf("\nCele 2 liste s-au concatenat cu succes");
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
	nodls* cap1 = NULL;
	nodls* cap2 = NULL;
	printf("\nCati studenti sunt in prima lista?");
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap1);
	}
	printf("\n-------------------\n");
	traversareListaSimpla(cap1);
	printf("\nCati studenti sunt in a doua lista?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap2);
	}
	printf("\n-------------------\n");
	traversareListaSimpla(cap2);
	printf("\n-------------------\n");
	concatenareListaSimpla(cap1, &cap2);
	traversareListaSimpla(cap1);
	system("pause");
	return 0;
}