#include "eventHorizon.h"

int compareTimes(void *data, void *data2)
{
    struct Event *event = data;
    struct Event *event2 = data2;
    if (event->time >= event2->time)
    {
        return 1;
    }
    return 0;
}

CLIENT *checkIfClientExists(struct List *eventHorizon, CLIENT *client)
{
    struct Node *start = eventHorizon->head;
    struct Node *end = eventHorizon->tail;
    while (start != end && start->next != end)
    {
        struct Event *event = start->data;
        struct Event *event2 = end->data;
        if (((CLIENT *)event->client)->id == client->id)
        {
            return event->client;
        }
        if (((CLIENT *)event2->client)->id == client->id)
        {
            return event2->client;
        }
        start = start->next;
        end = end->previous;
    }
    return NULL;
}

EVENT *findEventByClientId(struct List *eventHorizon, int id)
{
    struct Node *currentStart = eventHorizon->head;
    struct Node *currentEnd = eventHorizon->tail;
    while (currentStart != currentEnd && currentStart->next != currentEnd)
    {
        struct Event *event = currentStart->data;
        struct Event *event2 = currentEnd->data;
        if (event->client->id == id)
        {
            return event;
        }
        if (event2->client->id == id)
        {
            return event2;
        }
        currentStart = currentStart->next;
        currentEnd = currentEnd->previous;
    }
    return NULL;
}

struct List *createEventHorizon(struct List *clientList, int performanceMode)
{
    printf("Creating event horizon...                    \n");
    struct List *eventHorizon = createList();
    int numberOfClients = rand() % 4000 + 3000;
    for (int i = numberOfClients; i != 0; --i)
    {
        CLIENT *client = NULL;
        struct Node *current = clientList->head;
        int randomClient = rand() % clientList->size;
        for (int j = 0; j < randomClient; j++)
        {
            current = current->next;
        }
        while (current && client == NULL)
        {
            if (((CLIENT *)current->data)->inStore == 0)
            {
                client = current->data;
            }
            else
                current = current->next;
        }
        if (client && client->inStore == 0)
        {
            struct Event *arrival = (struct Event *)malloc(sizeof(struct Event));
            client->inStore = 1;
            arrival->client = client;
            arrival->type = 0;
            arrival->time = rand() % 43200;
            addToMiddle(eventHorizon, arrival, *compareTimes);
            if (performanceMode != 1)
                printf("\33[0;32mEvent horizon created: %d%%\r\33[0;97m", (int)((numberOfClients - i) * 100 / numberOfClients) + 1);
        }
        else
        {
            i++;
        }
    }

    printf("\33[0;32mEvent horizon created.                          \n\33[0;97m");
    return eventHorizon;
}

void addSingleClient(struct List *eventHorizon, struct List *productList, struct List *clientList, int arrivalTime)
{
    CLIENT *client = NULL;
    struct Node *current = clientList->head;
    int randomClient = rand() % clientList->size;
    for (int j = 0; j < randomClient; j++)
    {
        current = current->next;
    }
    while (current && client == NULL)
    {
        if (((CLIENT *)current->data)->inStore == 0)
        {
            client = current->data;
        }
        else
            current = current->next;
    }
    if (client && client->inStore == 0 && client->id != ((EVENT *)eventHorizon->head->data)->client->id)
    {
        struct Event *arrival = (struct Event *)malloc(sizeof(struct Event));
        client->inStore = 1;
        arrival->client = client;
        arrival->type = 0;
        arrival->time = rand() % 43200;
        addToMiddle(eventHorizon, arrival, *compareTimes);
    }
}

void writeLineToTxt(char line[])
{
    char caracter = 0;
    int i = 0;
    FILE *file = fopen("History.txt", "a");
    fprintf(file, "%s\n", line);
    fclose(file);
}

void printEvent(EVENT *event)
{
    printf("Client: %d\n", event->client->id);
    if (event->type == 0)
        printf("Type: Arrival\n");
    else if (event->type == 1)
        printf("Type: Checkout\n");
    else if (event->type == 2)
        printf("Type: Pay and leave\n");
    printf("Time: %d\n", event->time);
}

int averageTimeInQueue(struct List *eventHorizon)
{

    int sum = 0;
    int numberOfClients = 0;

    struct Node *current = eventHorizon->head;
    EVENT *event = (EVENT *)current->data;

    while (current)
    {
        CLIENT *client = (CLIENT *)malloc(sizeof(CLIENT));

        if (event->type == 1)
        {
            client = event->client;

            struct Node *current2 = current->next;
            EVENT *event2 = (EVENT *)current2->data;

            while (event2)
            {
                if (event2->type == 2 && event2->client->id == client->id)
                {
                    numberOfClients++;
                    sum += event2->time - event->time;
                    break;
                }
                current2 = current2->next;
            }
        }
        current = current->next;
    }

    return sum / numberOfClients;
}