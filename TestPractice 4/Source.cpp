//~45min
#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
struct Fisier {
	char* denumire;
	char* cale;
	char* extensie;
	unsigned int dimensiune;
};
struct nodlp {
	Fisier* info;
	nodlp* next;
	nodlp* prev;
};
Fisier* citireFisier() {
	Fisier* file = (Fisier*)malloc(sizeof(Fisier));
	char buffer[50];
	printf("\nCare este denumire fisierului?");
	scanf("%s", buffer);
	file->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->denumire, buffer);
	printf("\nCare este cale fisierului?");
	scanf("%s", buffer);
	file->cale = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->cale, buffer);
	printf("\nCare este extensia fisierului?");
	scanf("%s", buffer);
	file->extensie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(file->extensie, buffer);
	printf("\nCare este dimensiunea fisierului?");
	scanf("%d", &file->dimensiune);
	return file;
}
void inserareListaDubla(nodlp** cap,nodlp** coada,Fisier* file) {
	nodlp* nou = (nodlp*)malloc(sizeof(nodlp));
	nou->info = file;
	nou->next = NULL;
	nou->prev = NULL;
	if (*cap == NULL) {
		*cap = nou;
		*coada = nou;
	}
	else {
		nodlp* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
}
void traversareListaDubla(nodlp* cap) {
	nodlp* temp = cap;
	printf("\n");
	printf("\nAfisare fisiere in sens direct:");
	while (temp) {
		printf("\nFisier:");
		printf("\n\tDenumire %s ", temp->info->denumire);
		printf("\n\tCale %s ", temp->info->cale);
		printf("\n\tExtensie %s ", temp->info->extensie);
		printf("\n\tDimensiune %d ", temp->info->dimensiune);
		temp = temp->next;
	}
}
void traversareListaDublaInvers(nodlp* coada) {
	nodlp* temp = coada;
	printf("\n");
	printf("\nAfisare fisiere in sens invers:");
	while (temp) {
		printf("\nFisier:");
		printf("\n\tDenumire %s ", temp->info->denumire);
		printf("\n\tCale %s ", temp->info->cale);
		printf("\n\tExtensie %s ", temp->info->extensie);
		printf("\n\tDimensiune %d ", temp->info->dimensiune);
		temp = temp->prev;
	}
}
Fisier** cautareFisiereExtensie(nodlp* cap,char* extensie,int* numarFisiereExtensie) {
	Fisier** file = NULL;
	nodlp* temp = cap;
	while (temp) {
		if ((strcmp(temp->info->extensie, extensie) == 0)) {
			Fisier** dummy = file;
			(*numarFisiereExtensie)++;
			file = (Fisier**)malloc((*numarFisiereExtensie) * sizeof(Fisier*));
			for (int i = 0; i < *numarFisiereExtensie - 1; i++) {
				file[i] = dummy[i];
			}
			file[*numarFisiereExtensie - 1] = temp->info;
			free(dummy);
		}
		temp = temp->next;
	}
	return file;
}
void modificareFisiere(nodlp* cap,char* caleCurenta,char* caleNoua) {
	nodlp* temp = cap;
	while (temp!=NULL&&(strcmp(temp->info->cale,caleCurenta)!=0)) {
		temp = temp->next;
	}
	if (temp) {
		free(temp->info->cale);
		temp->info->cale = (char*)malloc((strlen(caleNoua) + 1) * sizeof(char));
		strcpy(temp->info->cale, caleNoua);
	}
	else {
		printf("\nNu s-a gasit calea precizata");
	}
}
void dezalocareListaDubla(nodlp** cap, nodlp** coada) {
	nodlp* temp = *cap;
	while (temp) {
		nodlp* temp2 = temp;
		temp = temp->next;
		free(temp2->info->denumire);
		free(temp2->info->cale);
		free(temp2->info->extensie);
		free(temp2);
	}
}
int main() {
	nodlp* cap = NULL;
	nodlp* coada = NULL;
	//CERINTA II
	printf("\nCerinta II\n");
	for (int i = 0; i < 5; i++) {
		Fisier* file = citireFisier();
		inserareListaDubla(&cap,&coada,file);
	}
	//CERINTA III
	printf("\nCerinta III\n");
	traversareListaDubla(cap);
	traversareListaDublaInvers(coada);
	//CERINTA VI
	printf("\nCerinta VI\n");
	printf("\nCare este extensia cautata?");
	char buffer[50];
	int n = 0;
	scanf("%s", buffer);
	Fisier** copie = cautareFisiereExtensie(cap, buffer,&n);
	if (copie) {
		for(int i=0;i<n;i++){
			printf("\nFisier:");
			printf("\n\tDenumire %s ", copie[i]->denumire);
			printf("\n\tCale %s ", copie[i]->cale);
			printf("\n\tExtensie %s ", copie[i]->extensie);
			printf("\n\tDimensiune %d", copie[i]->dimensiune);
		}
		free(copie);
		n = 0;
	}
	else {
		printf("\nNu s-au gasit fisiere cu extensia respectiva");
	}
	//CERINTA V
	printf("\nCerinta V\n");
	printf("\nCare este calea veche?");
	scanf("%s", buffer);
	printf("\nCare este calea noua?");
	char buffer2[50];
	scanf("%s", buffer2);
	modificareFisiere(cap, buffer, buffer2);
	traversareListaDubla(cap);
	dezalocareListaDubla(&cap, &coada);
	printf("\nFINAL\n");
	system("pause");
	return 0;
}