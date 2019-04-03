//9.Scrieţi funcţia recursivă pentru ştergerea tuturor elementelor dintr-o stivă alocată dinamic.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodStiva {
	int element;
	nodStiva* next;
};
void pushStiva(nodStiva** cap, int val) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->element = val;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nou->next = *cap;
		*cap = nou;
	}
}
int popStiva(nodStiva** cap, int* val) {
	if (*cap == NULL) {
		return -1;
	}
	else {
		nodStiva* temp = *cap;
		*val = temp->element;
		*cap = (*cap)->next;
		free(temp);
		return 1;
	}
}
void traversareStiva(nodStiva* cap) {
	printf("\nAfisare stiva:\n");
	nodStiva* temp = cap;
	while (temp) {
		printf("%d ", temp->element);
		temp = temp->next;
	}
}
void stergereRecursiva(nodStiva** cap) {
	if (*cap != NULL) {
		int ceva;
		popStiva(cap, &ceva);
		printf("%d ", ceva);
		stergereRecursiva(cap);
	}
}
void dezalocareStiva(nodStiva** cap) {
	int dummy;
	do
		dummy = 1;
	while (popStiva(cap, &dummy) == 1);
}
int main() {
	nodStiva* cap = NULL;
	int ok = 1;
	int dummy;
	while (ok) {
		printf("\nCare este elementul inserat in stiva?");
		scanf("%d", &dummy);
		pushStiva(&cap, dummy);
		printf("\nContinui inserarea?1=DA/0=NU");
		scanf("%d", &ok);
	}
	stergereRecursiva(&cap);
	system("pause");
	return 0;
}