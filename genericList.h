#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    struct Node *next;
};

struct List
{
    struct Node *head;
    struct Node *tail;
    int size;
};

struct List *createList()
{
    struct List *list = (struct List *)malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int addToBackOfList(struct List *list, void *data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 1;
}

struct Node *findMiddle(struct Node *start, struct Node *end)
{
    if (start == NULL)
        return NULL;
    struct Node *slow = start;
    struct Node *fast = start->next;
    while (fast != end)
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

struct Node *findInList(struct List *list, void *data)
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
            end = middle->next;
        else
            start = middle->next;
    } while (end != start);
    return NULL;
}

struct Node *removeFromList(struct List *list, void *data)
{
    struct Node *found = findInList(list, data);
    if (found != NULL)
    {
        struct Node *current = list->head;
        while (current->next != found)
        {
            current = current->next;
        }
        current->next = found->next;
        list->size--;
        return found;
    }
    return NULL;
}