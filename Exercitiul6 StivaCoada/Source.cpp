//6.Să se scrie funcţia de concatenare a două stive alocate dinamic S1 şi S2 folosind doar operaţiile de bază 
//(adăugare, extragere, testare stivă vidă). Rezultatul trebuie să conţină elementele din cele două stive în ordinea iniţială.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodStiva {
	char* nume;
	nodStiva* next;
};
void pushStiva(nodStiva** cap,char* buffer) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(nou->nume, buffer);
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nodStiva* temp = *cap;
		*cap = nou;
		(*cap)->next = temp;
	}
}
int popStiva(nodStiva** cap,char** ceva) {
	if (*cap == NULL) {
		return -1;
	}
	else {
		nodStiva* temp = *cap;
		*ceva = (char*)malloc((strlen((*cap)->nume) + 1) * sizeof(char));
		strcpy(*ceva, (*cap)->nume);
		*cap = (*cap)->next;
		free(temp->nume);
		free(temp);
		return 1;
	}
}
void traversareStiva(nodStiva* cap) {
	nodStiva* temp = cap;
	printf("\nAfisare stiva:");
	while (temp) {
		printf("%s ", temp->nume);
		temp = temp->next;
	}
}
void dezalocareStiva(nodStiva** cap) {
	nodStiva* temp = *cap;
	while (temp) {
		nodStiva* temp2 = temp;
		temp = temp->next;
		free(temp2->nume);
		free(temp2);
	}
}
int main() {
	nodStiva* cap1 = NULL;
	nodStiva* cap2 = NULL;
	printf("\nCare este numarul de noduri din stiva 1?");
	int n = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("\nCare este stringul pe care vrei sa il inserezi?");
		char buffer[50];
		scanf("%s", buffer);
		pushStiva(&cap1,buffer);
	}
	printf("\nCare este numarul de noduri din stiva 2?");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("\nCare este stringul pe care vrei sa il inserezi?");
		char buffer[50];
		scanf("%s", buffer);
		pushStiva(&cap2,buffer);
	}
	traversareStiva(cap1);
	printf("\n");
	traversareStiva(cap2);
	printf("\n------------------------------\n");
	nodStiva* stivaConcatenata = NULL;
	char* dummy = NULL;
	while (popStiva(&cap1, &dummy) == 1) {
		pushStiva(&stivaConcatenata, dummy);
		free(dummy);
	}
	while (popStiva(&cap2, &dummy) == 1) {
		pushStiva(&stivaConcatenata, dummy);
		free(dummy);
	}
	printf("\nAfisare stive concatenate:");
	traversareStiva(stivaConcatenata);
	dezalocareStiva(&stivaConcatenata);
	system("pause");
	return 0;
}