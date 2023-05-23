#include "checkoutList.h"
#include "genericList.h"

struct List *createCheckoutList()
{
    return createList();
}

void openCheckout(struct List *checkoutList, struct List *employeeList)
{
    struct Checkout *checkout = createCheckout(checkoutList->size + 1, employeeList);
    addToBackOfList(checkoutList, checkout);
    char sentence[100];
    sprintf(sentence, "CHECKOUT %d OPENED", checkout->numCheckout);
    writeLineToTxt(sentence);
}

void closeCheckout(struct List *checkoutList, struct Checkout *checkout)
{
    struct Node *current = checkoutList->head;
    struct Node *previous = NULL;
    while (current != NULL && current->data != checkout)
    {
        previous = current;
        current = current->next;
    }
    if (previous == NULL)
    {
        checkoutList->head = current->next;
    }
    else if (current == checkoutList->tail)
    {
        checkoutList->tail = previous;
        previous->next = NULL;
    }
    else
    {
        previous->next = current->next;
    }
    checkoutList->size--;
    char sentence[100];
    sprintf(sentence, "CHECKOUT %d CLOSED", checkout->numCheckout);
    writeLineToTxt(sentence);
}

CHECKOUT *checkoutWithLeastClients(struct List *checkoutList)
{
    struct Node *aux = checkoutList->head;
    CHECKOUT *checkout = (CHECKOUT *)aux->data;
    for (int i = 0; i < checkoutList->size; i++)
    {
        if (((CHECKOUT *)aux->data)->queue->size < checkout->queue->size)
        {
            checkout = (CHECKOUT *)aux->data;
        }
        aux = aux->next;
    }
    return checkout;
}

void checkStatusOfCheckouts(struct List *checkoutList, struct List *employeeList)
{
    if (checkoutList->size == 0)
    {
        // there are no checkouts open
        openCheckout(checkoutList, employeeList);
    }
    else
    {
        for (int i = 0; i < checkoutList->size; i++)
        {
            struct Node *aux = checkoutList->head;
            if (((CHECKOUT *)aux->data)->closing == 1)
            {
                if (((CHECKOUT *)aux->data)->queue->size == 0 && ((CHECKOUT *)aux->data)->servingClient == NULL)
                {
                    closeCheckout(checkoutList, aux->data);
                    free(aux->data);
                }
            }
        }
        int averageClientsPerCheckout = 0;
        struct List *aux = copyList(checkoutList);
        for (int i = 0; i < checkoutList->size; i++)
        {
            averageClientsPerCheckout += ((CHECKOUT *)aux->head->data)->queue->size;
            nextNode(aux);
        }
        averageClientsPerCheckout /= checkoutList->size;
        free(aux);
        if (averageClientsPerCheckout > 5)
        {
            openCheckout(checkoutList, employeeList);
        }
        else if (averageClientsPerCheckout < 2 && checkoutList->size > 1)
        {
            // CHECKOUT *checkout = checkoutWithLeastClients(checkoutList);
            // if (checkout->queue->size == 0 && checkout->servingClient == NULL)
            // {
            //     closeCheckout(checkoutList, checkout);
            // }
            // else
            // {
            //     checkout->closing = 1;
            // }
            CHECKOUT *checkout = checkoutList->tail->data;
            if (checkout->queue->size == 0 && checkout->servingClient == NULL)
            {
                closeCheckout(checkoutList, checkout);
            }
            else
            {
                checkout->closing = 1;
            }
        }
    }
}
