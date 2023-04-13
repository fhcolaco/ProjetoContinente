#include "clients.h"

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
    // int choice;
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList();
    struct List *clientList = createClientList(productList);
    // // LOAD DATA
    printf("Data loaded successfully!\n");
    printf("Exitem %d produtos na Lista.\n", productList->size);
    printf("Exitem %d clientes na Lista.\n", clientList->size);
    int n;
    for (int i = 0; i < 3; i++)
    {
        struct List *list2 = copyList(clientList);
        printf("Qual é o cliente que pretende ver: (1-10000)\nEscolha: ");
        scanf("%d", &n);
        showClientByID(list2, n);
        free(list2);
    }
    // printf("A mostrar um cliente aleatorio:\n");
    // int random = rand() % clientList->size;
    // for (int i = 0; i < random; i++)
    // {
    //     clientList->head = clientList->head->next;
    // }
    // struct Client *client = (struct Client *)clientList->head->data;
    // printClient(client);
    // printShoppingList(client);
    // // struct Client *client = createClient(1000, "Joao");

    // do
    // {
    //     printf("==========MENU==========\n");
    //     printf("1. Start simulation\n");
    //     printf("2. Print averages\n");
    //     printf("3. Show data\n");
    //     printf("4. Exit\n");
    //     printf("========================\n");
    //     printf("Enter your choice: ");
    //     scanf("%d", &choice);
    //     switch (choice)
    //     {
    //     case 1:
    //         printf("Starting simulation...\n");
    //         break;
    //     case 2:
    //         printf("Printing averages...\n");
    //         break;
    //     case 3:
    // printf("Showing data...\n");

    // printClient(client);
    // printShoppingList(client);
    // printf("\ntimeAccInStore: %f\n", calculateTotalTimeInStore(client));
    // printf("timeAccInCheckOut: %f\n", calculateTotalTimeInCheckOut(client));

    //         break;
    //     case 4:
    //         printf("Exiting program...\n");
    //         break;
    //     default:
    //         printf("Invalid choice. Please try again.\n");
    //         break;
    //     }
    // } while (choice != 4);

    // struct clientsInStore *clientsInStore = createClientsInStore();
    // struct Test *test = (struct Test *)malloc(sizeof(struct Test));
    // test->a = 'a';
    // test->b = 2;
    // addClient(clientsInStore, test);
    // printChar(clientsInStore->clients->head->data);

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
