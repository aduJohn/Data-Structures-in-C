#include <iostream>
#include <malloc.h>
#include <conio.h>
using namespace std;
struct Produs {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};
struct Nod {
	Produs info;
	Nod* next;
};
void afisareMeniu() {
	printf("\n1. Afisarea listei simple inlantuite.");
	printf("\n2. Afisare Vector.");
	printf("\n3. Inserarea unui element in lista simplu inlantuita.");
	printf("\n4. Inserarea unui element in Vector.");
	printf("\n5. Stergerea unui element din lista simplu inlantuita.");
	printf("\n6. Stergerea unui element din Vector.");
	printf("\n7. Conversie listei simplu inlantuite in vector.");
	printf("\n8. Conversia vectorului in lista simplu inlantuita.");
	printf("\n9. Exit");
}
Produs* citireProdus() {
	Produs* produs = (Produs*)malloc(sizeof(Produs));
	printf("\nCare este codul produsului?");
	scanf("%d", &produs->cod);
	printf("\nCare este denumirea produsului?");
	char buffer[50];
	scanf("%s", buffer);
	produs->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(produs->denumire, buffer);
	printf("\nCare este pretul produsului?");
	scanf("%f", &produs->pret);
	printf("\nCare este cantitatea produsului?");
	scanf("%f", &produs->cantitate);
	return produs;
}
void inserareNod(Nod** cap) {
	Nod* nodls = (Nod*)malloc(sizeof(Nod));
	Produs* produs = citireProdus();
	nodls->info.cantitate = produs->cantitate;
	nodls->info.pret = produs->pret;
	nodls->info.cod = produs->cod;
	nodls->info.denumire = (char*)malloc((strlen(produs->denumire) + 1) * sizeof(char));
	strcpy(nodls->info.denumire, produs->denumire);
	nodls->next = NULL;
	if (*cap == NULL) {
		*cap = nodls;
	}
	else {
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nodls;
	}
	free(produs);
}
int numarNoduri(Nod* cap) {
	int i = 1;
	Nod* temp = cap;
	while (temp->next != NULL) {
		i++;
		temp = temp->next;
	}
	return i;
}
void stergeDinLista(Nod** cap, int index) {
	Nod* temp = *cap;
	int i = 1;
	if (*cap == NULL) {
		printf("Lista nu are nici un elementen momentan...");
	}
	else {
		if (index > 0 && i <= numarNoduri(*cap)) {
			temp = *cap;
			if (index == 1) {
				Nod* temp2 = temp;
				*cap = temp->next;
				free(temp2);
			}
			else {
				while (temp != NULL && i <= numarNoduri(*cap)) {
					if (i == index - 1) {
						Nod* temp2 = temp->next;
						temp->next = temp->next->next;
						free(temp2);
						i = numarNoduri(*cap) + 1;
					}
					i++;
					temp = temp->next;
				}
			}
		}
		else {
			printf("Indexul este in afara multimii...");
		}
	}
}
void afisareLista(Nod* cap) {
	Nod* temp = cap;
	int i = 1;
	if (cap == NULL) {
		printf("\nLista nu are nici un element...");
	}
	else {
		while (temp != NULL) {
			printf("\nProdusul %d, cu codul %d; denumirea %s; pretul %5.2f; cantitatea %5.2f;",i, temp->info.cod, temp->info.denumire, temp->info.pret,
				temp->info.cantitate);
			temp = temp->next;
			i++;
		}
	}
}
void afisareVector(Produs* produse,int n) {
	if (n==0) {
		printf("Nu exista elemente in vector");
	}
	else {
		for (int i = 0; i < n; i++) {
			printf("\nProdusul %d, cu codul %d; denumirea %s; pretul %5.2f; cantitatea %5.2f;", i+1, produse[i].cod, produse[i].denumire,
				produse[i].pret, produse[i].cantitate);
		}
	}
}
void inserareVector(Produs** produse,int* n) {
	if ((*n) == 0) {
		Produs* aux = citireProdus();
		*produse = aux;
	}
	else {
		Produs* copie = *produse;
		*produse = (Produs*)malloc((*n + 1) * sizeof(Produs));
		for (int i = 0; i < *n; i++) {
			(*produse)[i].cod = copie[i].cod;
			(*produse)[i].cantitate = copie[i].cantitate;
			(*produse)[i].pret = copie[i].pret;
			(*produse)[i].denumire = (char*)malloc((strlen(copie[i].denumire)+1) * sizeof(char));
			strcpy((*produse)[i].denumire, copie[i].denumire);
		}
		Produs* aux = citireProdus();
		(*produse)[*n].cod = aux->cod;
		(*produse)[*n].cantitate = aux->cantitate;
		(*produse)[*n].pret = aux->pret;
		(*produse)[*n].denumire = (char*)malloc((strlen(aux->denumire) + 1) * sizeof(char));
		strcpy((*produse)[*n].denumire, aux->denumire);
		for (int i = 0; i < *n; i++) {
			free(copie[i].denumire);
		}
		free(copie);
		free(aux->denumire);
		free(aux);
	}
	(*n)++;
}
void stergereDinVector(Produs** produse, int* n, int index) {
	if (index > 0 && index <= *n) {
		Produs* copie = *produse;
		int j = 0;
		*produse = (Produs*)malloc((*n - 1) * sizeof(Produs));
		for (int i = 0; i < *n; i++) {
			if (i != index - 1) {
				(*produse)[j].cod = copie[i].cod;
				(*produse)[j].cantitate = copie[i].cantitate;
				(*produse)[j].pret = copie[i].pret;
				(*produse)[j].denumire = (char*)malloc((strlen(copie[i].denumire) + 1) * sizeof(char));
				strcpy((*produse)[j].denumire, copie[i].denumire);
				j++;
			}
		}
		for (int i = 0; i < *n; i++) {
			free(copie[i].denumire);
		}
		free(copie);
		(*n)--;
	}
	else {
		printf("Indexul este in afara vectorului...");
	}
}
void conversieVectorInLista(Nod** cap, Produs** produse, int* n) {
	Nod* nodls = (Nod*)malloc(sizeof(Nod));
	nodls->info.cantitate = (*produse)[0].cantitate;
	nodls->info.cod = (*produse)[0].cod;
	nodls->info.pret = (*produse)[0].pret;
	nodls->info.denumire = (char*)malloc((strlen((*produse)[0].denumire) + 1) * sizeof(char));
	strcpy(nodls->info.denumire, (*produse)[0].denumire);
	nodls->next = NULL;
	*cap = nodls;
	Nod* temp = *cap;
	for (int i = 1; i < *n; i++) {
		nodls = (Nod*)malloc(sizeof(Nod));
		nodls->info.cantitate = (*produse)[i].cantitate;
		nodls->info.cod = (*produse)[i].cod;
		nodls->info.pret = (*produse)[i].pret;
		nodls->info.denumire = (char*)malloc((strlen((*produse)[i].denumire) + 1) * sizeof(char));
		strcpy(nodls->info.denumire, (*produse)[i].denumire);
		nodls->next = NULL;
		temp->next = nodls;
		temp = temp->next;
	}
	for (int i = 0; i < *n; i++) {
		free((*produse)[i].denumire);
	}
	free(*produse);
	*produse = NULL;
	*n = 0;
}
void dezalocareVector(Produs* produse,int* n) {
	for (int i = 0; i < *n; i++) {
		free(produse[i].denumire);
	}
	free(produse);
	*n = 0;
}
void dezalocareLista(Nod* cap) {
	if (cap != NULL) {
		Nod* temp = cap;
		while (temp->next != NULL) {
			Nod* temp2 = temp->next;
			free(temp->info.denumire);
			free(temp);
			temp = temp2;
		}
	}

}
void conversieListaInVector(Nod** cap, Produs** produse, int* n) {
	*n = numarNoduri(*cap);
	Nod* copie = *cap;
	*produse = (Produs*)malloc((*n) * sizeof(Produs));
	for (int i = 0; i < *n; i++) {
		(*produse)[i].cod = copie->info.cod;
		(*produse)[i].cantitate = copie->info.cantitate;
		(*produse)[i].pret = copie->info.pret;
		(*produse)[i].denumire = (char*)malloc((strlen(copie->info.denumire) + 1) * sizeof(char));
		strcpy((*produse)[i].denumire, copie->info.denumire);
		copie = copie->next;
	}
	dezalocareLista(*cap);
	*cap = NULL;
}
int main() {
	int numarOptiune = 0;
	Nod* cap = NULL;
	Produs* produse = NULL;
	int n=0;
	int esteLista = 3;
	int index;
	afisareMeniu();
	printf("\nCare este optiunea dvs.?");
	scanf("%d", &numarOptiune);
	system("cls");
	while (numarOptiune != 9) {
		switch (numarOptiune) {
		case 1:	afisareLista(cap); break;
		case 2: afisareVector(produse, n); break;
		case 3: 
		if (esteLista == 3 || esteLista == 1) { inserareNod(&cap); esteLista = 1; }
		else {
			printf("Exista doar un vector in memorie, pentru a insera intr-o lista trebuie sa faci conversie");
		} 
		break;
		case 4: 
		if (esteLista == 3 || esteLista == 2) { inserareVector(&produse, &n); esteLista = 2; }
		else {
			printf("Exista doar o lista in memorie, pentru a insera intr-un vector trebuie sa faci conversie");
		}
		break;
		case 5: 
		if (esteLista == 1) {
			printf("Care este nodul pe care vrei sa il stergi?");
			scanf("%d", &index);
			stergeDinLista(&cap, index);
		}
		else if (esteLista == 3) {
			printf("Nu exista nici o lista in memorie din care sa faci stergerea");
		}
		else {
			printf("Exista doar un vector in memorie, pentru a insera intr-o lista trebuie sa faci conversie");
		}
		break;
		case 6:	
		if (esteLista == 2) {
			printf("Care este elementul din vector pe care vrei sa il stergi?");
			scanf("%d", &index);
			stergereDinVector(&produse, &n, index);
		}
		else if (esteLista == 3) {
			printf("Nu exista nici un vector in memorie din care sa faci stergerea");
		}
		else {
			printf("Exista doar o lista in memorie, pentru a insera intr-un vector trebuie sa faci conversie");
		}
		break;
		case 7:
		if (esteLista == 1) {
			conversieListaInVector(&cap, &produse, &n);
			printf("Conversie reusita...");
			esteLista = 2;
		}
		else if (esteLista == 3) {
			printf("Nu exista o lista pe care sa o convertesti");
		}
		else {
			printf("Deja exista un vector in memorie");
		}
		break;
		case 8: 
		if (esteLista == 2) {
			conversieVectorInLista(&cap, &produse, &n);
			printf("Conversie reusita...");
			esteLista = 1;
		}
		else if (esteLista == 3) {
			printf("Nu exista vectorul pe care sa il convertesti");
		}
		else {
			printf("Deja exista lista in memorie");
		}
		break;
		default: {
			printf("Tasta gresita...");
			break;
		}
		}
		printf("\n");
		system("pause");
		system("cls");
		afisareMeniu();
		printf("\nCare este optiunea dvs.?");
		scanf("%d", &numarOptiune);
		system("cls");
	}
	dezalocareVector(produse, &n);
	dezalocareLista(cap);
	system("pause");
	return 0;
}