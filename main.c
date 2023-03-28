#include "clients.h"
struct Test
{
    char a;
    int b;
};

int main(void)
{
    // struct clientsInStore *clientsInStore = createClientsInStore();
    // struct Test *test = (struct Test *)malloc(sizeof(struct Test));
    // test->a = 'a';
    // test->b = 2;
    // addClient(clientsInStore, test);
    // printChar(clientsInStore->clients->head->data);

    struct Client *client = createClient(1000, "John Snow");
    printClient(client);
    printShoppingList(client);
    printf("\ntimeAccInStore: %f", calculateTotalTimeInStore(client));
    printf("\ntimeAccInCheckOut: %f", calculateTotalTimeInCheckOut(client));

    // for (int i = 0; i < 5; i++)
    // {
    //     printClients(clientsInStore, printInt);
    // }
    // printf("OG Clients in store: ");
    // printClients(clientsInStore);
    // struct Node *removedValue = removeClient(clientsInStore, &test[2]);
    // if (removedValue != NULL)
    // {
    //     printf("\nRemoved value: %d", *(int *)removedValue->data);
    // }
    // else
    // {
    //     printf("\nValue not found");
    // }
    // printf("\nLast Gen Clients in store: ");
    return 0;
};
