#include "genericList.h"
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS_PER_CLIENT 9;
#define MAX_PRODUCTS_IN_FILE 9662;

struct Client
{
    int id;
    char name[50];
    struct List *shoppingList;
};

typedef struct product
{
    int id;
    char description[100];
    float price;
    float timeInStore;
    float timeInCheckOut;
} PRODUCT;

PRODUCT *createProduct(int id, char *description, float price, float timeInStore, float timeInCheckOut)
{
    PRODUCT *product = (PRODUCT *)malloc(sizeof(PRODUCT));
    product->id = id;
    strcpy(product->description, description);
    product->price = price;
    product->timeInStore = timeInStore;
    product->timeInCheckOut = timeInCheckOut;
    return product;
}
void *generateRandomProductList(struct Client *client)
{
    char ch;
    srand(time(0));
    unsigned int numberOfProducts = rand() % MAX_PRODUCTS_PER_CLIENT;
    printf("Number of products: %d\n", numberOfProducts + 1);
    int id;
    char description[100];
    float price;
    float timeInStore;
    float timeInCheckOut;
    unsigned int random;
    for (int z = 1; z <= numberOfProducts + 1; z++)
    {
        id = 0;
        description[0] = 0;
        price = 0;
        timeInStore = 0;
        timeInCheckOut = 0;
        random = rand() % MAX_PRODUCTS_IN_FILE;
        printf("Random number: %d\n", random);
        FILE *products;
        products = fopen("produtosOriginal.txt", "r");
        if (products == NULL)
        {
            printf("Error opening file");
            exit(1);
        }
        else
        {
            ch = '\0';
            for (int j = 0; j < random - 1; j++) // Choosing a random product
            {
                ch = fgetc(products);
                while (ch != '\n')
                {
                    ch = fgetc(products);
                }
            }
            for (int i = 0; i < 5; i++)
            {
                char aux[50] = "\0";
                ch = fgetc(products);
                while (ch != '\t')
                {
                    strncat(aux, &ch, 1);
                    ch = fgetc(products);
                }
                if (i == 0)
                {
                    id = atoi(aux);
                }
                else if (i == 1)
                {
                    strcpy(description, aux);
                }
                else if (i == 2)
                {
                    price = atof(aux);
                }
                else if (i == 3)
                {
                    timeInStore = atof(aux);
                }
                else if (i == 4)
                {
                    timeInCheckOut = atof(aux);
                }
            }
            PRODUCT *product = createProduct(id, description, price, timeInStore, timeInCheckOut);
            if (addToBackOfList(client->shoppingList, product) != 1)
            {
                printf("Error adding product to list");
            }
        }
        fclose(products);
    }
}

void createShoppingList(struct Client *client)
{
    client->shoppingList = createList();
    generateRandomProductList(client);
}

struct Client *createClient(int id, char *name)
{
    struct Client *client = (struct Client *)malloc(sizeof(struct Client));
    client->id = id;
    strcpy(client->name, name);
    createShoppingList(client);
    return client;
}

void printClient(struct Client *client)
{
    printf("Client %d: %s\n", client->id, client->name);
}

void printShoppingList(struct Client *client)
{
    printf("Shopping list:\n");
    printf("\tID\tDescription\tPrice\tTime in store\tTime in checkout\n");
    struct Node *current = client->shoppingList->head;
    while (current != NULL)
    {
        printf("\t%d\t%s\t%f\t%f\t%f\n", ((PRODUCT *)current->data)->id, ((PRODUCT *)current->data)->description, ((PRODUCT *)current->data)->price, ((PRODUCT *)current->data)->timeInStore, ((PRODUCT *)current->data)->timeInCheckOut);
        current = current->next;
    }
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
        totalTime += ((PRODUCT *)current->data)->timeInStore;
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
        totalTime = ((PRODUCT *)current->data)->timeInCheckOut;
        current = current->next;
    }
    return totalTime;
}