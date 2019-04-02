//2. Să se scrie funcţia de adăugare pentru o stivă alocată ca vector.
//3.Să se scrie funcţia de extragere a unui element dintr-o stivă alocată ca vector.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodStiva {
	char* info;
	nodStiva* next;
};
void pushStivaVector(nodStiva** cap,int* numarNoduri) {
	printf("\nCare este stringul inserat?");
	char buffer[30];
	scanf("%s", buffer);
	if (*cap == NULL) {
		*cap = (nodStiva*)malloc(sizeof(nodStiva));
		(*cap)->next = NULL;
		(*cap)->info=(char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy((*cap)->info, buffer);
		(*numarNoduri)++;
	}
	else {
		nodStiva* copie = *cap;
		(*numarNoduri)++;
		*cap = (nodStiva*)malloc((*numarNoduri) * sizeof(nodStiva));
		(*cap)->info= (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy((*cap)->info, buffer);
		(*cap)->next = NULL;
		for (int i = 1; i < *numarNoduri; i++) {
			(*cap+i)->info= (char*)malloc((strlen((copie+i-1)->info) + 1) * sizeof(char));
			strcpy((*cap + i)->info, (copie + i-1)->info);
			(*cap + i)->next = NULL;
		}
		free(copie);
	}
}
int popStivaVector(nodStiva** cap,int* numarNoduri,char** ceva) {
	if (*cap == NULL) {
		return -1;
	}
	else {
		*ceva = (char*)malloc(sizeof(char)*(strlen((*cap)->info) + 1));
		strcpy(*ceva, (*cap)->info);
		nodStiva* copie = *cap;
		(*numarNoduri)--;
		if (*numarNoduri != 0) {
			*cap = (nodStiva*)malloc(*numarNoduri * sizeof(nodStiva));
			for (int i = 0; i < *numarNoduri; i++) {
				(*cap + i)->info = (char*)malloc((strlen((copie + i + 1)->info) + 1) * sizeof(char));
				strcpy((*cap + i)->info, (copie + i + 1)->info);
				(*cap + i)->next = NULL;
			}
		}
		else {
			*cap = NULL;
		}
		return 1;
	}
}
void traversareStivaVector(nodStiva* cap,int n) {
	printf("\nStiva sub forma de vector\n");
	for (int i = 0; i < n; i++){
		printf("%s ", (cap+i)->info);
	}
}
void dezalocareStivaVector(nodStiva** cap,int* numarNoduri) {
	for (int i = 0; i < *numarNoduri; i++) {
		free((*cap + i)->info);
	}
	free(*cap);
	*numarNoduri = 0;
}
int main() {
	nodStiva* cap = NULL;
	int n = 0;
	int ok = 1;
	while (ok) {
		pushStivaVector(&cap, &n);
		printf("\n1=Continua inserarea | 0=Opreste inserarea\n");
		scanf("%d", &ok);
	}
	printf("\n-------------------------\n");
	traversareStivaVector(cap, n);
	printf("\n---------------------------\n");
	char* ceva;
	while (popStivaVector(&cap, &n, &ceva) == 1) {
		printf("%s ",ceva);
		free(ceva);
	}
	dezalocareStivaVector(&cap, &n);
	system("pause");
	return 0;
}
