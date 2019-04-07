//1:30-1:40
#include<iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct Agrafa {
	int cod_agrafa;
	int dimensiune;
	char* culoare;
};
struct CutieAgrafe {
	int cod_cutie;
	int numarAgrafe;
	Agrafa* agrafe;
};
struct nodls {
	CutieAgrafe* info;
	nodls* next;
};
CutieAgrafe* citireCutieAgrafe() {
	CutieAgrafe* cutie = (CutieAgrafe*)malloc(sizeof(CutieAgrafe));
	printf("\nCare este codul cutie de agrafe?");
	scanf("%d", &cutie->cod_cutie);
	printf("\nCare este numarul de agrafe din cutie?");
	scanf("%d", &cutie->numarAgrafe);
	char buffer[50];
	cutie->agrafe = (Agrafa*)malloc(cutie->numarAgrafe * sizeof(Agrafa));
	for (int i = 0; i < cutie->numarAgrafe; i++) {
		printf("\nCare este codul agrafei?");
		scanf("%d", &cutie->agrafe[i].cod_agrafa);
		printf("\nCare este dimensiunea agrafei?");
		scanf("%d", &cutie->agrafe[i].dimensiune);
		printf("\nCare este culoare agrafei?");
		scanf("%s", buffer);
		cutie->agrafe[i].culoare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(cutie->agrafe[i].culoare, buffer);
	}
	return cutie;
}
void inserareListaSimpla(nodls** cap, CutieAgrafe* cutie) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = cutie;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
		(*cap)->next = *cap;
	}
	else {
		nodls* temp = *cap;
		while (temp->next != *cap) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->next = *cap;
	}
}
void traversareListaSimpla(nodls* cap) {
	if (cap) {
		nodls* temp = cap;
		while (temp->next != cap) {
			printf("\nCutia cu agrafe %d:", temp->info->cod_cutie);
			printf("\nNumar de agrafe, %d", temp->info->numarAgrafe);
			for (int i = 0; i < temp->info->numarAgrafe; i++) {
				printf("\n\tAgrafa[%d]: %d %d %s", i, temp->info->agrafe[i].cod_agrafa, temp->info->agrafe[i].dimensiune, temp->info->agrafe[i].culoare);
			}
			temp = temp->next;
		}
		printf("\nCutia cu agrafe %d:", temp->info->cod_cutie);
		printf("\nNumar de agrafe, %d", temp->info->numarAgrafe);
		for (int i = 0; i < temp->info->numarAgrafe; i++) {
			printf("\n\tAgrafa[%d]: %d %d %s", i, temp->info->agrafe[i].cod_agrafa, temp->info->agrafe[i].dimensiune, temp->info->agrafe[i].culoare);
		}
	}
}
CutieAgrafe* stergereNodLista(nodls** cap, int codCautat) {
	if ((*cap)->info->cod_cutie == codCautat) {
		nodls* temp = *cap;
		while (temp->next != *cap) {
			temp = temp->next;
		}
		temp->next = (*cap)->next;
		CutieAgrafe* dummy = (*cap)->info;
		if (temp->next == *cap) {
			free(*cap);
			*cap = NULL;
		}
		else {
			free(*cap);
			*cap = temp->next;
		}
		return dummy;
	}
	else {
		nodls* temp = *cap;
		while (temp->next != *cap&&temp->next->info->cod_cutie != codCautat) {
			temp = temp->next;
		}
		if (temp->next != *cap) {
			nodls* temp2 = temp->next;
			CutieAgrafe* dummy = temp2->info;
			temp->next = temp2->next;
			free(temp2);
			return dummy;
		}
		else {
			return NULL;
		}
	}
}
void stergereNumar(nodls** cap, int numarAgrafe) {
		CutieAgrafe* dummy = NULL;
		while (*cap != NULL && (*cap)->info->numarAgrafe > numarAgrafe) {
			dummy = stergereNodLista(cap, (*cap)->info->cod_cutie);
			if (dummy) {
				printf("\nCutia cu agrafe %d:", dummy->cod_cutie);
				printf("\nNumar de agrafe, %d", dummy->numarAgrafe);
				for (int i = 0; i < dummy->numarAgrafe; i++) {
					printf("\n\tAgrafa[%d]: %d %d %s", i, dummy->agrafe[i].cod_agrafa, dummy->agrafe[i].dimensiune, dummy->agrafe[i].culoare);
					free(dummy->agrafe[i].culoare);
				}
				free(dummy->agrafe);
				free(dummy);
				dummy = NULL;
			}
		}
		if (*cap) {
			nodls* temp = (*cap)->next;
			dummy = temp->info->numarAgrafe > numarAgrafe ? stergereNodLista(&temp, temp->info->cod_cutie) : NULL;
			while (temp->next != *cap || dummy) {
				if (dummy) {
					printf("\nCutia cu agrafe %d:", dummy->cod_cutie);
					printf("\nNumar de agrafe, %d", dummy->numarAgrafe);
					for (int i = 0; i < dummy->numarAgrafe; i++) {
						printf("\n\tAgrafa[%d]: %d %d %s", i, dummy->agrafe[i].cod_agrafa, dummy->agrafe[i].dimensiune, dummy->agrafe[i].culoare);
						free(dummy->agrafe[i].culoare);
					}
					free(dummy->agrafe);
					free(dummy);
					dummy = NULL;
				}
				else {
					temp = temp->next;
				}
				dummy = temp->info->numarAgrafe > numarAgrafe ? stergereNodLista(&temp, temp->info->cod_cutie) : NULL;
			}
	    }
}
void dezalocareListaSimpla(nodls** cap) {
	if (*cap) {
		nodls* temp = *cap;
		while (temp->next != *cap) {
			for (int i = 0; i < temp->info->numarAgrafe; i++) {
				free(temp->info->agrafe[i].culoare);
			}
			free(temp->info->agrafe);
			free(temp->info);
			nodls* temp2 = temp;
			temp = temp->next;
			free(temp2);
		}
	}
	*cap = NULL;
}
int main() {
	nodls* cap = NULL;
	CutieAgrafe* cutie = NULL;
	//CERINTA II
	printf("\nCerinta II\n");
	printf("\nInserati in lista simpla:");
	for (int i = 0; i < 2; i++) {
		cutie = citireCutieAgrafe();
		inserareListaSimpla(&cap, cutie);
	}
	//CERINTA 3
	printf("\nCerinta III\n");
	traversareListaSimpla(cap);
	//CERINTA 4
	printf("\nCerinta IV\n");
	printf("\nCare este nodul din lista pe care vrei sa il stergi?");
	int codCautat = 0;
	scanf("%d", &codCautat);
	cutie = stergereNodLista(&cap, codCautat);
	if (cutie) {
		printf("\nCutia cu agrafe %d:", cutie->cod_cutie);
		printf("\nNumar de agrafe, %d", cutie->numarAgrafe);
		for (int i = 0; i < cutie->numarAgrafe; i++) {
			printf("\n\tAgrafa[%d]: %d %d %s", i, cutie->agrafe[i].cod_agrafa, cutie->agrafe[i].dimensiune, cutie->agrafe[i].culoare);
			free(cutie->agrafe[i].culoare);
		}
		free(cutie->agrafe);
		free(cutie);
		cutie = NULL;
	}
	else {
		printf("\Nu s-a gasit nici un nod cu acest cod %d", codCautat);
	}
	printf("\nTraversare lista dupa stergere nod\n:");
	traversareListaSimpla(cap);
	//CERINTA V
	printf("\nCerinta V\n");
	printf("\nCare este numarul de stergere?");
	scanf("%d", &codCautat);
	printf("\nAfisare nodurilor cu un numar de agrafe mai mare de %d", codCautat);
	stergereNumar(&cap, codCautat);
	printf("\n--------------\n");
	printf("\nAfisare nodurilor cu un numar de agrafe mai mic de %d", codCautat);
	traversareListaSimpla(cap);
	dezalocareListaSimpla(&cap);
	system("pause");
	return 0;
}