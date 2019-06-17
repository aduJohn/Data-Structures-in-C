#include <iostream>
#include <malloc.h>
#include <stdio.h>
#define LIMSIZE 128
using namespace std;
struct Student {
	int cod;
	char* nume;
	float medie;
};
struct heap{
	Student* student;
	int dimensiune;
};
void filtrare(heap* h,int index) {
	int indexMax = index;
	int indexS = 2 * index + 1;
	int indexD = 2 * index + 2;
	if (indexS<(*h).dimensiune && (*h).student[indexMax].cod<(*h).student[indexS].cod) {
		indexMax = indexS;
	}
	if (indexD<(*h).dimensiune && (*h).student[indexMax].cod<(*h).student[indexD].cod) {
		indexMax = indexD;
	}
	if (indexMax != index) {
		Student aux = (*h).student[indexMax];
		(*h).student[indexMax] = (*h).student[index];
		(*h).student[index] = aux;
		filtrare(h, indexMax);
	}
}
void inserare(heap* h,Student student) {
	Student* studenti = (Student*)malloc(sizeof(Student)*((*h).dimensiune + 1));
	for (int i = 0; i < (*h).dimensiune; i++) {
		studenti[i] = (*h).student[i];
	}
	studenti[(*h).dimensiune] = student;
	(*h).dimensiune++;
	free((*h).student);
	(*h).student = studenti;
	for (int i = ((*h).dimensiune-1); i >= 0; i--) {
		filtrare(h, i);
	}
}
void extragere(heap* h,Student* student) {
	Student* studenti = (Student*)malloc(((*h).dimensiune - 1) * sizeof(Student));
	*student = (*h).student[0];
	for (int i = 1; i < (*h).dimensiune; i++) {
		studenti[i - 1] = (*h).student[i];
	}
	(*h).dimensiune--;
	free((*h).student);
	(*h).student = studenti;
	for (int i=((*h).dimensiune-1)/2;i>=0;i++) {
		filtrare(h, i);
	}
}
void afisare(heap* h) {
	printf("\nAfisare heap:\n");
	for (int i = 0; i < (*h).dimensiune; i++) {
		printf("\nStudent: Cod: %d, Nume: %s, Medie: %5.2f;", (*h).student[i].cod, (*h).student[i].nume, (*h).student[i].medie);
	}
}
void citireFisier(char* fisier,heap* h) {
	FILE* f;
	char* token, fis_buf[LIMSIZE];
	f = fopen(fisier, "r");
	if (f) {
		fgets(fis_buf, sizeof(fis_buf), f);
		token = strtok(fis_buf, " ");
		int numar = atoi(token);
		Student* studenti = (Student*)malloc(numar * sizeof(Student));
		int i = 0;
		while (fgets(fis_buf,sizeof(fis_buf),f)) {
			Student student;
			token = strtok(fis_buf, ",");
			student.cod = atoi(token);
			token = strtok(NULL, ",");
			student.nume = (char*)malloc((strlen(token) + 1));
			strcpy(student.nume, token);
			token = strtok(NULL, ",");
			student.medie = atof(token);
			inserare(h, student);
			i++;
		}
		//(*h).dimensiune = i;
		//(*h).student = studenti;
		//for (int i = ((*h).dimensiune - 1) / 2; i >= 0; i--) {
		//	filtrare(h, i);

		//}
		fclose(f);
	}
	else {
		printf("Nu s-a putut deschide fisierul");
		h->dimensiune = 0;
		h->student = NULL;
	}
}
int main() {
	heap h;
	h.dimensiune = 0;
	h.student = NULL;
	char fisier[] = "heap.txt";
	citireFisier(fisier, &h);
	Student student;
	student.cod = 14;
	student.medie = 23.2;
	afisare(&h);
	student.nume = (char*)malloc(sizeof(char)*((strlen("Ceva") + 1)));
	strcpy(student.nume, "Ceva");
	inserare(&h, student);
	afisare(&h);
	getchar();
	getchar();
	return 0;
}