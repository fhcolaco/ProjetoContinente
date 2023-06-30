#ifndef CHECKOUTLIST_H
#define CHECKOUTLIST_H

#include "checkout.h"

struct List *createCheckoutList();
int compareCheckout(struct List *list);
void openCheckout(struct List *checkoutList, struct List *employeeList);
void closeCheckout(struct List *checkoutList, struct Checkout *checkout);
CHECKOUT *checkoutWithLeastClients(struct List *checkoutList);
void checkStatusOfCheckouts(struct List *checkoutList, struct List *employeeList);
void printCheckoutList(struct List *checkoutList);
CHECKOUT *findCheckoutByNumCheckout(struct List *checkoutList, int numCheckout);

#endif