#include "eventHorizon.h"

int compareTimes(struct Event *data, struct Event *data2)
{
    if (data->time > data2->time)
    {
        return 1;
    }
    return 0;
}

CLIENT *checkIfClientExists(struct List *eventHorizon, int id)
{
    struct Node *current = eventHorizon->head;
    for (int i = 0; i < eventHorizon->size; i++)
    {
        struct Event *event = (struct Event *)current->data;
        if (event->client->id == id)
        {
            return event->client;
        }
        current = current->next;
    }
    return NULL;
}

struct List *createEventHorizon(struct List *clientList)
{
    printf("Creating event horizon...\n");
    struct List *eventHorizon = createList();
    unsigned int t = 0;
    int numberOfClients = rand() % 4000 + 3000;
    int randomClient = 0;
    for (int i = numberOfClients; i != 0; i--)
    {
        struct List *current = copyList(clientList);
        randomClient = rand() % clientList->size;
        for (int j = 0; j < randomClient; j++)
        {
            current->head = current->head->next;
        }
        while (checkIfClientExists(eventHorizon, ((struct Client *)current->head->data)->id) != NULL)
        {
            if (current->head->next == NULL)
            {
                i++;
                break;
            }
            else
            {
                current->head = current->head->next;
            }
        }
        if (checkIfClientExists(eventHorizon, ((struct Client *)current->head->data)->id) == NULL)
        {
            struct Event *arrival = (struct Event *)malloc(sizeof(struct Event));
            t = rand() % 43200;
            arrival->client = (struct Client *)current->head->data;
            arrival->type = 0;
            arrival->time = t;
            addToMiddle(eventHorizon, arrival, *compareTimes);
            free(current);
        }
    }

    printf("\33[0;32mEvent horizon created.\n\33[0;97m");
    return eventHorizon;
}

void addSingleClient(struct List *eventHorizon, struct List *productList, struct List *clientList, int arrivalTime)
{
    struct List *current = copyList(clientList);
    int randomClient = rand() % clientList->size;
    CLIENT *client = NULL;
    for (int j = 0; j < randomClient; j++)
    {
        current->head = current->head->next;
    }
    while (checkIfClientExists(eventHorizon, ((struct Client *)current->head->data)->id) != NULL)
    {
        if (current->head->next == NULL)
        {
            break;
        }
        else
        {
            current->head = current->head->next;
        }
    }
    if (checkIfClientExists(eventHorizon, ((struct Client *)current->head->data)->id) != NULL)
    {
        client = addSingleClientToClientList(clientList, productList);
    }
    if (checkIfClientExists(eventHorizon, ((struct Client *)current->head->data)->id) == NULL || client)
    {
        struct Event *arrival = (struct Event *)malloc(sizeof(struct Event));
        arrival->client = (struct Client *)current->head->data;
        arrival->type = 0;
        int time = arrivalTime + rand() % 300;
        arrival->time = time > 43200 ? arrivalTime : time;
        addToMiddle(eventHorizon, arrival, *compareTimes);
        free(current);
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
