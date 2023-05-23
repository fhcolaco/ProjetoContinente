#include "CONSTANTS.h"
#include "genericList.h"
#include "clients.h"
#include "employee.h"
#include "eventHorizon.h"
#include "checkout.h"
#include "checkoutList.h"

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
    while (eventHorizon->head != NULL)
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
            checkStatusOfCheckouts(checkoutList, employeeList);
            CHECKOUT *checkout = chooseCheckout(checkoutList);
            if (checkout == NULL)
            {
                printf("ERRO: checkout não encontrado.\n");
                printf("Cliente: %d\n", event->client->id);
                printf("Evento: %d\n", event->type);
                exit(1);
            }
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
            // Start being served
            checkStatusOfCheckouts(checkoutList, employeeList);
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
            checkStatusOfCheckouts(checkoutList, employeeList);
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
        nextNode(eventHorizon);
        printf("Exitem %d eventos na Lista EVENTOS.\n", eventHorizon->size);
    }
    while (checkoutList->size != 1)
    {
        checkStatusOfCheckouts(checkoutList, employeeList);
    }
    if (checkoutList->size == 1)
    {
        closeCheckout(checkoutList, checkoutList->head->data);
        sprintf(sentence, "ALL THE CHECKOUTS ARE NOW CLOSED. THE STORE WILL CLOSE IN 1 SECOND. THANK YOU AND GOODBYE");
        writeLineToTxt(sentence);
    }
    destroyList(eventHorizon);
    destroyList(checkoutList);
    destroyList(employeeList);
    destroyList(clientList);
    destroyList(productList);

    printf("\n\33[0;32mSimulação terminada com sucesso!\nObrigado por ter escolhido o Continente.\n\tOnde a sua satisfação é a nossa prioridade, menos nas ilhas\n\33[0;97m");
    return 0;
};
