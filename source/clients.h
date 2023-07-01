#ifndef CLIENTS_H
#define CLIENTS_H

#include "genericList.h"

typedef struct Client
{
    int id;
    char name[50];
    struct List *shoppingList;
    int inStore;
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
struct List *createProductList(int performanceMode);
void changeShoppingList(struct Client *client, struct List *productList);
float calculateTotalPrice(struct Client *client);
struct List *createClientList(struct List *productList, int performanceMode);
void printProduct(PRODUCT *product);
int checkIfClientIsInStore(CLIENT *client);
void printClient(struct Client *client);
void printShoppingList(struct Client *client);
float calculateTotalTimeInStore(struct Client *client);
float calculateTotalTimeInCheckOut(struct Client *client);

#endif