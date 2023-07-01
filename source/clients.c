#include "clients.h"

int *compareClients(void *data, void *data2)
{
    CLIENT *client = data;
    CLIENT *client2 = data2;
    if (client->id > client2->id)
    {
        return 1;
    }
    return 0;
}

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
    unsigned int numberOfProducts = rand() % MAX_PRODUCTS_PER_CLIENT;
    unsigned int random;
    for (int i = 0; i < numberOfProducts + 3; i++)
    {
        random = rand() % productList->size;
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

void changeShoppingList(struct Client *client, struct List *productList)
{
    free(client->shoppingList);
    createShoppingList(client, productList);
}

CLIENT *createClient(int id, char *name, struct List *productList)
{
    CLIENT *client = (struct Client *)malloc(sizeof(struct Client));
    client->id = id;
    client->inStore = 0;
    strcpy(client->name, name);
    createShoppingList(client, productList);
    return client;
}

struct List *deleteClient(struct List *clientList, CLIENT *client)
{
    struct List *newList = createList();
    struct Node *current = clientList->head;
    for (int i = 0; i < clientList->size; i++)
    {
        if (((CLIENT *)current->data)->id != client->id)
        {
            addToBackOfList(newList, current->data);
        }
        current = current->next;
    }
    clientList = copyList(newList);
    free(client->shoppingList);
    free(client);
    return clientList;
};

struct List *createProductList(int performanceMode)
{
    struct List *ListaProdutos = createList();
    FILE *products = fopen("produtosOriginal.txt", "r");
    if (products == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {
        printf("Creating product list...\n");
        char ch = 0;
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
            if (performanceMode != 1)
                printf("\33[0;32mProduct list created: %d%%\r\33[0;97m", (int)(((TOTAL_PRODUCTS) - ((TOTAL_PRODUCTS)-ListaProdutos->size)) * 100 / TOTAL_PRODUCTS) + 1);
        }
    }
    printf("\33[0;32mProduct list created!                        \n\33[0;97m");
    fclose(products);
    return ListaProdutos;
}
struct List *createClientList(struct List *productList, int performanceMode)
{
    if (productList->head == NULL)
    {
        productList = createProductList(performanceMode);
    }
    struct List *clientList = createList();
    FILE *clients = fopen("clientesOriginal.txt", "r");
    if (clients == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    else
    {
        printf("Creating client list...\n");
        char ch = 0;
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
            addToMiddle(clientList, createClient(id, name, productList), *compareClients);
            if (performanceMode != 1)
                printf("\33[0;32mClient list created: %d%%\r\33[0;97m", (int)((TOTAL_CLIENTS - (TOTAL_CLIENTS - clientList->size)) * 100 / TOTAL_CLIENTS) + 1);
        }
    }
    printf("\33[0;32mClient list created!                        \n\33[0;97m");
    fclose(clients);
    return clientList;
}

void printProduct(PRODUCT *product)
{
    printf("%d\t%s\t%.2f\t%.2f\t%.2f\n", product->id, product->description, product->price, product->timeInStore, product->timeInCheckOut);
}

void printClient(struct Client *client)
{
    printf("Cliente %d: %s\n", client->id, client->name);
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

int checkIfClientIsInStore(CLIENT *client)
{
    return client->inStore;
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
        totalTime += ((PRODUCT *)current->data)->timeInCheckOut;
        current = current->next;
    }
    return totalTime;
}

float calculateTotalPrice(struct Client *client)
{
    float totalPrice = 0;
    struct Node *current = client->shoppingList->head;
    if (current == NULL)
    {
        return -1;
    }
    while (current != NULL)
    {
        totalPrice += ((PRODUCT *)current->data)->price;
        current = current->next;
    }
    return totalPrice;
}

int checkIfClientExistsInClientList(struct List *clientList, int id)
{
    struct Node *current = clientList->head;
    while (current)
    {
        if (((CLIENT *)current->data)->id == id)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}