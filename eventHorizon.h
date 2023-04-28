#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Event
{
    struct Client *client;
    unsigned int type; // 0 = arrival, 1 = checkout, 2 = pay, 3 = leave
    unsigned int time; // 0 to 43200 (OPEN 12 hours)
};

int compareTimes(struct Event *data, struct Event *data2)
{
    if (data->time > data2->time)
    {
        return 1;
    }
    return 0;
}

struct List *createEventHorizon(struct List *clientList)
{
    printf("Creating event horizon...\n");
    struct List *eventHorizon = createList();
    struct Node *current = (struct Node *)clientList->head;
    srand(time(0));
    unsigned int t;
    while (current != NULL)
    // for (int t = clientList->size; t != 0; t--)
    {
        t = rand() % 43200;
        printf("Client %d arrived at %d\n", ((struct Client *)current->data)->id, t);
        struct Event *event = malloc(sizeof(struct Event));
        event->client = current->data;
        event->type = 0;
        event->time = t;
        addToMiddle(eventHorizon, event, *compareTimes);
        current = current->next;
    }
    printf("\33[0;32mEvent horizon created.\n\33[0;97m");
    return eventHorizon;
}