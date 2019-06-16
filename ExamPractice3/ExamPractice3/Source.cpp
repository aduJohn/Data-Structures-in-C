#include <iostream>
#include <stdio.h>
#include <malloc.h>
#define LIMSIZE 128
using namespace std;
struct Monitor {
	int cod;
	char* producator;
	float diagonala;
	int numarPorturi;
};
struct nodls {
	Monitor* info;
	nodls* next;
};
void inserareLista(nodls** cap, Monitor* monitor) {
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info = monitor;
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
		nou->next = *cap;
		temp->next = nou;
	}
}
void citireFisier(char* fisier, nodls** cap) {
	FILE* f;
	f = fopen(fisier, "r");
	if (f != NULL) {
		char* token, fis_buf[LIMSIZE];
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			Monitor* monitor = (Monitor*)malloc(sizeof(Monitor));
			token = strtok(fis_buf, ",");
			monitor->cod = atoi(token);
			token = strtok(NULL, ",");
			monitor->producator = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(monitor->producator, token);
			token = strtok(NULL, ",");
			monitor->diagonala = atof(token);
			token = strtok(NULL, ",");
			monitor->numarPorturi = atoi(token);
			inserareLista(cap, monitor);
		}
		fclose(f);
	}
	else {
		printf("Nu s-a putut deschide fisierul");
	}
}
void traversareLista(nodls* cap) {
	nodls* temp = cap;
	if (cap != NULL) {
		printf("\nAfisare lista simpla circulara:\n");
		while (temp->next != cap) {
			printf("\nMonitor: Cod: %d, Producator: %s, Diagonala: %5.2f, Numar porturi: %d", temp->info->cod, temp->info->producator, temp->info->diagonala, temp->info->numarPorturi);
			temp = temp->next;
		}
		printf("\nMonitor: Cod: %d, Producator: %s, Diagonala: %5.2f, Numar porturi: %d", temp->info->cod, temp->info->producator, temp->info->diagonala, temp->info->numarPorturi);
	}
}
Monitor* extragereLista(nodls** cap,int cod) {
	if (*cap == NULL) {
		return NULL;
	}
	else {
		if ((*cap)->next == *cap) {
			if ((*cap)->info->cod == cod) {
				Monitor* monitor = (*cap)->info;
				free(*cap);
				*cap = NULL;
				return monitor;
			}
			else {
				return NULL;
			}
		}
		else {
			nodls* temp = *cap;
			while (temp->next != *cap&&temp->next->info->cod != cod) {
				temp = temp->next;
			}
			if (temp->next->info->cod == cod) {
				if (temp->next == *cap) {
					Monitor* monitor = temp->next->info;
					nodls* temp2 = temp->next;
					temp->next = temp2->next;
					free(temp2);
					*cap = temp->next;
					return monitor;
				}
				else {
					Monitor* monitor = temp->next->info;
					nodls* temp2 = temp->next;
					temp->next = temp2->next;
					free(temp2);
					return monitor;
				}
			}
			else {
				return NULL;
			}
		}
	}
}
void afisareMonitoare(nodls** cap,float diagonala) {
	Monitor* monitor = extragereLista(cap, (*cap)->info->cod);
	printf("\nAfisarea monitoarele cu diagonala mai mare de %5.2f:", diagonala);
	while (monitor&&*cap) {
		if (monitor->diagonala > diagonala) {
			printf("\nMonitor: Cod: %d, Producator: %s, Diagonala: %5.2f, Numar porturi: %d", monitor->cod, monitor->producator, monitor->diagonala, monitor->numarPorturi);
		}
		monitor = extragereLista(cap, (*cap)->info->cod);
	}
}
void dezalocareLista(nodls** cap) {
	nodls* temp = *cap;
	if (*cap != NULL) {
		while (temp->next != *cap) {
			nodls* temp2 = temp;
			temp = temp->next;
			free(temp2->info->producator);
			free(temp2);
		}
		free(temp->info->producator);
		free(temp);
	}
	*cap = NULL;
}
int main() {
	nodls* cap = NULL;
	char fisier[] = "monitor.txt";
	citireFisier(fisier, &cap);
	traversareLista(cap);
	printf("\nOperatiunea de extragere:\n");
	printf("\nExtragerea nodului 3\n");
	Monitor* monitor = extragereLista(&cap, 5234);
	if (monitor) {
		printf("\nMonitor: Cod: %d, Producator: %s, Diagonala: %5.2f, Numar porturi: %d", monitor->cod, monitor->producator, monitor->diagonala, monitor->numarPorturi);
	}
	printf("\nAfisare restului din lista\n");
	traversareLista(cap);
	afisareMonitoare(&cap, 24);
	traversareLista(cap);
	dezalocareLista(&cap);
	getchar();
	getchar();
	return 0;
}