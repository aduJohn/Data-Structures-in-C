//1.Să se scrie funcţia de inversare a unui şir folosind o stivă alocată dinamic.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct nodStiva {
	int val;
	nodStiva* next;
};
void pushStiva(nodStiva** cap,int element) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->val = element;
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
int popStiva(nodStiva** cap,int* element) {
	if (*cap==NULL) {
		return -1;
	}
	else {
		*element = (*cap)->val;
		nodStiva* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		return 1;
	}
}
void traversareStiva(nodStiva* cap) {
	nodStiva* temp = cap;
	while (temp) {
		printf("\nElementul: %d", temp->val);
		temp = temp->next;
	}
}
void dezalocareStiva(nodStiva** cap) {
	int val,i;
	do {
		i=popStiva(cap, &val);
	} while (i==1);
}
int main() {
	printf("\nCare este numarul de elemente?");
	int n;
	nodStiva* cap = NULL;
	scanf("%d", &n);
	int* vector = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", vector+i);
		pushStiva(&cap, vector[i]);
	}
	printf("\n------------------------\n");
	int val;
	while (popStiva(&cap, &val) == 1) {
		printf("%d ", val);
	}
	system("pause");
	return 0;
}