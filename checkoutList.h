struct List *createCheckoutList()
{
    return createList();
}

void openCheckout(struct List *checkoutList)
{
    struct Checkout *checkout = createCheckout(checkoutList->size + 1);
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

void checkStatusOfCheckouts(struct List *checkoutList)
{
    if (checkoutList->tail != NULL && ((CHECKOUT *)checkoutList->tail->data)->closing == 1)
    {
        CHECKOUT *checkout = checkoutList->tail->data;
        if (checkout->queue->size == 0 && checkout->servingClient == NULL)
        {
            // there are no clients in the queue and the checkout is not serving a client, so it can be closed
            closeCheckout(checkoutList, checkout);
            free(checkout);
        }
    }
    if (checkoutList->size == 0)
    {
        // there are no checkouts open
        openCheckout(checkoutList);
    }
    else
    {
        int averageClientsPerCheckout = 0;
        struct List *aux = copyList(checkoutList);
        for (int i = 0; i < checkoutList->size; i++)
        {
            averageClientsPerCheckout += ((struct Checkout *)aux->head->data)->queue->size;
            nextNode(aux);
        }
        averageClientsPerCheckout /= checkoutList->size;
        free(aux);
        if (averageClientsPerCheckout > 5)
        {
            openCheckout(checkoutList);
        }
        else if (averageClientsPerCheckout < 2 && checkoutList->size > 1)
        {
            if (((CHECKOUT *)checkoutList->tail->data)->queue->size == 0 && ((CHECKOUT *)checkoutList->tail->data)->servingClient == NULL)
            {
                closeCheckout(checkoutList, checkoutList->tail->data);
            }
            else if (((CHECKOUT *)checkoutList->tail->data)->closing == 0)
            {
                ((CHECKOUT *)checkoutList->tail->data)->closing = 1;
            }
        }
    }
}