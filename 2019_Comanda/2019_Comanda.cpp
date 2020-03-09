#include <iostream>
#include <cstring>
using namespace std;
// definirea structurii comanda
struct Comanda
{
    int codComanda;
    char *numeClient;
    int numarProduse;
    char **denumireProduse;
    float sumaDePlata;
};
// definirea cozii
struct Coada
{
    Comanda *comanda;
    Coada *next;
};
struct doubleLinkedList
{
    Comanda *comanda;
    doubleLinkedList *prev;
    doubleLinkedList *next;
};
//Comanda functions
Comanda *citireComanda()
{
    Comanda *comanda = (Comanda *)malloc(sizeof(Comanda));
    printf("\nCare este codul comenzii?");
    scanf("%d", &comanda->codComanda);
    char buffer[50];
    printf("\nCare este numele clientului?");
    scanf("%s", buffer);
    comanda->numeClient = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(comanda->numeClient, buffer);
    printf("\nCare este numarul de produse?");
    scanf("%d", &comanda->numarProduse);
    comanda->denumireProduse = (char **)malloc(comanda->numarProduse * sizeof(char *));
    for (int i = 0; i < comanda->numarProduse; i++)
    {
        printf("\nCare este denumire produsului %d ?", i + 1);
        scanf("%s", buffer);
        comanda->denumireProduse[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(comanda->denumireProduse[i], buffer);
    }
    printf("\nCare este pretul comenzii?");
    scanf("%f", &comanda->sumaDePlata);
    return comanda;
}
void afisareComanda(Comanda *comanda)
{
    printf("\nAfisare comanda:");
    printf("\n\tCodul comenzii: %d", comanda->codComanda);
    printf("\n\tNume client: %s", comanda->numeClient);
    printf("\n\tAfisare produse:");
    for (int i = 0; i < comanda->numarProduse; i++)
    {
        printf("\n\t\tDenumire produs %i : %s", i + 1, comanda->denumireProduse[i]);
    }
    printf("\n\tSuma de plata: %5.2f", comanda->sumaDePlata);
    printf("\n");
}

//Queue functions
void inserareElementCoada(Coada **start)
{
    //Construim un nou element pe care sa il inseram in coada
    Coada *nodNou = (Coada *)malloc(sizeof(Coada));
    nodNou->comanda = citireComanda();
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
Comanda *extragereNod(Coada **start)
{
    //Cand extragem din coada ne asiguram ca avem ce sa extragem
    if (*start)
    {
        //Pentru ca extragem din coada atunci o sa extragem fix primul element
        //Deci trebuie sa preluam comanda si sa mutam noul start al cozii
        Comanda *nodExtras = (*start)->comanda;
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
        afisareComanda(start->comanda);
        start = start->next;
        printf("\n");
    }
}
void dezalocareCoada(Coada **start)
{
    //Verificam daca avem ceva de extras
    if (start)
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
            free(temp->comanda->numeClient);
            for (int i = 0; i < temp->comanda->numarProduse; i++)
            {
                free(temp->comanda->denumireProduse[i]);
            }
            free(temp->comanda->denumireProduse);
            free(temp);
            temp = temp2;
        }
        *start = NULL;
    }
}
//DoubleLinkedList functions
void inserareListaDubla(doubleLinkedList **start, Comanda *comanda)
{
    //Inserarea in lista dubla este asemanatoare cu cea a cozii doar ca trebuie
    //Sa ne asiguram ca avem si legatura cu nodurile anterioare
    doubleLinkedList *nodNou = (doubleLinkedList *)malloc(sizeof(doubleLinkedList));
    nodNou->comanda = comanda;
    nodNou->prev = NULL;
    nodNou->next = NULL;
    if (*start)
    {
        doubleLinkedList *temp = *start;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = nodNou;
        nodNou->prev = nodNou;
    }
    else
    {
        *start = nodNou;
    }
}
void afisareListaDubla(doubleLinkedList *start)
{
    printf("\nAfisare lista dubla:");
    while (start)
    {
        afisareComanda(start->comanda);
        start = start->next;
        printf("\n");
    }
}
//Funcite ajutatoare pentru a identifica numarul corect de noduri
//Ultima cerinta presupune formarea unui vector de comenzi
//In momentul initierii vectoruluia avem nevoie de numarul de elemente
//al liste duble
int numarDeElementeInListaDubla(doubleLinkedList *start)
{
    int numarElemente = 0;
    while (start)
    {
        numarElemente++;
        start = start->next;
    }
    return numarElemente;
}
Comanda *salvareComenziInVector(doubleLinkedList *start)
{
    //Ne folosim de functia anterioara pentru a aloca dinamic vectorul
    Comanda *comenzi = (Comanda *)malloc(sizeof(Comanda) * numarDeElementeInListaDubla(start));
    int i = 0;
    while (start)
    {
        //Parcurgem lista dubla si copiem din continut in fiecare element al vectorului de comenzi
        comenzi[i].codComanda = start->comanda->codComanda;
        comenzi[i].numarProduse = start->comanda->numarProduse;
        comenzi[i].sumaDePlata = start->comanda->sumaDePlata;
        comenzi[i].numeClient = (char *)malloc(sizeof(char) * (strlen(start->comanda->numeClient) + 1));
        strcpy(comenzi[i].numeClient, start->comanda->numeClient);
        comenzi[i].denumireProduse = (char **)malloc(sizeof(char *) * comenzi[i].numarProduse);
        for (int j = 0; j < start->comanda->numarProduse; j++)
        {
            comenzi[i].denumireProduse[j] = (char *)malloc((strlen(start->comanda->denumireProduse[j]) + 1) * sizeof(char));
            strcpy(comenzi[i].denumireProduse[j], start->comanda->denumireProduse[j]);
        }
        i++;
        start = start->next;
    }
    return comenzi;
}
void dezalocareListaDubla(doubleLinkedList **start)
{
    if (*start)
    {
        doubleLinkedList *temp = *start;
        while (temp)
        {
            doubleLinkedList *temp2 = temp->next;
            temp = temp->next;
            free(temp->comanda->numeClient);
            for (int i = 0; i < temp->comanda->numarProduse; i++)
            {
                free(temp->comanda->denumireProduse[i]);
            }
            free(temp->comanda->denumireProduse);
            free(temp);
            temp = temp2;
        }
        *start = NULL;
    }
}
int main()
{
    Coada *start = NULL;
    //Cerinta2
    for (int i = 0; i < 5; i++)
    {
        inserareElementCoada(&start);
    }
    //Cerinta3
    afisareCoada(start);
    //Cerinta4
    printf("\n\n");
    doubleLinkedList *comenziPeste200 = NULL;
    doubleLinkedList *comenziSub200 = NULL;
    while (start)
    {
        Comanda *dummy = extragereNod(&start);
        if (dummy->sumaDePlata > 200)
        {
            inserareListaDubla(&comenziPeste200, dummy);
        }
        else
        {
            inserareListaDubla(&comenziSub200, dummy);
        }
    }
    printf("\nCoada lasata:");
    afisareCoada(start);
    printf("\nLista dubla cu acele comenzi sub 200(inclusiv):");
    afisareListaDubla(comenziSub200);
    printf("\nLista dubla cu acele comenzi peste 200:");
    afisareListaDubla(comenziPeste200);
    printf("\n\n");
    //Cerinta5
    Comanda *vectorComenzi = NULL;
    vectorComenzi = salvareComenziInVector(comenziPeste200);
    printf("\nAfisare comenzi:");
    for (int i = 0; i < numarDeElementeInListaDubla(comenziPeste200); i++)
    {
        afisareComanda(&vectorComenzi[i]);
    }
    return 0;
}