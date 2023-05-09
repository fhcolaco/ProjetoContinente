struct List *createCheckoutList(){
    return createList();
}

void openCheckout(struct List *checkoutList, struct Checkout *checkout){
    addToBackOfList(checkoutList, checkout);
}

void closeCheckout(struct List *checkoutList, struct Checkout *checkout){
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
    else
    {
        previous->next = current->next;
    }
    checkoutList->size--;
}