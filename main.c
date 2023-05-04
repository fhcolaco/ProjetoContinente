#include "genericList.h"
#include "functions.h"
#include "clients.h"
#include "employee.h"
#include "eventHorizon.h"

void *showClientByID(struct List *list, int n)
{
    for (int i = 1; i < n; i++)
    {
        list->head = list->head->next;
    }
    struct Client *client = (struct Client *)list->head->data;
    printClient(client);
    printShoppingList(client);
}

int main(void)
{
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList();
    struct List *clientList = createClientList(productList);
    struct List *employeeList = createEmployeeList();
    struct List *eventHorizon = createEventHorizon(clientList);

    printf("\n\33[0;32mData loaded successfully!\n\33[0;97m");
    printf("Exitem %d produtos na Lista PRODUTOS.\n", productList->size);
    printf("Exitem %d clientes na Lista CLIENTES.\n", clientList->size);
    printf("Exitem %d empregados na Lista COLABORADORES.\n", employeeList->size);
    printf("Exitem %d eventos na Lista EVENTOS.\n", eventHorizon->size);

    // WRITE HISTORY TO TXT
    char historyLine[100];
    struct List *eventHorizonCopy = copyList(eventHorizon);
    struct Node *current = (struct Event *)eventHorizonCopy->head;
    FILE *f = fopen("History.txt", "w");
    fprintf(f, "");
    fclose(f);
    while (current != NULL)
    {
        struct Event *event = (struct Event *)current->data;
        sprintf(historyLine, "O Cliente %d chegou à loja ao instante %d", event->client->id, event->time);
        writeLineToTxt(historyLine);
        free(event);
        current = current->next;
    }

    return 0;
};
