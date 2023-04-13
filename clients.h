#include "genericList.h"
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS_PER_CLIENT 9;
#define MAX_PRODUCTS_IN_FILE 9662;

typedef struct Client
{
    int id;
    char name[50];
    struct List *shoppingList;
} CLIENT;

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

void *generateRandomProductList(struct Client *client, struct List *productList)
{
    char ch;
    srand(time(0));
    unsigned int numberOfProducts = rand() % MAX_PRODUCTS_PER_CLIENT;
    int id;
    char description[100];
    float price;
    float timeInStore;
    float timeInCheckOut;
    unsigned int random;
    for (int i = 0; i < numberOfProducts + 1; i++)
    {
        random = rand() % MAX_PRODUCTS_IN_FILE;
        struct Node *current = productList->head;
        for (int j = 0; j < random; j++)
        {
            current = current->next;
        }
        addToBackOfList(client->shoppingList, current->data);
    }
}

void createShoppingList(struct Client *client, struct List *productList)
{
    client->shoppingList = createList();
    generateRandomProductList(client, productList);
}
CLIENT *createClient(int id, char *name, struct List *productList)
{
    struct Client *client = (struct Client *)malloc(sizeof(struct Client));
    client->id = id;
    strcpy(client->name, name);
    createShoppingList(client, productList);
    return client;
}

struct List *createProductList()
{
    struct List *ListaProdutos = createList();
    FILE *products;
    products = fopen("produtosOriginal.txt", "r");
    if (products == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    else
    {
        printf("Creating product list...\n");
        char ch;
        int id;
        char description[100];
        float price;
        float timeInStore;
        float timeInCheckOut;
        int estaMerdaNaoFazSentido = 0;
        while (ch != EOF)
        {
            description[0] = 0;
            ch = '\0';
            for (int i = 0; i < 5; i++)
            {
                char aux[100] = "\0";
                ch = fgetc(products);
                while (ch != '\t' && ch != '\n' && ch != EOF)
                {
                    strncat(aux, &ch, 1);
                    ch = fgetc(products);
                }
                if (i == 0)
                {
                    id = atoi(aux);
                }
                if (i == 1)
                {
                    strcpy(description, aux);
                }
                if (i == 2)
                {
                    price = atof(aux);
                }
                if (i == 3)
                {
                    timeInStore = atof(aux);
                }
                if (i == 4)
                {
                    timeInCheckOut = atof(aux);
                }
            }
            addToBackOfList(ListaProdutos, createProduct(id, description, price, timeInStore, timeInCheckOut));
        }
    }
    printf("Product list created!\n");
    fclose(products);
    return ListaProdutos;
}
struct List *createClientList(struct List *productList)
{
    struct List *clientList = createList();
    FILE *clients;
    clients = fopen("clientesOriginal.txt", "r");
    if (clients == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    else
    {
        printf("Creating client list...\n");
        char ch;
        int id;
        char name[50];
        int estaMerdaNaoEstaAFAzerNada = 0;
        while (ch != EOF)
        {
            name[0] = 0;
            ch = '\0';
            for (int i = 0; i < 2; i++)
            {
                char aux[50] = "\0";
                ch = fgetc(clients);
                while (ch != '\t' && ch != '\n' && ch != EOF)
                {
                    strncat(aux, &ch, 1);
                    ch = fgetc(clients);
                }
                if (i == 0)
                {
                    id = atoi(aux);
                }
                if (i == 1)
                {
                    strcpy(name, aux);
                }
            }
            addToBackOfList(clientList, createClient(id, name, productList));
        }
    }
    printf("Client list created!\n");
    fclose(clients);
    return clientList;
}

void printProduct(PRODUCT *product)
{
    printf("%d\t%s\t%.2f\t%.2f\t%.2f\n", product->id, product->description, product->price, product->timeInStore, product->timeInCheckOut);
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