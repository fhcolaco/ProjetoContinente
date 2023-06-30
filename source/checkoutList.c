#include "checkoutList.h"
#include "genericList.h"
#include "CONSTANTS.h"

struct List *createCheckoutList()
{
    return createList();
}

int compareCheckout(struct List *list)
{
    struct Node *current = list->head;
    int i = 1;
    while (current)
    {
        if (((CHECKOUT *)current->data)->numCheckout == i)
        {
            current = current->next;
            i++;
        }
        else
        {
            return i;
        }
    }
    if (current == NULL)
    {
        return i;
    }
}

int checkoutInTheRightPlace(CHECKOUT *data, CHECKOUT *data2)
{
    if (data->numCheckout > data2->numCheckout)
    {
        return 1;
    }
    return 0;
}

void openCheckout(struct List *checkoutList, struct List *employeeList)
{
    int maxCheckouts = MAX_CHECKOUTS;
    if (checkoutList->size < maxCheckouts)
    {
        CHECKOUT *checkout = NULL;
        checkout = createCheckout(compareCheckout(checkoutList), employeeList);
        addToMiddle(checkoutList, checkout, *checkoutInTheRightPlace);
        char sentence[100];
        sprintf(sentence, "CHECKOUT %d OPENED", checkout->numCheckout);
        writeLineToTxt(sentence);
    }
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
    CHECKOUT *checkout = aux->data;
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
        free(aux);
        if (checkoutList->size != 0)
        {
            averageClientsPerCheckout /= checkoutList->size;
            if (averageClientsPerCheckout > 5)
            {
                openCheckout(checkoutList, employeeList);
            }
            else if (averageClientsPerCheckout < 2 && checkoutList->size > 1)
            {
                CHECKOUT *checkout = checkoutWithLeastClients(checkoutList);
                if (checkout->queue->size == 0 && checkout->servingClient == NULL)
                {
                    closeCheckout(checkoutList, checkout);
                }
                else
                {
                    checkout->closing = 1;
                }
                // CHECKOUT *checkout = checkoutList->tail->data;
                // if (checkout->queue->size == 0 && checkout->servingClient == NULL)
                // {
                //     closeCheckout(checkoutList, checkout);
                // }
                // else
                // {
                //     checkout->closing = 1;
                // }
            }
        }
    }
}

void printCheckoutList(struct List *checkoutList)
{
    int maxCheckout = MAX_CHECKOUTS;
    struct Node *current = checkoutList->head;
    int i = 1;
    while (current != NULL && i <= 25)
    {
        //     // CHECKOUT *checkout = current->data;
        //     // if (checkout->numCheckout == i)
        //     // {
        //     //     printf("\nCaixa %d [%s]: Aberta", checkout->numCheckout, checkout->employee->name);
        //     //     i++;
        //     //     current = current->next;
        //     // }
        //     // else
        //     // {
        //     //     printf("\nCaixa %d: Fechada", i);
        //     //     i++;
        //     // }

        while (((CHECKOUT *)current->data)->numCheckout != i && i <= 25)
        {
            printf("\nCaixa %d: Fechada", i);
            i++;
        }
        printf("\nCaixa %d [%s]: Aberta", i, ((CHECKOUT *)current->data)->employee->name);
        i++;
        current = current->next;
    }
    while (i <= 9)
    {
        printf("\nCaixa %d: Fechada", i);
        i++;
    }

    // while (current != NULL)
    // {
    //     printf("\nCaixa %d [%s]: Aberta", ((CHECKOUT *)current->data)->numCheckout, ((CHECKOUT *)current->data)->employee->name);
    //     current = current->next;
    // }
}

CHECKOUT *findCheckoutByNumCheckout(struct List *checkoutList, int numCheckout)
{
    struct Node *current = checkoutList->head;
    while (current)
    {
        CHECKOUT *checkout = current->data;
        if (checkout->numCheckout == numCheckout)
        {
            return checkout;
        }
        else
        {
            return NULL;
        }
        current = current->next;
    }
}