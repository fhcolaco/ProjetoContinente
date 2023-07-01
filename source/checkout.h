#ifndef CHECKOUT_H
#define CHECKOUT_H

#include "clients.h"
#include "employee.h"

typedef struct Checkout
{
    int numCheckout;
    EMPLOYEE *employee;
    struct List *queue;
    CLIENT *servingClient;
    int closing;
} CHECKOUT;

CHECKOUT *createCheckout(int numCheckout, struct List *employeeList);
void addToCheckoutQueue(CHECKOUT *checkout, CLIENT *client);
void removeFromCheckoutQueue(CHECKOUT *checkout);
int addServingClient(CHECKOUT *checkout);
void removeServingClient(CHECKOUT *checkout);
CHECKOUT *chooseCheckout(struct List *checkoutList, CLIENT *client);
CHECKOUT *findCheckout(struct List *checkoutList, CLIENT *client);
CHECKOUT *findServingClient(struct List *checkoutList, CLIENT *client);
CHECKOUT *findIfServingClient(struct List *checkoutList, CLIENT *client);
#endif