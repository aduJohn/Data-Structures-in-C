//8. Conversia unei matrice in matrice rara memorata ca lista simpla.
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct element {
	int linie;
	int coloana;
	int valoare;
};
struct nodls {
	element* info;
	nodls* next;
};

int** citireMatrice(int& n,int& m) {
	int** mat;
	printf("\nCare este numarul de linii?");
	scanf("%d", &n);
	printf("\nCare este numarul de coloane");
	scanf("%d", &m);
	mat = (int**)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		mat[i] = (int*)malloc(m * sizeof(int));
		for (int j = 0; j < m; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	return mat;
}
void afisareMatrice(int** mat,int n,int m) {
	printf("\nAfisare matricei rara:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}
int elementGasit(nodls* cap, int n, int m) {
	nodls* temp = cap;
	while (temp) {
		if (temp->info->coloana == m && temp->info->linie == n) {
			return temp->info->valoare;
		}
		temp = temp->next;
	}
	return 0;
}
void afisareMatriceRaraListaSimpla(nodls* cap,int n,int m) {
	printf("\n-----------------------\n");
	printf("Afisare matrice rara din lista:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", elementGasit(cap, i, j));
		}
		printf("\n");
	}
}
void inserareListaSimpla(nodls** cap,int n,int m,int val) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = (element*)malloc(sizeof(element));
	nou->info->coloana = m;
	nou->info->linie = n;
	nou->info->valoare = val;
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
		printf("\nElementul: [%d][%d]=%d",temp->info->linie,temp->info->coloana,temp->info->valoare);
		temp = temp->next;
	}
}
void dezalocareListaSimpla(nodls** cap) {
		nodls* temp = *cap;
		while (temp) {
			nodls* temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
		*cap = NULL;
}
int main() {
	nodls* cap = NULL;
	int n, m;
	int** mat=citireMatrice(n,m);
	afisareMatrice(mat, n, m);
	int indice = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j]!=0) {
				inserareListaSimpla(&cap, i, j, mat[i][j]);
			}
		}
	}
	printf("\n----------------------\n");
	traversareListaSimpla(cap);
	printf("\n----------------------\n");
	afisareMatriceRaraListaSimpla(cap, n, m);
	dezalocareListaSimpla(&cap);
	system("pause");
	return 0;
}