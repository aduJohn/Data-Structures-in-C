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
struct nodArb {
	Student* student;
	nodArb* st;
	nodArb* dr;
};
void inserare(nodArb** root, Student* student) {
	if (*root == NULL) {
		nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
		nou->dr = NULL;
		nou->st = NULL;
		nou->student = student;
		*root = nou;
	}
	else {
		if ((*root)->student->cod == student->cod) {
			printf("\nStudentul exista deja\n");
		}
		else if ((*root)->student->cod < student->cod) {
			inserare(&(*root)->dr, student);
		}
		else {
			inserare(&(*root)->st, student);
		}
	}
}
void preordine(nodArb* root) {
	if (root) {
		printf("\nStudent: Cod: %d, Nume: %s, Medie:%5.2f", root->student->cod, root->student->nume, root->student->medie);
		preordine(root->st);
		preordine(root->dr);
	}
}
void inordine(nodArb* root) {
	if (root) {
		preordine(root->st);
		printf("\nStudent: Cod: %d, Nume: %s, Medie:%5.2f", root->student->cod, root->student->nume, root->student->medie);
		preordine(root->dr);
	}
}
void postordine(nodArb* root) {
	if (root) {
		preordine(root->st);
		preordine(root->dr);
		printf("\nStudent: Cod: %d, Nume: %s, Medie:%5.2f", root->student->cod, root->student->nume, root->student->medie);
	}
}
void citireFisier(char* fisier, nodArb** root) {
	char* token, fis_buf[LIMSIZE];
	FILE* f;
	f = fopen(fisier, "r");
	if (f) {
		while (fgets(fis_buf, sizeof(fis_buf), f)) {
			Student* student = (Student*)malloc(sizeof(Student));
			token = strtok(fis_buf, ",");
			student->cod = atoi(token);
			token = strtok(NULL, ",");
			student->nume = (char*)malloc((strlen(token) + 1));
			strcpy(student->nume, token);
			token = strtok(NULL, ",");
			student->medie = atof(token);
			inserare(root, student);
		}
		fclose(f);
	}
	else {
		printf("Nu s-a putut deschide fisierul");
		*root = NULL;
	}
}
int main() {
	nodArb* root = NULL;
	char fisier[] = "trees.txt";
	citireFisier(fisier, &root);
	printf("\nPREORDINE:\n");
	preordine(root);
	printf("\nINORDINE:\n");
	inordine(root);
	printf("\nPOSTORDINE:\n");
	postordine(root);
	getchar();
	getchar();
	return 0;
}