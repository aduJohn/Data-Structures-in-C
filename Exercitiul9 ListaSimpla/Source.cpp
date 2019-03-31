//9. Inversarea elementelor unei liste prin modificarea legaturilor.
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
	student* p = (student*)malloc(sizeof(student));
	printf("\nCare este codul studentului?");
	scanf("%d", &p->cod);
	printf("\nCare este numele studentului?");
	char buffer[50];
	scanf("%s", buffer);
	p->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(p->nume, buffer);
	printf("\nCare este media studentului");
	scanf("%f", &p->medie);
	return p;
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
int numarNoduri(nodls* cap) {
	int i = 0;
	nodls* temp = cap;
	while (temp) {
		i++;
		temp = temp->next;
	}
	return i;
}
void interschimbareListaSimpla(nodls** cap, int n1, int n2) {
	int i = 0;
	nodls* temp = *cap;
	while ((n1 - 1) != i) {
		temp = temp->next;
		i++;
	}
	nodls* temp1 = temp;
	student* p1 = temp1->info;
	i = 0;
	temp = *cap;
	while ((n2 - 1) != i) {
		temp = temp->next;
		i++;
	}
	nodls* temp2 = temp;
	student* p2 = temp2->info;
	temp1->info = p2;
	temp2->info = p1;
}
void traversareListaSimpla(nodls* cap) {
	nodls* temp = cap;
	while (temp) {
		printf("\nStudentul: %d, %s, %5.2f", temp->info->cod, temp->info->nume, temp->info->medie);
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
	*cap = NULL;
}
int main() {
	nodls* cap = NULL;;
	int n = 0;
	printf("\nCati studenti sunt?");
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		inserareListaSimpla(&cap);
	}
	printf("\n-----------------------\n");
	traversareListaSimpla(cap);
	printf("\n---------------------------\n");
	for (int i = 0; i < n / 2; i++) {
		interschimbareListaSimpla(&cap, i+1, n - i);
	}
	traversareListaSimpla(cap);
	dezalocareListaSimpla(&cap);
	system("pause");
	return 0;
}