#include "genericList.h"
#include <string.h>

struct Client
{
    int id;
    char name[50];
    struct List *shoppingList;
};

struct Product
{
    int id;
    char description[50];
    float price;
    float timeInStore;
    float timeInCheckOut;
};

struct Product *createProduct(int id, char *description, float price, float timeInStore, float timeInCheckOut)
{
    struct Product *product = (struct Product *)malloc(sizeof(struct Product));
    product->id = id;
    strcpy(product->description, description);
    product->price = price;
    product->timeInStore = timeInStore;
    product->timeInCheckOut = timeInCheckOut;
    return product;
}
struct Product *generateRandomProduct()
{
    FILE *products;
    products = fopen("produtosOriginal.txt", "r");
    if (products == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    else
    {
        char ch;
        while (!feof(products))
        {
            int id;
            char description[50];
            float price;
            float timeInStore;
            float timeInCheckOut;
            ch = fgetc(products);
            fscanf(products, "%d %s %f %f %f", &id, description, &price, &timeInStore, &timeInCheckOut);
            struct Product *product = createProduct(id, description, price, timeInStore, timeInCheckOut);
            return product;
        }
    }
}

void createShoppingList(struct Client *client)
{
    client->shoppingList = createList();
    // addToBackOfList(client->shoppingList, generateRandomProduct());
    // addToBackOfList(client->shoppingList, generateRandomProduct());
    addToBackOfList(client->shoppingList, createProduct(1, "Apple", 1.5, 0.5, 0.5));
    addToBackOfList(client->shoppingList, createProduct(2, "Banana", 1.5, 0.5, 0.5));
    addToBackOfList(client->shoppingList, createProduct(3, "Orange", 1.5, 0.5, 0.5));
}

struct Client *createClient(int id, char *name)
{
    struct Client *client = (struct Client *)malloc(sizeof(struct Client));
    client->id = id;
    strcpy(client->name, name);
    createShoppingList(client);
    return client;
}

void printShoppingList(struct Client *client)
{
    printf("Shopping list:\n");
    printf("\tID\tDescription\tPrice\tTime in store\tTime in checkout\n");
    struct Node *current = client->shoppingList->head;
    while (current != NULL)
    {
        printf("\t%d\t%s\t\t%f\t%f\t%f\n", ((struct Product *)current->data)->id, ((struct Product *)current->data)->description, ((struct Product *)current->data)->price, ((struct Product *)current->data)->timeInStore, ((struct Product *)current->data)->timeInCheckOut);
        current = current->next;
    }
}
void printClient(struct Client *client)
{
    printf("Client %d: %s\n", client->id, client->name);
}

float calculateTotalTimeInStore(struct Client *client)
{
    float totalTime = 0;
    struct Node *current = client->shoppingList->head;
    if (current == NULL)
    {
        return -1;
    }
    while (current != NULL)
    {
        totalTime += ((struct Product *)current->data)->timeInStore;
        current = current->next;
    }
    return totalTime;
}

float calculateTotalTimeInCheckOut(struct Client *client)
{
    float totalTime = 0;
    struct Node *current = client->shoppingList->head;
    if (current == NULL)
    {
        return -1;
    }
    while (current != NULL)
    {
        totalTime = ((struct Product *)current->data)->timeInCheckOut;
        current = current->next;
    }
    return totalTime;
}