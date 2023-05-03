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

    return 0;
};
