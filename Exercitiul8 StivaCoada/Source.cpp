//8.Se consideră un şir de numere întregi. Să se scrie funcţia care construieşte două stive 
//(una cu numerele negative şi una cu cele pozitive) ce conţin numerele în ordinea iniţială folosind doar structuri de tip stivă.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodStiva {
	int element;
	nodStiva* next;
};
void pushStiva(nodStiva** cap,int val) {
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
int popStiva(nodStiva** cap,int* val) {
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
void dezalocareStiva(nodStiva** cap) {
	int dummy;
	do
		dummy = 1;
	while (popStiva(cap, &dummy) == 1);
}
int main() {
	nodStiva* capDummy = NULL;
	nodStiva* capImpar = NULL;
	nodStiva* capPar = NULL;
	int ok = 1;
	int dummy;
	while (ok) {
		printf("\nCare este elementul inserat in stiva?");
		scanf("%d", &dummy);
		pushStiva(&capDummy, dummy);
		printf("\nContinui inserarea?1=DA/0=NU");
		scanf("%d", &ok);
	}
	traversareStiva(capDummy);
	while (popStiva(&capDummy, &dummy) == 1) {
		pushStiva(&capPar, dummy);
	}
	while (popStiva(&capPar, &dummy) == 1) {
		pushStiva(&capDummy, dummy);
	}
	while (popStiva(&capDummy, &dummy) == 1) {
		if (dummy % 2 == 0) {
			pushStiva(&capPar, dummy);
		}
		else {
			pushStiva(&capImpar, dummy);
		}
	}
	traversareStiva(capPar);
	traversareStiva(capImpar);
	dezalocareStiva(&capImpar);
	dezalocareStiva(&capPar);
	system("pause");
	return 0;
}