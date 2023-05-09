#include <stdio.h>
#include <stdlib.h>

typedef struct Checkout
{
    int numCheckout;
    struct Employee *employee;
    struct List *queue;
    CLIENT *servingClient;
    float timeWaiting;
    float timeCheckout;
} CHECKOUT;

CHECKOUT *createCheckout(int numCheckout)
{
    CHECKOUT *checkout = (CHECKOUT *)malloc(sizeof(CHECKOUT));
    checkout->numCheckout = numCheckout;
    checkout->employee = NULL;
    checkout->queue = createList();
    checkout->servingClient = NULL;
    checkout->timeWaiting = 0;
    checkout->timeCheckout = 0;
    return checkout;
}

void addToCheckoutQueue(CHECKOUT *checkout, CLIENT *data, int time)
{
    addToBackOfList(checkout->queue, data);
    checkout->timeWaiting += calculateTotalTimeInCheckOut(data);
    char sentence[100];
    sprintf(sentence, "Cliente %d entrou na caixa %d ao instante %d", data->id, checkout->numCheckout, time);
    writeLineToTxt(sentence);
}

void removeFromCheckoutQueue(CHECKOUT *checkout)
{
    checkout->timeWaiting -= calculateTotalTimeInCheckOut(checkout->queue->head->data);
    checkout->queue->head = checkout->queue->head->next;
}

void addServingClient(CHECKOUT *checkout, int time) {
    checkout->servingClient = checkout->queue->head->data;
    checkout->timeCheckout += calculateTotalTimeInCheckOut(checkout->servingClient);
    char sentence[100];
    sprintf(sentence, "Cliente %d começou a passar os produtos na caixa %d ao instante %d", checkout->servingClient->id, checkout->numCheckout, time);
    writeLineToTxt(sentence);
}

void removeServingClient(CHECKOUT *checkout, int time)
{
    char sentence[100];
    sprintf(sentence, "Cliente %d terminou de passar os produtos na caixa %d e saiu da loja ao instante %d", checkout->servingClient->id, checkout->numCheckout, time);
    writeLineToTxt(sentence);
    free(checkout->servingClient);
    checkout->servingClient = NULL;
    checkout->timeCheckout = 0;

}