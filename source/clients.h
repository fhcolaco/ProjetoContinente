#ifndef CLIENTS_H
#define CLIENTS_H

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

PRODUCT *createProduct(int id, char *description, float price, float timeInStore, float timeInCheckOut);
void *generateRandomProductList(struct Client *client, struct List *productList);
void createShoppingList(struct Client *client, struct List *productList);
struct List *deleteClient(struct List *clientList, CLIENT *client);
struct List *createProductList();
struct List *createClientList(struct List *productList);
void printProduct(PRODUCT *product);
void printClient(struct Client *client);
void printShoppingList(struct Client *client);
float calculateTotalTimeInStore(struct Client *client);
float calculateTotalTimeInCheckOut(struct Client *client);

#endif