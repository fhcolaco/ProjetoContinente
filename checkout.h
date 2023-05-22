#include <stdio.h>
#include <stdlib.h>

typedef struct Checkout
{
    int numCheckout;
    struct Employee *employee;
    struct List *queue;
    CLIENT *servingClient;
    float timeWaiting;
    int closing;
} CHECKOUT;

CHECKOUT *createCheckout(int numCheckout)
{
    CHECKOUT *checkout = (CHECKOUT *)malloc(sizeof(CHECKOUT));
    checkout->numCheckout = numCheckout;
    checkout->employee = NULL;
    checkout->queue = createList();
    checkout->servingClient = NULL;
    checkout->timeWaiting = 0;
    checkout->closing = 0;
    return checkout;
}

void addToCheckoutQueue(CHECKOUT *checkout, CLIENT *client)
{
    addToBackOfList((struct List *)checkout->queue, client);
}

void removeFromCheckoutQueue(CHECKOUT *checkout)
{
    checkout->timeWaiting -= calculateTotalTimeInCheckOut(checkout->queue->head->data);
    checkout->queue->head = checkout->queue->head->next;
    checkout->queue->size--;
    if (checkout->queue->size == 0)
    {
        checkout->queue->tail = NULL;
    }
}

void addServingClient(CHECKOUT *checkout)
{
    if (checkout->servingClient == NULL)
    {
        checkout->servingClient = (CLIENT *)checkout->queue->head->data;
    }
    else
    {
        exit(1);
    }
    checkout->timeWaiting += calculateTotalTimeInCheckOut(checkout->servingClient);
}

void removeServingClient(CHECKOUT *checkout)
{
    checkout->timeWaiting -= calculateTotalTimeInCheckOut(checkout->servingClient);
    checkout->servingClient = NULL;
}

CHECKOUT *chooseCheckout(struct List *checkoutList)
{
    struct List *aux = copyList(checkoutList);
    CHECKOUT *checkout = aux->head->data;
    while (aux->head != NULL)
    {
        if (((CHECKOUT *)aux->head->data)->queue->size < checkout->queue->size && ((CHECKOUT *)aux->head->data)->closing == 0)
        {
            checkout = aux->head->data;
        }
        nextNode(aux);
    }
    free(aux);
    return checkout;
}

CHECKOUT *findCheckout(struct List *checkoutList, CLIENT *client)
{
    struct List *aux = copyList(checkoutList);
    for (int i = 0; i < aux->size; i++)
    {
        struct List *aux2 = copyList(((CHECKOUT *)aux->head->data)->queue);
        for (int j = 0; j < aux2->size; j++)
        {
            if (((CLIENT *)aux2->head->data)->id == client->id)
            {
                CHECKOUT *checkout = aux->head->data;
                free(aux2);
                free(aux);
                return checkout;
            }
            aux2->head = aux2->head->next;
        }
        free(aux2);
        aux->head = aux->head->next;
    }
    free(aux);
    return NULL;
}

CHECKOUT *findServingClient(struct List *checkoutList, CLIENT *client)
{
    struct List *aux = copyList(checkoutList);
    for (int i = 0; i < aux->size; i++)
    {
        if (((CHECKOUT *)aux->head->data)->servingClient != NULL && ((CHECKOUT *)aux->head->data)->servingClient->id == client->id)
        {
            CHECKOUT *checkout = aux->head->data;
            free(aux);
            return checkout;
        }
        aux->head = aux->head->next;
    }
    free(aux);
    return NULL;
}
