#ifndef EVENTHORIZON_H
#define EVENTHORIZON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "clients.h"
#include "genericList.h"

typedef struct Event
{
    struct Client *client;
    unsigned int type; // 0 = arrival, 1 = checkout, 2 = start checkout, 3 = end checkout and leave
    unsigned int time; // 0 to 43200 (OPEN 12 hours)
} EVENT;

int compareTimes(struct Event *data, struct Event *data2);
CLIENT *checkIfClientExists(struct List *eventHorizon, int id);
struct List *createEventHorizon(struct List *clientList);
void addSingleClient(struct List *eventHorizon, struct List *productList, struct List *clientList, int arrivalTime);
void writeLineToTxt(char line[]);
void printEvent(EVENT *event);

#endif