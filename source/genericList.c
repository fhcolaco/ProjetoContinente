#include "genericList.h"

struct List *createList()
{
    struct List *list = (struct List *)malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void addToMiddle(struct List *list, void *data, int (*compare)(void *, void *))
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    int i = 0;
    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else if (compare(list->head->data, data) == 1)
    {
        new_node->next = list->head;
        new_node->next->previous = new_node;
        list->head = new_node;
    }
    else
    {
        struct Node *current = list->head;
        while (current->next && compare(current->next->data, data) == 0)
        {
            current = current->next;
            i++;
        }
        new_node->next = current->next;
        if (current->next)
        {
            new_node->next->previous = new_node;
        }
        if (current == list->tail)
            list->tail = new_node;
        current->next = new_node;
        new_node->previous = current;
    }
    list->size++;
}

void addToBackOfList(struct List *list, void *data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        new_node->previous = list->tail;
        list->tail = new_node;
    }
    list->size++;
}

struct Node *findMiddle(struct Node *start, struct Node *end)
{
    if (start == NULL)
        return NULL;
    struct Node *slow = start;
    struct Node *fast = start->next;
    while (fast && fast != end)
    {
        fast = fast->next;
        if (fast != end)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}

struct Node *findInListBinarySearch(struct List *list, void *data)
{
    struct Node *start = list->head;
    struct Node *end = list->tail;
    do
    {
        struct Node *middle = findMiddle(start, end);
        if (middle == NULL)
            return NULL;
        if (middle->data == data)
            return middle;
        else if (middle->data > data)
            end = middle;
        else
            start = middle;
    } while (end != start);
    return NULL;
}

struct Node *removeFromList(struct List *list, void *data, int (*compare)(void *, void *))
{
    struct Node *previous = list->head;
    while (previous->next && compare(previous->next->data, data) == 0)
    {
        previous = previous->next;
    }
    if (previous)
    {
        struct Node *found = previous->next;
        previous->next = found->next;
        list->size--;
        return found;
    }
    else
    {
        printf("Element not found\n");
        return NULL;
    }
}

struct List *copyList(struct List *list)
{
    struct List *list2 = createList();
    struct Node *current = list->head;
    while (current != NULL)
    {
        addToBackOfList(list2, current->data);
        current = current->next;
    }
    return list2;
}

void destroyList(struct List *list)
{
    struct Node *current = list->head;
    while (current != NULL)
    {
        struct Node *aux = current;
        current = current->next;
        free(aux);
    }
    free(list);
}

void nextNode(struct List *list)
{
    struct Node *aux = list->head;
    list->head = list->head->next;
    list->size--;
    free(aux);
}
