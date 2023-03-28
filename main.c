#include "clientsInStore.h"

void main(void)
{
    struct clientsInStore *clientsInStore = createClientsInStore();
    int test[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        addClient(clientsInStore, &test[i]);
    }
    printf("OG Clients in store: ");
    printClients(clientsInStore);
    struct Node *removedValue = removeClient(clientsInStore, &test[2]);
    if (removedValue != NULL)
    {
        printf("\nRemoved value: %d", *(int *)removedValue->data);
    }
    else
    {
        printf("\nValue not found");
    }
    printf("\nLast Gen Clients in store: ");
    printClients(clientsInStore);
}