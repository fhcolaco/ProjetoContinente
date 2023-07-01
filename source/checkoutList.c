#include "checkoutList.h"

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

int checkoutInTheRightPlace(void *data, void *data2)
{
    CHECKOUT *checkout = data;
    CHECKOUT *checkout2 = data2;
    if (checkout->numCheckout > checkout2->numCheckout)
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
    else
    {
        printf("Maximum number of checkouts reached\n");
    }
}

int closeCheckout(struct List *checkoutList, struct Checkout *checkout)
{
    if (checkout->closing == 0)
    {
        checkout->closing = 1;
        return 1;
    }
    else
    {
        if (checkout->queue->size > 0 || checkout->servingClient != NULL)
            return 2;
        struct Node *current = checkoutList->head;
        struct Node *previous = NULL;
        ((EMPLOYEE *)checkout->employee)->isWorking = false;
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
        char sentence[100];
        sprintf(sentence, "CHECKOUT %d CLOSED", checkout->numCheckout);
        writeLineToTxt(sentence);
        checkoutList->size--;
        return 0;
    }
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
        struct Node *aux = checkoutList->head;
        while (aux && checkoutList->size > 1)
        {
            if (((CHECKOUT *)aux->data)->closing == 1)
            {
                if (((CHECKOUT *)aux->data)->queue->size == 0 && ((CHECKOUT *)aux->data)->servingClient == NULL)
                {
                    closeCheckout(checkoutList, aux->data);
                    free(aux->data);
                }
            }
            aux = aux->next;
        }
        int averageClientsPerCheckout = 0;
        aux = checkoutList->head;
        for (int i = 0; i < checkoutList->size; i++)
        {
            averageClientsPerCheckout += ((CHECKOUT *)aux->data)->queue->size;
            aux = aux->next;
        }
        if (checkoutList->size != 0)
        {
            averageClientsPerCheckout /= checkoutList->size;
            if (averageClientsPerCheckout > 5 && checkoutList->size < MAX_CHECKOUTS)
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
        current = current->next;
    }
    return NULL;
}
