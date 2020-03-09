#include <iostream>
#include <cstring>
using namespace std;
struct Fisier
{
    char *denumireFisier;
    char *path;
    char *extensie;
    unsigned int dimensiune;
};
struct DoubleLinkedList
{
    Fisier *fisier;
    DoubleLinkedList *prev;
    DoubleLinkedList *next;
};
//Functii Fisier
Fisier *citireFisier()
{
    Fisier *fisier = (Fisier *)malloc(sizeof(Fisier));
    printf("\nCitire fisier:");
    char buffer[50];
    printf("\n\tCare este denumire fisierului?");
    scanf("%s", buffer);
    fisier->denumireFisier = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(fisier->denumireFisier, buffer);

    printf("\n\tCare este calea fisierului?");
    scanf("%s", buffer);
    fisier->path = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(fisier->path, buffer);

    printf("\n\tCare este extensia fisierului?");
    scanf("%s", buffer);
    fisier->extensie = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(fisier->extensie, buffer);

    printf("\n\tCare este dimensiunea fisierului?");
    scanf("%i", &fisier->dimensiune);

    return fisier;
}
void afisareFisier(Fisier *fisier)
{
    printf("\nAfisare fisier:");
    printf("\n\tDenumire fisier: %s", fisier->denumireFisier);
    printf("\n\tCale fisier: %s", fisier->path);
    printf("\n\tExtensie fisier: %s", fisier->extensie);
    printf("\n\tDimensiune fisier: %i", fisier->dimensiune);
    printf("\n");
}
//Functii lista dubla
void inserareListaDubla(DoubleLinkedList **start, DoubleLinkedList **final)
{
    DoubleLinkedList *nodNou = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    nodNou->fisier = citireFisier();
    nodNou->next = NULL;
    nodNou->prev = NULL;

    if (*start)
    {
        DoubleLinkedList *temp = *start;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = nodNou;
        nodNou->prev = temp;
    }
    else
    {
        *start = nodNou;
    }
    *final = nodNou;
}
void traversareDirecta(DoubleLinkedList *start)
{
    printf("\nTraversarea directa a listei duble inlantuite:");
    while (start)
    {
        printf("\n\tAfisare nod:");
        afisareFisier(start->fisier);
        start = start->next;
    }
}
void traversareIndirecta(DoubleLinkedList *final)
{
    printf("\nTraversarea inversa a listei duble inlantuite:");
    while (final)
    {
        printf("\n\tAfisare nod:");
        afisareFisier(final->fisier);
        final = final->prev;
    }
}
int numarDeFisiereDupaExtensie(DoubleLinkedList *start, const char *extensie)
{
    int numarFisiere = 0;
    while (start)
    {
        if (strcmp(start->fisier->extensie, extensie) == 0)
        {
            numarFisiere++;
        }
        start = start->next;
    }
    return numarFisiere;
}
Fisier *gasireFisiere(DoubleLinkedList *start, const char *extensie)
{
    Fisier *fisiere = (Fisier *)malloc(sizeof(Fisier) * numarDeFisiereDupaExtensie(start, extensie));
    int i = 0;
    while (start)
    {
        if (strcmp(start->fisier->extensie, extensie) == 0)
        {
            fisiere[i].denumireFisier = (char *)malloc((strlen(start->fisier->denumireFisier) + 1) * sizeof(char));
            strcpy(fisiere[i].denumireFisier, start->fisier->denumireFisier);
            fisiere[i].extensie = (char *)malloc((strlen(start->fisier->extensie) + 1) * sizeof(char));
            strcpy(fisiere[i].extensie, start->fisier->extensie);
            fisiere[i].path = (char *)malloc((strlen(start->fisier->path) + 1) * sizeof(char));
            strcpy(fisiere[i].path, start->fisier->path);
            fisiere[i].dimensiune = start->fisier->dimensiune;
            i++;
        }
        start = start->next;
    }
    return fisiere;
}
void modificareCale(DoubleLinkedList *start, const char *caleVeche, const char *caleNoua)
{
    while (start)
    {
        if (strcmp(start->fisier->path, caleVeche) == 0)
        {
            free(start->fisier->path);
            start->fisier->path = (char *)malloc((strlen(caleNoua) + 1) * sizeof(char));
            strcpy(start->fisier->path, caleNoua);
        }
        start = start->next;
    }
}
void dezalocareListaDubla(DoubleLinkedList **start, DoubleLinkedList **final)
{
    while (*start)
    {
        DoubleLinkedList *temp = *start;
        *start = (*start)->next;

        free(temp->fisier->denumireFisier);
        free(temp->fisier->extensie);
        free(temp->fisier->path);
        free(temp);
    }
    *final = NULL;
}
int main()
{
    //Cerinta2
    DoubleLinkedList *start = NULL;
    DoubleLinkedList *final = NULL;
    for (int i = 0; i < 5; i++)
    {
        inserareListaDubla(&start, &final);
    }
    //Cerinta3
    printf("\n\n");
    traversareDirecta(start);
    traversareIndirecta(final);
    //Cerinta4
    printf("\n\n");
    printf("\nAfisare fisiere dupa extensia txt:");
    Fisier *fisiere = gasireFisiere(start, "txt");
    for (int i = 0; i < numarDeFisiereDupaExtensie(start, "txt"); i++)
    {
        afisareFisier(&fisiere[i]);
    }
    //Cerinta5
    printf("\n\n");
    printf("\nAfisarea listei duble dupa modificare:");
    modificareCale(start, "ceva", "altceva");
    traversareDirecta(start);
    dezalocareListaDubla(&start, &final);
    return 0;
}