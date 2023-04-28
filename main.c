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
    // int choice;
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList();
    struct List *clientList = createClientList(productList);
    struct List *employeeList = createEmployeeList();
    struct List *eventHorizon = createEventHorizon(clientList);
    // // LOAD DATA
    printf("\n\33[0;32mData loaded successfully!\n\33[0;97m");
    printf("Exitem %d produtos na Lista.\n", productList->size);
    printf("Exitem %d clientes na Lista.\n", clientList->size);
    printf("Exitem %d empregados na Lista.\n", employeeList->size);
    printf("Exitem %d eventos na Lista.\n", eventHorizon->size);

    struct List *list2 = copyList(eventHorizon);
    struct Node *current = (struct Node *)list2->head;
    while (current != NULL)
    {
        struct Event *event = (struct Event *)current->data;
        printf("Event: %d\n", event->type);
        printf("Time: %d\n", event->time);
        printf("Client: %d\n\n", event->client->id);
        current = current->next;
        free(event);
    }
    free(current);
    free(list2);

    // show employee name and nummec
    // for (int i = 0; i < 2; i++)
    // {
    //     struct List *list2 = copyList(employeeList);
    //     printf("\n\n\tROUND %d\n\n", i + 1);
    //     for (int i = 0; i < employeeList->size; i++)
    //     {
    //         struct Employee *employee = (struct Employee *)list2->head->data;
    //         printf("Name: %s\n", employee->name);
    //         printf("NumMec: %d\n", employee->numMec);
    //         list2->head = list2->head->next;
    //     }
    //     free(list2);
    // }

    // int n;
    // for (int i = 0; i < 3; i++)
    // {
    //     struct List *list2 = copyList(clientList);
    //     printf("Qual é o cliente que pretende ver: (1-10000)\nEscolha: ");
    //     scanf("%d", &n);
    //     showClientByID(list2, n);
    //     free(list2);
    // }
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
