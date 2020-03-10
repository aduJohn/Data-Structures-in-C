#include <iostream>
#include <cstring>
using namespace std;
struct Masina
{
    char *numarInmatriculare;
    char *marca;
    int numarOreParcare;
    float plata;
};
struct Coada
{
    Masina *masina;
    Coada *next;
};
struct CircularDoubleLinkedList
{
    Masina *masina;
    CircularDoubleLinkedList *prev;
    CircularDoubleLinkedList *next;
};
//Functii Masina
Masina *citireMasina()
{
    Masina *masina = (Masina *)malloc(sizeof(Masina));
    printf("\nCitire masina:");

    printf("\n\tNumar inmatriculare:");
    char buffer[50];
    scanf("%s", buffer);
    masina->numarInmatriculare = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(masina->numarInmatriculare, buffer);

    printf("\n\tMarca: ");
    scanf("%s", buffer);
    masina->marca = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(masina->marca, buffer);

    printf("\n\tNumar de ore parcare:");
    scanf("%i", &masina->numarOreParcare);

    printf("\n\tPlata:");
    scanf("%f", &masina->plata);

    return masina;
}
void afisareMasina(Masina *masina)
{
    printf("\nAfisare masina:");
    printf("\n\tNumar inmatriculare masina: %s", masina->numarInmatriculare);
    printf("\n\tMarca masina: %s", masina->marca);
    printf("\n\tNumarul de ore in parcare: %i", masina->numarOreParcare);
    printf("\n\tPlata: %5.2f", masina->plata);
    printf("\n");
}
//Queue functions
void inserareElementCoada(Coada **start)
{
    //Construim un nou element pe care sa il inseram in coada
    Coada *nodNou = (Coada *)malloc(sizeof(Coada));
    nodNou->masina = citireMasina();
    nodNou->next = NULL;
    //Verificam daca in coada exista sau nu un element
    if (*start)
    {
        //Daca exista trebuie sa parcurgem coada pana la ultimul element (FIFO)
        Coada *temp = *start;
        while (temp->next)
        {
            temp = temp->next;
        }
        //Odata ajunsi la capatul cozii legam de coada noul element
        temp->next = nodNou;
    }
    else
    {
        //Daca nu exista coada, atunci nodul creat este fix coada si noul inceput al cozii
        *start = nodNou;
    }
}
Masina *extragereNod(Coada **start)
{
    //Cand extragem din coada ne asiguram ca avem ce sa extragem
    if (*start)
    {
        //Pentru ca extragem din coada atunci o sa extragem fix primul element
        //Deci trebuie sa preluam comanda si sa mutam noul start al cozii
        Masina *nodExtras = (*start)->masina;
        Coada *temp = *start;
        *start = (*start)->next;
        free(temp);
        return nodExtras;
    }
    else
    {
        return NULL;
    }
}
void afisareCoada(Coada *start)
{
    //Pentru afisarea cozii parcurgem din nod in nod coada si afisam continutul
    printf("\nAfisare coada:");
    while (start)
    {
        //Functia ajutatoare pentru afisarea cozii
        afisareMasina(start->masina);
        start = start->next;
        printf("\n");
    }
}
void dezalocareCoada(Coada **start)
{
    //Verificam daca avem ceva de extras
    if (*start)
    {
        //Mergem din nod in nod si stergem succesiv
        Coada *temp = *start;
        while (temp->next)
        {
            //Ne copiem nodul actual intr-o alta variabila pentru ca
            //in momentul in care inaintam cu urmatorul nod sa putem
            //sa stergem nodurile fara a pierde ordinea cozii
            Coada *temp2 = temp->next;
            temp = temp->next;
            free(temp->masina->numarInmatriculare);
            free(temp->masina->marca);
            free(temp);
            temp = temp2;
        }
        *start = NULL;
    }
}
//Functii Lista dubla circulara
void inserareListaDublaCirculara(CircularDoubleLinkedList **start, CircularDoubleLinkedList **final, Masina *masina)
{
    CircularDoubleLinkedList *nodNou = (CircularDoubleLinkedList *)malloc(sizeof(CircularDoubleLinkedList));
    nodNou->masina = masina;
    nodNou->next = NULL;
    nodNou->prev = NULL;
    if (*start)
    {
        CircularDoubleLinkedList *temp = *start;
        while (temp != *final)
        {
            temp = temp->next;
        }
        temp->next = nodNou;
        nodNou->prev = temp;
        (*start)->prev = nodNou;
        nodNou->next = *start;
        *final = nodNou;
    }
    else
    {
        nodNou->next = nodNou;
        nodNou->prev = nodNou;
        *start = nodNou;
        *final = nodNou;
    }
}
void afisareListaDublaCirculara(CircularDoubleLinkedList *start)
{
    CircularDoubleLinkedList *temp = start;
    afisareMasina(start->masina);
    while (temp->next != start)
    {
        temp = temp->next;
        afisareMasina(temp->masina);
    }
}
int numarNoduriListaCircularaDubla(CircularDoubleLinkedList *start)
{
    int numarNoduri;
    if (start)
    {
        numarNoduri = start->masina->numarOreParcare == 4 ? 1 : 0;
        CircularDoubleLinkedList *temp = start;
        while (temp->next != start)
        {
            temp = temp->next;
            numarNoduri = temp->masina->numarOreParcare == 4 ? numarNoduri + 1 : numarNoduri;
        }
    }
    else
    {
        numarNoduri = 0;
    }
    return numarNoduri;
}
Masina *extragereMasini(CircularDoubleLinkedList *start)
{
    CircularDoubleLinkedList *temp = start;
    Masina *masini = (Masina *)malloc(sizeof(Masina) * numarNoduriListaCircularaDubla(start));
    int i = 0;
    if (start->masina->numarOreParcare == 4)
    {
        masini[i].numarInmatriculare = (char *)malloc((strlen(start->masina->numarInmatriculare) + 1) * sizeof(char));
        strcpy(masini[i].numarInmatriculare, start->masina->numarInmatriculare);
        masini[i].marca = (char *)malloc((strlen(start->masina->marca) + 1) * sizeof(char));
        strcpy(masini[i].marca, start->masina->marca);
        masini[i].numarOreParcare = start->masina->numarOreParcare;
        masini[i].plata = start->masina->plata;
        i++;
    }
    while (temp->next != start)
    {
        temp = temp->next;
        if (temp->masina->numarOreParcare == 4)
        {
            masini[i].numarInmatriculare = (char *)malloc((strlen(temp->masina->numarInmatriculare) + 1) * sizeof(char));
            strcpy(masini[i].numarInmatriculare, temp->masina->numarInmatriculare);
            masini[i].marca = (char *)malloc((strlen(temp->masina->marca) + 1) * sizeof(char));
            strcpy(masini[i].marca, temp->masina->marca);
            masini[i].numarOreParcare = temp->masina->numarOreParcare;
            masini[i].plata = temp->masina->plata;
            i++;
        }
    }
    return masini;
}
void dezalocareListaDublaCirculara(CircularDoubleLinkedList **start, CircularDoubleLinkedList **final)
{
    CircularDoubleLinkedList *temp = *start;
    while (temp != *final)
    {
        CircularDoubleLinkedList *temp2 = temp;
        temp = temp->next;
        free(temp2->masina->numarInmatriculare);
        free(temp2->masina->marca);
        free(temp2);
    }
    free(temp->masina->numarInmatriculare);
    free(temp->masina->marca);
    free(temp);
    *start = NULL;
    *final = NULL;
}
int main()
{
    //Cerinta2
    Coada *startCoada = NULL;
    for (int i = 0; i < 5; i++)
    {
        inserareElementCoada(&startCoada);
    }
    //Cerinta3
    printf("\n\n");
    afisareCoada(startCoada);
    //Cerinta4
    printf("\n\n");
    CircularDoubleLinkedList *startCDL = NULL;
    CircularDoubleLinkedList *finalCDL = NULL;
    while (startCoada)
    {
        Masina *masinaExtrasa = extragereNod(&startCoada);
        inserareListaDublaCirculara(&startCDL, &finalCDL, masinaExtrasa);
    }
    printf("\nAfisarea restului din coada:");
    afisareCoada(startCoada);
    printf("\nAfisarea lisei noi:");
    afisareListaDublaCirculara(startCDL);
    //Cerinta5
    printf("\n\n");
    printf("\nAfisare masini:");
    Masina *masini = extragereMasini(startCDL);
    for (int i = 0; i < numarNoduriListaCircularaDubla(startCDL); i++)
    {
        afisareMasina(&masini[i]);
    }
    dezalocareListaDublaCirculara(&startCDL, &finalCDL);
    dezalocareCoada(&startCoada);

    return 0;
}