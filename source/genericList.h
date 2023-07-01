#ifndef GENERICLIST_H
#define GENERICLIST_H

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_PRODUCTS 9662
#define TOTAL_CLIENTS 10000
#define MAX_PRODUCTS_PER_CLIENT 9
#define MAX_CHECKOUTS 9

struct Node
{
    void *data;
    struct Node *next;
    struct Node *previous;
};

struct List
{
    struct Node *head;
    struct Node *tail;
    int size;
};

struct List *createList();
void addToMiddle(struct List *list, void *data, int (*compare)(void *, void *));
void addToBackOfList(struct List *list, void *data);
struct Node *findMiddle(struct Node *start, struct Node *end);
struct Node *findInListBinarySearch(struct List *list, void *data);
struct Node *removeFromList(struct List *list, void *data, int (*compare)(void *, void *));
struct List *copyList(struct List *list);
void destroyList(struct List *list);
void nextNode(struct List *list);

#endif