#include <iostream>
#include <stdio.h>
#include <malloc.h>
#define LIMSIZE 128
using namespace std;
struct Produs {
	char* nume;
	int cantitate;
	char* unitate;
};
struct Comanda {
	int id;
	char* denumire;
	int numar;
	Produs* produse;
	char* data;
};
struct nodArb {
	Comanda* comanda;
	nodArb* left;
	nodArb* right;
};
nodArb* inserareArbore(nodArb* root, Comanda* comanda) {
	if (root == NULL) {
		nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
		nou->left = NULL;
		nou->right = NULL;
		nou->comanda = comanda;
		root = nou;
	}
	else {
		if (root->comanda->id == comanda->id) {
			printf("\nComanda exista deja in arbore\n");
		}
		else if (root->comanda->id>comanda->id) {
			root->left = inserareArbore(root->left, comanda);
		}
		else {
			root->right = inserareArbore(root->right, comanda);
		}
	}
	return root;
}
void inordine(nodArb* root) {
	if (root) {
		inordine(root->left);
		printf("\nComanda: Id:%d, Denumire: %s, Data: %s\n", root->comanda->id, root->comanda->denumire, root->comanda->data);
		printf("\n\tProdusele:");
		for (int i = 0; i < root->comanda->numar; i++) {
			printf("\n\tProdus: Nume: %s, Unitate: %s, Cantitate: %d", root->comanda->produse[i].nume, root->comanda->produse[i].unitate, root->comanda->produse[i].cantitate);
		}
		inordine(root->right);
	}
}
void intoarcereVector(nodArb* root, int** vector, int* numar,const char* data) {
	if (root) {
		if (strcmp(data, root->comanda->data) == 0) {
			if (*vector) {
				(*numar)++;
				int* copie = (int*)malloc((*numar - 1) * sizeof(int));
				for (int i = 0; i < (*numar - 1); i++) {
					copie[i] = (*vector)[i];
				}
				*vector = (int*)malloc((*numar) * sizeof(int));
				for (int i = 0; i < (*numar - 1); i++) {
					(*vector)[i] = copie[i];
				}
				(*vector)[(*numar - 1)] = root->comanda->id;
			}
			else {
				*numar = 1;
				*vector = (int*)malloc(sizeof(int));
				(*vector)[0] = root->comanda->id;
			}
		}
		intoarcereVector(root->left, vector, numar, data);
		intoarcereVector(root->right, vector, numar, data);
	}
}
int numarFrunze(nodArb* root,const char* client) {
	if (root) {
		if (root->left == NULL && root->right == NULL&&strcmp(client,root->comanda->denumire)==0) {
			return 1;
		}
		else {
			return numarFrunze(root->left, client) + numarFrunze(root->right, client);
		}
	}
	else {
		return 0;
	}
}
void citireFisier(char* fisier,nodArb** root) {
	FILE* f;
	f = fopen(fisier, "r");
	if (f) {
		char* token, fis_buf[LIMSIZE];
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			Comanda* comanda = (Comanda*)malloc(sizeof(Comanda));
			token = strtok(fis_buf, ",");
			comanda->id = atoi(token);
			printf("%d", comanda->id);
			token = strtok(NULL, ",");
			comanda->denumire = (char*)malloc((strlen(token) + 1));
			strcpy(comanda->denumire, token);
			token = strtok(NULL, ",");
			comanda->numar = atoi(token);
			token = strtok(NULL, ",");
			comanda->data = (char*)malloc((strlen(token) + 1));
			strcpy(comanda->data, token);
			Produs* produse = (Produs*)malloc(comanda->numar * sizeof(Produs));
			FILE* f2;
			f2 = fopen("produse.txt", "r");
			if (f2) {
				int i = 0;
				char* token2, fis_buf2[LIMSIZE];
				while (fgets(fis_buf2,sizeof(fis_buf2),f2)) {
					token2 = strtok(fis_buf2, ",");
					int cod = atoi(token2);
					if (cod == comanda->id) {
						token2 = strtok(NULL, ",");
						produse[i].cantitate = atoi(token2);
						token2 = strtok(NULL, ",");
						produse[i].nume = (char*)malloc((strlen(token2) + 1));
						strcpy(produse[i].nume, token2);
						token2 = strtok(NULL, ",");
						produse[i].unitate = (char*)malloc((strlen(token2) + 1));
						strcpy(produse[i].unitate, token2);
						i++;
					}
				}
			}
			comanda->produse = produse;
			*root = inserareArbore(*root, comanda);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu s-a putut deschide");
		*root = NULL;
	}
}
int main() {
	nodArb* root;
	root = NULL;
	char fisier[] = "comenzi.txt";
	citireFisier(fisier, &root);
	printf("\nAfisare INORDINE\n");
	inordine(root);
	int* vector = NULL;
	int numar = 0;
	char data[] = "20/04/2018";
	intoarcereVector(root, &vector, &numar,data);
	printf("\nVector:\n");
	for (int i = 0; i < numar; i++) {
		printf("%d ", vector[i]);
	}
	printf("\nNumar frunze: %d ", numarFrunze(root,"Comanda4"));
	getchar();
	getchar();
	return 0;
}