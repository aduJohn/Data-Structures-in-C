#include <iostream>
#include <stdio.h>
#include <malloc.h>
#define LIMSIZE 128
#define DIM 101
using namespace std;
struct Adresa {
	int numar;
	char* strada;
};
struct CotaIntretinere {
	Adresa adresa;
	int numarApartament;
	int numarPersoane;
	int an;
	int luna;
	float valoare;
};
struct nodls {
	CotaIntretinere* cota;
	nodls* next;
};
struct tabHash {
	nodls** tabela;
};
int functieHash(int cheie) {
	return cheie % DIM;
}
void inserareListaSimpla(nodls** cap,CotaIntretinere* cota) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->next = NULL;
	nou->cota = cota;
	if (*cap==NULL) {
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
	if (cap) {
		printf("\nTranversarea cotelor pentru apartamentul %d\n", cap->cota->numarApartament);
		printf("\nAdresa apartamentului este: %s, nr. %d", cap->cota->adresa.strada, cap->cota->adresa.numar);
		nodls* temp = cap;
		while (temp) {
			printf("\nCotaIntretinere: NumarPersoane: %d, An: %d, Luna: %d, Valoare: %5.2f", temp->cota->numarApartament, temp->cota->an, temp->cota->luna,temp->cota->valoare);
			temp = temp->next;
		}
	}
}
void dezalocareListaSimpla(nodls** cap) {
	if (cap) {
		printf("\nDezalocare cotelor pentru apartamentul %d\n",(*cap)->cota->numarApartament);
		nodls* temp = *cap;
		while (temp) {
			nodls* temp2 = temp;
			temp = temp->next;
			free(temp2->cota->adresa.strada);
			free(temp2);
		}
	}
	*cap = NULL;
}
void citireFisier(char* fisier,tabHash h) {
	FILE* f;
	f = fopen(fisier, "r");
	if (f) {
		char* token, fis_buf[LIMSIZE];
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			CotaIntretinere* cota = (CotaIntretinere*)malloc(sizeof(CotaIntretinere));
			token = strtok(fis_buf, ",");
			cota->numarApartament = atoi(token);
			token = strtok(NULL, ",");
			cota->adresa.strada = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(cota->adresa.strada, token);
			token = strtok(NULL, ",");
			cota->adresa.numar = atoi(token);
			token = strtok(NULL, ",");
			cota->numarPersoane = atoi(token);
			token = strtok(NULL, ",");
			cota->an = atoi(token);
			token = strtok(NULL, ",");
			cota->luna = atoi(token);
			token = strtok(NULL, ",");
			cota->valoare = atof(token);
			inserareListaSimpla(&h.tabela[functieHash(cota->numarApartament)], cota);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu s-a putut deschide!!!");
	}
}
float calculValoare(tabHash h,int numarApartament,int An,int numarAdresa,const char* nume) {
	nodls* temp = h.tabela[functieHash(numarApartament)];
	float valoare = 0;
	if (temp) {
		while (temp) {
			if (temp->cota->adresa.numar == numarAdresa && strcmp(nume, temp->cota->adresa.strada) == 0 && temp->cota->an == An) {
				valoare += temp->cota->valoare;
			}
			temp = temp->next;
		}
	}
	return valoare;
}
nodls* stergereLista(nodls* cap,int numarAdresa,const char* strada) {
	nodls* capNou = NULL;
	nodls* temp = cap;
	while (temp) {
		if (temp->cota->adresa.numar != numarAdresa || strcmp(strada, temp->cota->adresa.strada) != 0) {
			inserareListaSimpla(&capNou, temp->cota);
		}
		temp = temp->next;
	}
	temp = cap;
	while (temp) {
		nodls* temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	return capNou;
}
void traversareHashTable(tabHash h) {
	printf("\nAfisare elementelor din tabela\n");
	for (int i = 0; i < DIM; i++) {
		if (h.tabela[i]) {
			traversareListaSimpla(h.tabela[i]);
		}
	}
}
int numarCote(tabHash h,float valoare) {
	int numar = 0;
	for (int i = 0; i < DIM; i++) {
		if (h.tabela[i]) {
			nodls* temp = h.tabela[i];
			while (temp) {
				if (temp->cota->valoare > valoare) {
					numar++;
				}
				temp = temp->next;
			}
		}
	}
	return numar;
}
int main() {
	tabHash h;
	h.tabela = (nodls**)malloc(DIM * sizeof(nodls*));
	for (int i = 0; i < DIM; i++) {
		h.tabela[i] = NULL;
	}
	char fisier[] = "exam.txt";
	citireFisier(fisier, h);
	traversareHashTable(h);
	printf("\n\nCalcularea valorii pentru apartamentul 23, %5.2f", calculValoare(h, 23, 2018, 17, "Poiana Vesela"));
	printf("\n\nNumarul cotelor care depases 200 este %d", numarCote(h, 200));
	printf("\n\nStergerea cotelor 23 de pe strada Poiana Vesela numar 7");
	h.tabela[functieHash(23)] = stergereLista(h.tabela[functieHash(23)], 17, "Poiana Vesela");
	traversareHashTable(h);
	getchar();
	getchar();
	return 0;
}