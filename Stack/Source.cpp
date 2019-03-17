#include <iostream>
#include <stdint.h>
#include <malloc.h>
using namespace std;
struct carte {
	int cod;
	char* titlu;
	float pret;
};
struct nodStiva {
	carte* info;
	nodStiva* next;
};
void meniu() {
	printf("\n1. Push");
	printf("\n2. Afisarea stivei");
	printf("\n3. Pop");
	printf("\n4. Afisare vector");
	printf("\n5. Conversie in vector");
	printf("\n6. Conversie in Stiva");
	printf("\n7. Exit");
}
int numarNoduri(nodStiva* cap) {
	int n = 0;
	nodStiva* temp = cap;
	while (temp) {
		n++;
		temp = temp->next;
	}
	return n;
}
carte* citireCarte() {
	carte* c = (carte*)malloc(sizeof(carte));
	printf("\nCare este codul cartii?");
	scanf("%d", &c->cod);
	printf("\nCare este titlu cartii?");
	char buffer[30];
	scanf("%s", buffer);
	c->titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(c->titlu, buffer);
	printf("\nCare este pretul cartii?");
	scanf("%f", &c->pret);
	return c;
}
void pushStiva(nodStiva** cap) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info = citireCarte();
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nou->next = *cap;
		*cap = nou;
	}
}
int popStiva(nodStiva** cap,carte** c) {
	if (*cap != NULL) {
		*c = (*cap)->info;
		nodStiva* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
		return 0;
	}
	else {
		return -1;
	}
}
void traversareStiva(nodStiva* cap) {
	nodStiva* temp = cap;
	if (cap != NULL) {
		while (temp != NULL) {
			printf("\nCartea: %d, Titlu: %s, Pret: %5.2f", temp->info->cod, temp->info->titlu, temp->info->pret);
			temp = temp->next;
		}
	}
	else {
		printf("\n Stiva nu are elemente");
	}
}
void conversieStivaVector(nodStiva** cap, carte** carti, int* n) {
	*n = numarNoduri(*cap);
	if (*n > 0) {
		*carti = (carte*)malloc((*n) * sizeof(carte));
		for (int i = 0; i < *n; i++) {
			carte* c;
			if (popStiva(cap, &c) == 0) {
				(*carti)[i].cod = c->cod;
				(*carti)[i].titlu = (char*)malloc((strlen(c->titlu) + 1) * sizeof(char));
				strcpy((*carti)[i].titlu, c->titlu);
				(*carti)[i].pret = c->pret;
				free(c->titlu);
				free(c);
			}
		}
	}
}
void conversieVectorStiva(nodStiva** cap, carte** carti, int* n) {
	if (*carti != NULL) {
		nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
		carte* aux = (carte*)malloc(sizeof(carte));
		aux->cod = (*carti)[0].cod;
		aux->pret = (*carti)[0].pret;
		aux->titlu = (char*)malloc((strlen((*carti)[0].titlu) + 1) * sizeof(char));
		strcpy(aux->titlu, (*carti)[0].titlu);
		nou->info = aux;
		nou->next = NULL;
		*cap = nou;
		nodStiva* temp = *cap;
		for (int i = 1; i < *n; i++) {
			nou = (nodStiva*)malloc(sizeof(nodStiva));
			aux = (carte*)malloc(sizeof(carte));
			aux->cod = (*carti)[i].cod;
			aux->pret = (*carti)[i].pret;
			aux->titlu = (char*)malloc((strlen((*carti)[i].titlu) + 1) * sizeof(char));
			strcpy(aux->titlu, (*carti)[i].titlu);
			nou->info = aux;
			nou->next = NULL;
			temp->next = nou;
			temp = temp->next;
		}
		for (int i = 0; i < *n; i++) {
			free((*carti)[i].titlu);
		}
		free(*carti);
		*carti = NULL;
		*n = 0;
	}
}
void afisareVector(carte* carti, int n) {
	for (int i = 0; i < n; i++) {
		printf("\nCartea: %d, Titlu: %s, Pret: %5.2f", carti[i].cod, carti[i].titlu, carti[i].pret);
	}
}
void dezalocareStiva(nodStiva** cap) {
	carte* c=NULL;
	while (popStiva(cap, &c) == 0) {
		free(c->titlu);
		free(c);
	}
}
void dezalocareVector(carte** carti,int* n) {
	for (int i = 0; i < *n; i++) {
		free((*carti)[i].titlu);
	}
	free(carti);
	*n = 0;
}
int main() {
	nodStiva* cap=NULL;
	carte* aux=NULL;
	int esteStiva = 3;
	int numarOptiune;
	int numarElemente = 0;
	carte* carti = NULL;
	meniu();
	printf("\nCare este optiunea dvs.?");
	scanf("%d", &numarOptiune);
	system("cls");
	while (numarOptiune != 7) {
		switch (numarOptiune) {
		case 1:if (esteStiva == 1 || esteStiva == 3) {
			pushStiva(&cap); esteStiva = 1;
		}
		else {
			printf("Nu exista stiva in memorie, necesita conversie");
		}
		break;
		case 2:if (esteStiva == 1) {
			traversareStiva(cap);
		}
		else {
			printf("Nu exista stiva in memorie");
		}break;
		case 3:
		if (popStiva(&cap, &aux) == 0) {
				printf("\nCartea: %d, Titlu: %s, Pret: %5.2f", aux->cod, aux->titlu, aux->pret);
		}
		else {
			printf("\nStiva nu are nici un nod");
		}
		break;
		case 4:if (esteStiva == 2) { afisareVector(carti, numarElemente); }
			   else {
				   printf("Nu exista vector in memorie");
			   } break;
		case 5: if (esteStiva == 1) {
			conversieStivaVector(&cap, &carti, &numarElemente); esteStiva = 2;
		}
				else {
					printf("Exista deja un vector");
				}break;
		case 6:if (esteStiva == 2) {
			conversieVectorStiva(&cap, &carti, &numarElemente); esteStiva = 1;
		}
			   else {
				   printf("Exista deja stiva in memorie");
			   } break;
		default:printf("Optiunea nu exista"); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		meniu();
		printf("\nCare este optiunea dvs.?");
		scanf("%d", &numarOptiune);
		system("cls");
	}
	dezalocareStiva(&cap);
	return 0;
}