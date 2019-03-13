#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct Produs {
	int* cod;
	char* denumire;
	float* pret;
	float* cantitate;
};
struct Nod {
	Produs* info;
	Nod* next;
	Nod* prev;
};
void afisareMeniu() {
	printf("\n1. Afisare lista dublu inlantuita.");
	printf("\n2. Afisarea inversa a listei dublue inlantuite.");
	printf("\n3. Afisare vector.");
	printf("\n4. Inserare in lista dublu inlantuita.");
	printf("\n5. Inserare in vector.");
	printf("\n6. Stergere din lista dublu inlantuita.");
	printf("\n7. Stergere din vector.");
	printf("\n8. Conversie din lista in vector.");
	printf("\n9. Conversie din vector in lista.");
	printf("\n10. Exit.");
}
Produs* citireProdus() {
	Produs* produs = (Produs*)malloc(sizeof(Produs));
	printf("\nCare este codul produsul?");
	produs->cod = (int*)malloc(sizeof(int));
	scanf("%d", produs->cod);
	printf("\nCare este denumire produsului?");
	char buffer[50];
	scanf("%s", buffer);
	produs->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(produs->denumire, buffer);
	printf("\nCare este pretul produsului?");
	produs->pret = (float*)malloc(sizeof(float));
	scanf("%f", produs->pret);
	printf("\nCare este cantitatea produsului?");
	produs->cantitate = (float*)malloc(sizeof(float));
	scanf("%f", produs->cantitate);
	return produs;
}
void inserareLista(Nod** cap,Nod** coada) {
	Nod* nodls = (Nod*)malloc(sizeof(Nod));
	nodls->info = citireProdus();
	nodls->next = NULL;
	nodls->prev = NULL;
	if (*cap == NULL) {
		*cap = nodls;
		*coada = nodls;
	}
	else {
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodls;
		nodls->prev = temp;
		*coada = nodls;
	}
}
int numarNoduri(Nod* cap) {
	int i = 0;
	Nod* temp = cap;
	while (temp != NULL) {
		i++;
		temp = temp->next;
	}
	return i;
}
void stergereLista(Nod** cap, Nod** coada, int index) {
	if (index > 0 && index <= numarNoduri(*cap)) {
		if (index == 1) {
			Nod* temp = *cap;
			*cap = temp->next;
			(*cap)->prev = NULL;
			free(temp->info->cod);
			free(temp->info->denumire);
			free(temp->info->pret);
			free(temp->info->cantitate);
			free(temp);
		}
		else if (index != numarNoduri(*cap)) {
				Nod* temp = *cap;
				int i = 1;
				while (index != i) {
					i++;
					temp = temp->next;
				}
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
				free(temp->info->cod);
				free(temp->info->denumire);
				free(temp->info->pret);
				free(temp->info->cantitate);
				free(temp);
			}
			else {
				Nod* temp = *coada;
				*coada = (*coada)->prev;
				(*coada)->next = NULL;
				free(temp->info->cod);
				free(temp->info->denumire);
				free(temp->info->pret);
				free(temp->info->cantitate);
				free(temp);
			}
	}else{
		printf("\n Indexul este in afara multimii...");
	}
}
void traversareDirecta(Nod* cap) {
	Nod* temp = cap;
	if (cap != NULL) {
		while (temp != NULL) {
			printf("\n Produsul cu: Codul %d; Denumirea %s; Pretul %5.2f; Cantitatea %5.2f .", *(temp->info->cod), temp->info->denumire,
				*(temp->info->pret), *(temp->info->cantitate));
			temp = temp->next;
		}
	}
	else {
		printf("Nu exista nici un nod in lista");
	}
}
void traversareInversa(Nod* coada) {
	Nod* temp = coada;
	if (coada != NULL) {
		while (temp != NULL) {
			printf("\n Produsul cu: Codul %d; Denumirea %s; Pretul %5.2f; Cantitatea %5.2f .", *(temp->info->cod), temp->info->denumire,
				*(temp->info->pret), *(temp->info->cantitate));
			temp = temp->prev;
		}
	}
	else {
		printf("\n Nu exista nici un nod in lista");
	}
}
void dezalocareLista(Nod* cap) {
	Nod* temp = cap;
	while (temp != NULL) {
		Nod* temp2 = temp->next;
		free(temp->info->cantitate);
		free(temp->info->cod);
		free(temp->info->denumire);
		free(temp->info->pret);
		free(temp);
		temp = temp2;
	}
	cap = NULL;
}
void inserareVector(Produs** produse,int* n) {
	Produs* copie = *produse;
	*produse = (Produs*)malloc((*n+1)*sizeof(Produs));
	for (int i = 0; i < *n; i++) {
		(*produse)[i].cod = (int*)malloc(sizeof(int));
		*((*produse)[i].cod) = *(copie[i].cod);
		(*produse)[i].denumire = (char*)malloc(strlen(copie[i].denumire) + 1);
		strcpy((*produse)[i].denumire,copie[i].denumire);
		(*produse)[i].cantitate = (float*)malloc(sizeof(float));
		*((*produse)[i].cantitate) = *(copie[i].cantitate);
		(*produse)[i].pret = (float*)malloc(sizeof(float));
		*((*produse)[i].pret) = *(copie[i].pret);
	}
	Produs* produs= citireProdus();
	(*produse)[*n].cod = produs->cod;
	(*produse)[*n].denumire = produs->denumire;
	(*produse)[*n].cantitate = produs->cantitate;
	(*produse)[*n].pret = produs->pret;
	(*n)++;
	for (int i = 0; i < *n-1; i++) {
		free(copie[i].cod);
		free(copie[i].denumire);
		free(copie[i].cantitate);
		free(copie[i].pret);
	}
	free(copie);
	free(produs);
}
void stergereVector(Produs** produse, int* n, int index) {
	if (index > 0 && index <= *n) {
		Produs* copie = *produse;
		*produse = (Produs*)malloc((*n-1)*sizeof(Produs));
		int j = 0;
		for (int i = 0; i < *n; i++) {
			if (index - 1 != i) {
				(*produse)[j].cod = copie[i].cod;
				(*produse)[j].cantitate = copie[i].cantitate;
				(*produse)[j].denumire = copie[i].denumire;
				(*produse)[j].pret = copie[i].pret;
				j++;
			}
			else {
				free(copie[i].cod);
				free(copie[i].cantitate);
				free(copie[i].denumire);
				free(copie[i].pret);
			}
		}
		free(copie);
		(*n)--;
	}
	else {
		printf("Indexul este in afara multimii...");
	}
}
void conversieListaInVector(Nod** cap,Nod** coada,Produs** produse,int* n) {
	*produse = (Produs*)malloc(numarNoduri(*cap)*sizeof(Produs));
	int i = 0;
	Nod* temp = *cap;
	*n = numarNoduri(*cap);
	while (temp != NULL) {
		(*produse)[i].cod = temp->info->cod;
		(*produse)[i].denumire = temp->info->denumire;
		(*produse)[i].cantitate = temp->info->cantitate;
		(*produse)[i].pret = temp->info->pret;
		i++;
		temp = temp->next;
	}
	temp = *cap;
	while (temp != NULL) {
		Nod* temp2 = temp;
		temp = temp->next;
		free(temp2->info);
		free(temp2);
	}
	*cap = NULL;
	*coada = NULL;
}
void conversieVectorInLista(Nod** cap,Nod** coada,Produs** produse,int* n) {
	Nod* nodls = (Nod*)malloc(sizeof(Nod));
	nodls->next = NULL;
	nodls->prev = NULL;
	Produs* produs = (Produs*)malloc(sizeof(Produs));
	produs->cod = (*produse)[0].cod;
	produs->cantitate = (*produse)[0].cantitate;
	produs->denumire = (*produse)[0].denumire;
	produs->pret = (*produse)[0].pret;
	nodls->info = produs;
	*cap = nodls;
	Nod* temp = *cap;
	for (int i = 1; i < *n; i++) {
		produs = (Produs*)malloc(sizeof(Produs));
		nodls = (Nod*)malloc(sizeof(Nod));
		produs->cod = (*produse)[i].cod;
		produs->cantitate = (*produse)[i].cantitate;
		produs->denumire = (*produse)[i].denumire;
		produs->pret = (*produse)[i].pret;
		nodls->info = produs;
		temp->next = nodls;
		nodls->prev = temp;
		temp = temp->next;
		nodls->next = NULL;
	}
	free(*produse);
	*coada = temp;
	*produse = NULL;
	*n = 0;
}	
void afisareVector(Produs* produse,int n) {
	if (n != 0) {
		for (int i = 0; i < n; i++) {
			printf("\n Produsul cu: Codul %d; Denumirea %s; Pretul %5.2f; Cantitatea %5.2f .", *(produse[i].cod), produse[i].denumire,
				*(produse[i].pret), *(produse[i].cantitate));
		}
	}
	else {
		printf("Nu exista nici un element in vector...");
	}
}
void dezalocareVector(Produs** produse, int* n) {
	for (int i = 0; i < *n; i++) {
		free((*produse)[i].cod);
		free((*produse)[i].denumire);
		free((*produse)[i].pret);
		free((*produse)[i].cantitate);
	}
	free(*produse);
	*n = 0;
}
int main() {
	Nod* cap=NULL;
	Nod* coada=NULL;
	Produs* produse = NULL;
	int index;
	int numarElemente=0;
	int numarOptiune;
	int esteLista = 3;
	afisareMeniu();
	printf("\nCare este optiunea dvs.?");
	scanf("%d", &numarOptiune);
	system("cls");
	while (numarOptiune != 10) {
		switch (numarOptiune) {
		case 1:traversareDirecta(cap); break;
		case 2:traversareInversa(coada);  break;
		case 3:afisareVector(produse,numarElemente); break;
		case 4:
			if (esteLista == 3 || esteLista == 1) {
				inserareLista(&cap, &coada);
				esteLista = 1;
			}
			else {
				printf("Nu se poate insera in lista deoarece exista un vector, trebuie sa faceti conversie...");
			}break;
		case 5:
			if (esteLista == 3 || esteLista == 2) {
				inserareVector(&produse, &numarElemente);
				esteLista = 2;
			}
			else {
				printf("Nu se poate insera in vector deoarece exista o lista, trebuie sa faceti conversie...");
			}break;
		case 6:
			if (esteLista == 1) {
				printf("Care este nodul pe care vrei sa il stergi?");
				scanf("%d", &index);
				stergereLista(&cap, &coada, index);
			}
			else {
				if (esteLista == 3) {
					printf("Nu exista nici un nod de sters...");
				}
				else {
					printf("Nu se poate sterge din lista deoarece exista un vector, trebuie sa faceti o conversie...");
				}
			}break;
		case 7:
			if (esteLista == 2) {
				printf("Care este elementul pe care vrei sa il stergi");
				scanf("%d", &index);
				stergereVector(&produse, &numarElemente, index);
			}
			else {
				if (esteLista==3) {
					printf("Nu exista nici un element de sters...");
				}
				else {
					printf("Nu se poate sterge din vector deoarece exista o lista in memorie, trebuie sa faceti o conversie...");
				}
			}
			   break;
		case 8:
			if (esteLista == 1) {
				conversieListaInVector(&cap,&coada,&produse,&numarElemente);
				printf("Conversie reusita...");
				esteLista = 2;
			}
			else {
				if (esteLista==3) {
					printf("Nu exista nici o lista/vector in memorie de convertit");
				}
				else {
					printf("Exista deja un vector in memorie...");
				}
			}
			break;
		case 9:
			if (esteLista == 2) {
				conversieVectorInLista(&cap, &coada, &produse, &numarElemente);
					printf("Conversie reusita");
					esteLista = 1;
			}
			else {
				if (esteLista == 3) {
					printf("Nu exista nici un vector/lista de convertit");
				}
				else {
					printf("Exista deja o lista in memorie...");
				}
			}
			break;
		default: printf("Optiunea nu exista...");
		}
		printf("\n");
		system("pause");
		system("cls");
		afisareMeniu();
		printf("\nCare este optiunea dvs.?");
		scanf("%d", &numarOptiune);
		system("cls");
	}
	dezalocareVector(&produse, &numarElemente);
	dezalocareLista(cap);
	system("pause");
	return 0;
}