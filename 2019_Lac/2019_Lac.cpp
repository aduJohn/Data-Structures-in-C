#include <iostream>
#include <cstring>
using namespace std;
struct Lac
{
    int cod;
    char *denumireLac;
    float suprafata;
    int areInsule;
};
struct DoubleLinkedList
{
    Lac *lac;
    DoubleLinkedList *prev;
    DoubleLinkedList *next;
};
//Functii lac
Lac *citireLac()
{
    Lac *lac = (Lac *)malloc(sizeof(Lac));
    printf("\nCitire lac:");
    printf("\n\tCare este codul lacului:");
    scanf("%i", &lac->cod);

    char buffer[50];
    printf("\n\tCare este denumire lacului?");
    scanf("%s", buffer);
    lac->denumireLac = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(lac->denumireLac, buffer);

    printf("\n\tCare este suprafata lacului?");
    scanf("%f", &lac->suprafata);

    printf("\n\tLacul dispune de insule?");
    scanf("%i", &lac->areInsule);
    return lac;
}
void afisareLac(Lac *lac)
{
    printf("\nAfisare lac:");
    if (lac)
    {
        printf("\n\tCod lac: %i", lac->cod);
        printf("\n\tDenumire lac: %s", lac->denumireLac);
        printf("\n\tSuprafata lac: %5.2f", lac->suprafata);
        printf("\n\tInsule lac: %i", lac->areInsule);
    }
    else
    {
        printf("\n\tLacul nu exista!");
    }
    printf("\n");
}
//Functii lista dubla
void inserareListaDubla(DoubleLinkedList **start, DoubleLinkedList **final)
{
    DoubleLinkedList *nodNou = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    nodNou->lac = citireLac();
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
        afisareLac(start->lac);
        start = start->next;
    }
}
void traversareIndirecta(DoubleLinkedList *final)
{
    printf("\nTraversarea inversa a listei duble inlantuite:");
    while (final)
    {
        printf("\n\tAfisare nod:");
        afisareLac(final->lac);
        final = final->prev;
    }
}
float suprafataTotala(DoubleLinkedList *start)
{
    float suprafata = 0;
    while (start)
    {
        if (start->lac->areInsule == 0)
        {
            suprafata += start->lac->suprafata;
        }
        start = start->next;
    }
    return suprafata;
}
Lac *extragereLac(DoubleLinkedList **start, DoubleLinkedList **final, int cod)
{
    Lac *lacExtras = NULL;
    if ((*start)->lac->cod == cod)
    {
        lacExtras = (*start)->lac;
        DoubleLinkedList *temp = *start;
        *start = (*start)->next;
        if (*start == NULL)
        {
            *final = NULL;
        }
        free(temp);
    }
    else if ((*final)->lac->cod == cod)
    {
        lacExtras = (*final)->lac;
        DoubleLinkedList *temp = *final;
        *final = (*final)->prev;
        (*final)->next = NULL;
        free(temp);
    }
    else
    {
        DoubleLinkedList *temp = *start;
        while (temp && temp->lac->cod != cod)
        {
            temp = temp->next;
        }
        if (temp)
        {
            lacExtras = temp->lac;
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            free(temp);
        }
        else
        {
            lacExtras = NULL;
        }
    }
    return lacExtras;
}
void dezalocareListaDubla(DoubleLinkedList **start, DoubleLinkedList **final)
{
    while (*start)
    {
        DoubleLinkedList *temp = *start;
        *start = (*start)->next;

        free(temp->lac->denumireLac);
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
    printf("\n\nSuprafata totala a lacurilor fara insule este: %5.2f", suprafataTotala(start));
    //Cerinta5
    printf("\n\n");
    afisareLac(extragereLac(&start, &final, 12));
    traversareDirecta(start);
    dezalocareListaDubla(&start, &final);
    return 0;
}