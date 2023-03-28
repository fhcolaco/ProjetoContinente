#include "genericList.h"
#include "functions.h"

struct clientsInStore
{
    struct List *clients;
};

void createClientsList(struct clientsInStore *clientsInStore)
{
    clientsInStore->clients = createList();
}

struct clientsInStore *createClientsInStore()
{
    struct clientsInStore *clientsInStore = (struct clientsInStore *)malloc(sizeof(struct clientsInStore));
    createClientsList(clientsInStore);
    return clientsInStore;
}

void addClient(struct clientsInStore *clientsInStore, void *client)
{
    addToBackOfList(clientsInStore->clients, client);
}

struct Node *removeClient(struct clientsInStore *clientsInStore, void *client)
{
    return removeFromList(clientsInStore->clients, client);
}

// void printClients(struct clientsInStore *clientsInStore, void (*printData)(void *))
// {
//     struct Node *current = clientsInStore->clients->head;
//     while (current != NULL)
//     {
//         printData(current->data->a);
//         printData(current->data->b);
//         current = current->next;
//     }
// }
