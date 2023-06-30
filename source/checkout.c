#include "checkout.h"
#include "employee.h"

CHECKOUT *createCheckout(int numCheckout, struct List *employeeList)
{
    CHECKOUT *checkout = (CHECKOUT *)malloc(sizeof(CHECKOUT));
    checkout->numCheckout = numCheckout;
    checkout->employee = chooseRandomEmployee(employeeList);
    checkout->queue = createList();
    checkout->servingClient = NULL;
    checkout->closing = 0;
    return checkout;
}

void addToCheckoutQueue(CHECKOUT *checkout, CLIENT *client)
{
    addToBackOfList((struct List *)checkout->queue, client);
}

void removeFromCheckoutQueue(CHECKOUT *checkout)
{
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
}

void removeServingClient(CHECKOUT *checkout)
{
    checkout->servingClient = NULL;
}

CHECKOUT *chooseCheckout(struct List *checkoutList)
{
    struct Node *current = checkoutList->head;
    CHECKOUT *checkout = current->data;
    while (current && checkoutList->size > 1)
    {
        if (((CHECKOUT *)current->data)->queue->size < checkout->queue->size)
            if (((CHECKOUT *)current->data)->closing == 0)
                checkout = current->data;
        current = current->next;
    }
    return checkout;
}

CHECKOUT *findCheckout(struct List *checkoutList, CLIENT *client)
{
    struct Node *current = checkoutList->head;
    while (current)
    {
        struct Node *currentQ = ((CHECKOUT *)current->data)->queue->head;
        while (currentQ)
        {
            if (((CLIENT *)currentQ->data)->id == client->id)
            {
                CHECKOUT *checkout = currentQ->data;
                return checkout;
            }
            currentQ = currentQ->data;
        }
        current = current->next;
    }
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
