#include <iostream>
#include <malloc.h>
#include <stdarg.h>
#define LIMSIZE 128
using namespace std;
struct Buyer {
	char* name;
	float budget;
	Buyer* next;
};
struct Apartment {
	int code;
	int rooms;
	float size;
	float price;
	Buyer* buyers;
};
Apartment* citireApartamente(char* fisier,int* numar) {
	*numar = 0;
	char* token, fis_buf[LIMSIZE];
	FILE* f;
	f = fopen(fisier, "r");
	if (f == NULL) {
		printf("Nu s-a putut citi din fisier");
	}
	else {
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			(*numar)++;
		}
	}
	fclose(f);
	f = fopen(fisier, "r");
	if (f == NULL) {
		printf("Nu s-a putut citi din fisier");
		return NULL;
	}
	else {
		Apartment* apartamente = (Apartment*)malloc(*numar * sizeof(Apartment));
		int i = 0;
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			token = strtok(fis_buf, " ");
			apartamente[i].code = atoi(token);
			token = strtok(NULL, " ");
			apartamente[i].rooms = atoi(token);
			token = strtok(NULL, " ");
			apartamente[i].size = atof(token);
			token = strtok(NULL, " ");
			apartamente[i].price = atof(token);
			apartamente[i].buyers = NULL;
			i++;
		}
		fclose(f);
		return apartamente;
	}
}
void afisareApartamente(Apartment* apartamente,int numar) {
	printf("\nAfisare vector de apartamente:\n");
	for (int i = 0; i < numar; i++) {
		printf("\nApartament: Cod: %d,Camere: %d, Marimea: %5.2f, Pret: %5.2f", apartamente[i].code, apartamente[i].rooms, apartamente[i].size, apartamente[i].price);
		Buyer* temp = apartamente[i].buyers;
		while (temp) {
			printf("\nCumparator: Nume: %s, Buget: %5.2f;", temp->name, temp->budget);
			temp = temp->next;
		}
	}
}
Buyer* citireCumparator() {
	Buyer* buyer = (Buyer*)malloc(sizeof(Buyer));
	printf("Care este numele cumparatorului?");
	char buffer[50];
	scanf("%s", buffer);
	buyer->name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
	strcpy(buyer->name, buffer);
	printf("Care este bugetul cumparatorului?");
	scanf("%f", &buyer->budget);
	buyer->next = NULL;
	return buyer;
}
void afisareFunctie(Apartment* apartamente,int numar,float valoare) {
	printf("\nAfisare apartamente conditionate:\n");
	for (int i = 0; i < numar; i++) {
		if (apartamente[i].size > valoare) {
			printf("\nApartament: Cod: %d,Camere: %d, Marimea: %5.2f, Pret: %5.2f", apartamente[i].code, apartamente[i].rooms, apartamente[i].size, apartamente[i].price);
			Buyer* temp = apartamente[i].buyers;
			while (temp) {
				if (temp->budget >= apartamente[i].price*apartamente[i].size) {
					printf("\nCumparator: Nume: %s, Buget: %5.2f;", temp->name, temp->budget);
				}
				temp = temp->next;
			}
		}
	}
}
void stergereCumparator(Apartment* apartamente,int numar,char* nume) {
	for (int i = 0; i < numar; i++) {
		Buyer* temp = apartamente[i].buyers;
		if(temp&&strcmp(temp->name,nume)==0){
			apartamente[i].buyers = apartamente[i].buyers->next;
			free(temp->name);
			free(temp);
		}
		else {
			if (temp) {
				while (temp->next&&strcmp(temp->next->name, nume) != 0) {
					temp = temp->next;
				}
				if (temp->next) {
					Buyer* temp2 = temp->next;
					temp->next = temp->next->next;
					free(temp2->name);
					free(temp2);
				}
			}
		}
	}
}
void adaugareCumparator(Apartment* apartamente, int numar, int cod) {
	for (int i = 0; i < numar; i++) {
		if (apartamente[i].code == cod) {
			if (apartamente[i].buyers == NULL) {
				apartamente[i].buyers = citireCumparator();
			}
			else {
				Buyer* temp = apartamente[i].buyers;
				while (temp->next) {
					temp = temp->next;
				}
				temp->next = citireCumparator();
			}
		}
	}
}
int main() {
	char fisier[] = "buyers.txt";
	int numar = 0;
	Apartment* apartamente = citireApartamente(fisier, &numar);
	afisareApartamente(apartamente, numar);
	adaugareCumparator(apartamente, numar, 1);
	adaugareCumparator(apartamente, numar, 1);
	adaugareCumparator(apartamente, numar, 2);
	adaugareCumparator(apartamente, numar, 3);
	adaugareCumparator(apartamente, numar, 3);
	afisareApartamente(apartamente, numar);
	printf("\n\n\n");
	afisareFunctie(apartamente, numar, 25);
	printf("\n\n\n");
	char nume[] = "1";
	stergereCumparator(apartamente, numar, nume);
	afisareFunctie(apartamente, numar, 25);
	getchar();
	getchar();
	return 0;
}
