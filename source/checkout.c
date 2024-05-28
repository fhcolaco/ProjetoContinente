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
    addToBackOfList(checkout->queue, client);
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
        printf("Error: Checkout already has a serving client.\n");
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
        {

            if (((CHECKOUT *)current->data)->closing == 0)
                checkout = current->data;
        }
        current = current->next;
    }
    return checkout;
}

CHECKOUT *findCheckout(struct List *checkoutList, CLIENT *client)
{
    struct Node *current = checkoutList->head;
    while (current)
    {
        struct Node *currentQueue = ((struct List *)((CHECKOUT *)current->data)->queue)->head;
        while (currentQueue)
        {
            if (((CLIENT *)currentQueue->data)->id == client->id)
            {
                CHECKOUT *checkout = current->data;
                return checkout;
            }
            currentQueue = currentQueue->next;
        }
        current = current->next;
    }
    return NULL;
}

CHECKOUT *findServingClient(struct List *checkoutList, CLIENT *client)
{
    struct Node *current = checkoutList->head;
    while (current)
    {
        if (((CHECKOUT *)current->data)->servingClient != NULL)
        {
            if (((CHECKOUT *)current->data)->servingClient->id == client->id)
            {
                CHECKOUT *checkout = current->data;
                return checkout;
            }
        }
        current = current->next;
    }
    current = checkoutList->head;
    while (current)
    {
        current = current->next;
    }
    return NULL;
}

CHECKOUT *findIfServingClient(struct List *checkoutList, CLIENT *client)
{
    struct Node *current = checkoutList->head->next;
    while (current)
    {
        if (((CHECKOUT *)current->data)->servingClient != NULL)
        {
            if (((CHECKOUT *)current->data)->servingClient->id == client->id)
            {
                CHECKOUT *checkout = current->data;
                return checkout;
            }
        }
        current = current->next;
    }
    return NULL;
}
