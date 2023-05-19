#include "genericList.h"
#include "functions.h"
#include "clients.h"
#include "employee.h"
#include "eventHorizon.h"
#include "checkout.h"
#include "checkoutList.h"

void printClientByID(struct List *list, int n)
{
    struct List *list2 = copyList(list);
    for (int i = 0; i < n; i++)
    {
        list2->head = list2->head->next;
    }
    printClient((CLIENT *)list2->head->data);
    printShoppingList((CLIENT *)list2->head->data);
    free(list2);
}

int main(void)
{
    srand(time(NULL));
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList();
    struct List *clientList = createClientList(productList);
    struct List *employeeList = createEmployeeList();
    struct List *eventHorizon = createEventHorizon(clientList);
    struct List *checkoutList = createCheckoutList();

    printf("\n\33[0;32mData loaded successfully!\n\33[0;97m");
    printf("Exitem %d produtos na Lista PRODUTOS.\n", productList->size);
    printf("Exitem %d clientes na Lista CLIENTES.\n", clientList->size);
    printf("Exitem %d empregados na Lista COLABORADORES.\n", employeeList->size);
    printf("Exitem %d eventos na Lista EVENTOS.\n", eventHorizon->size);
    printf("Exitem %d caixas na Lista CAIXAS.\n", checkoutList->size);

    printf("\n\33[0;32mPressione ENTER para continuar.\n\33[0;97m");
    getchar();
    printf("Começar simulação\n");
    FILE *txt = fopen("History.txt", "w");
    fprintf(txt, "Histórico de eventos:\n");
    fclose(txt);
    char sentence[100];
    while (eventHorizon->head->next != NULL)
    {
        EVENT *event = (EVENT *)eventHorizon->head->data;
        if (event->type == 0)
        {
            // Enter the store
            sprintf(sentence, "Cliente %d entrou na loja ao instante %d.", event->client->id, event->time);
            writeLineToTxt(sentence);
            EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
            newEvent->client = event->client;
            newEvent->type = 1;
            newEvent->time = event->time + calculateTotalTimeInStore(event->client);
            addToMiddle(eventHorizon, newEvent, *compareTimes);
        }
        else if (event->type == 1)
        {
            // Finish searching for products and enter a queue
            checkStatusOfCheckouts(checkoutList);
            CHECKOUT *checkout = chooseCheckout(checkoutList);
            sprintf(sentence, "Cliente %d terminou de procurar produtos e entrou na fila da caixa %d no instante %d.", event->client->id, checkout->numCheckout, event->time);
            writeLineToTxt(sentence);
            addToCheckoutQueue(checkout, event->client);
            if (checkout->servingClient == NULL && checkout->queue->size == 1)
            {
                EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                newEvent->client = event->client;
                newEvent->type = 2;
                newEvent->time = event->time;
                addToMiddle(eventHorizon, newEvent, *compareTimes);
            }
        }
        else if (event->type == 2)
        {
            CHECKOUT *checkout = findCheckout(checkoutList, event->client);
            if (checkout == NULL)
            {
                printf("ERRO: checkout não encontrado.\n");
                printf("Cliente: %d\n", event->client->id);
                printf("Evento: %d\n", event->type);
                exit(1);
            }
            else
            {
                sprintf(sentence, "Cliente %d vai ser atendido na caixa %d no instante %d.", event->client->id, checkout->numCheckout, event->time);
                writeLineToTxt(sentence);
                EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                newEvent->client = event->client;
                newEvent->type = 3;
                newEvent->time = event->time + (int)calculateTotalTimeInCheckOut(event->client);
                addServingClient(checkout);
                removeFromCheckoutQueue(checkout);
                addToMiddle(eventHorizon, newEvent, *compareTimes);
            }
        }
        else if (event->type == 3)
        {
            // finished being served and left the store
            CHECKOUT *checkout = findServingClient(checkoutList, event->client);
            if (checkout == NULL)
            {
                printf("ERRO: checkout não encontrado.\n");
                printf("Cliente: %d\n", event->client->id);
                printf("Evento: %d\n", event->type);
                exit(1);
            }
            else
            {
                sprintf(sentence, "Cliente %d terminou de ser atendido da caixa %d e saiu da loja no instante %d.", event->client->id, checkout->numCheckout, event->time);
                writeLineToTxt(sentence);
                removeServingClient(checkout);
                clientList = deleteClient(clientList, event->client);
                if (checkout->servingClient == NULL && checkout->queue->head != NULL)
                {
                    EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                    newEvent->client = checkout->queue->head->data;
                    newEvent->type = 2;
                    newEvent->time = event->time;
                    addToMiddle(eventHorizon, newEvent, *compareTimes);
                }
            }
        }
        eventHorizon->head = eventHorizon->head->next;
        free(event);
        eventHorizon->size--;
        printf("Exitem %d clientes na Lista CLIENTES e %d eventos na Lista EVENTOS.\n", clientList->size, eventHorizon->size);
    }
    return 0;
};
