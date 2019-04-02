//8. Sa se scrie functia pentru concatenarea a n liste dublu inlantuite.
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
void concatenareListaDubla(nodld* cap1,nodld** ultim1,nodld** cap2,nodld* ultim2) {
	(*ultim1)->next = *cap2;
	(*cap2)->prev = *ultim1;
	*cap2 = cap1;
	*ultim1 = ultim2;
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
	nodld** capLista = NULL;
	nodld** ultimLista = NULL;
	printf("\nCare este numarul de lista pe care vreti sa le puneti in vectorul de lista?");
	int n;
	scanf("%d", &n);
	capLista = (nodld**)malloc(n * sizeof(nodld*));
	ultimLista = (nodld**)malloc(n * sizeof(nodld*));
	int nr;
	for (int i = 0; i < n; i++) {
		printf("\nCare este numarul de elemente listei [%d]", i + 1);
		scanf("%d", &nr);
		capLista[i] = NULL;
		ultimLista[i] = NULL;
		for (int j = 0; j < nr; j++) {
			inserareListaDubla(capLista + i, ultimLista + i);
		}
	}
	for (int i = 0; i < n; i++) {
		printf("\nTraversarea listei %d\n", i + 1);
		traversare(capLista[i]);
	}
	printf("\n----------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("\nTraversarea inversa a listei %d\n", i + 1);
		traversareInversa(ultimLista[i]);
	}
	printf("\n--------------------------------\n");
	printf("\n--------------------------------\n");
	for (int i = 0; i < n - 1; i++) {
		concatenareListaDubla(capLista[i], ultimLista + i, capLista + (i + 1), ultimLista[i+1]);
	}
	nodld* capListaFinala = capLista[0];
	nodld* ultimListaFinala = ultimLista[0];
	free(capLista);
	free(ultimLista);
	printf("\nTraversare Lista Finala Concatenata\n");
	traversare(capListaFinala);
	dezalocareListaDubla(&capListaFinala, &ultimListaFinala);
	system("pause");
	return 0;
}