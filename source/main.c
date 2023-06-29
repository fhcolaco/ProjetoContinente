#include "CONSTANTS.h"
#include "genericList.h"
#include "functions.c"
#include "clients.h"
#include "employee.h"
#include "eventHorizon.h"
#include "checkout.h"
#include "checkoutList.h"

#include <conio.h>

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
    char ch;
    int numberOfClientsInStore = 0;
    int numberOfClientsServed = 0;
    int numberOfProcesEvents = 0;
    float totalCash = 0;
    while (eventHorizon->head != NULL)
    {
        EVENT *event = (EVENT *)eventHorizon->head->data;
        // In-simulation menu
        if (kbhit())
        {
            ch = getch();
            do
            {
                ch = '\0';
                printMenuInSimulation(event->time);
                while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '0')
                {
                    if (kbhit)
                    {
                        ch = getch();
                        if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '0')
                        {
                            printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                        }
                    }
                }
                if (ch == '0')
                {
                    printf("\nSimulação terminada.");
                    exit(0);
                }
                else if (ch == 'q' || ch == 'Q')
                {
                    printf("\nA voltar à simulação.\n");
                    break;
                }
                else if (ch == '1')
                {
                    do
                    {
                        ch = '\0';
                        printMenuInSimulationClient(numberOfClientsInStore);
                        while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                        {
                            if (kbhit)
                            {
                                ch = getch();
                                if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                                {
                                    printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                                }
                                else
                                {
                                    switch (ch)
                                    {
                                    case '1':
                                        char id[5];
                                        printf("Consultar se um cliente está na loja\nQual o ID do cliente que pretende consultar? ");
                                        scanf("%s", &id);
                                        if (atoi(id) == 0)
                                        {
                                            printf("O ID introduzido não é válido.\n");
                                            break;
                                        }
                                        CLIENT *client = checkIfClientExists(eventHorizon, atoi(id));
                                        if (client != NULL)
                                        {
                                            printf("O cliente %d %s está na loja.\n", client->id, client->name);
                                        }
                                        else
                                        {
                                            printf("O cliente não está na loja.\n");
                                        }
                                        printf("\nPrima ENTER para continuar.");
                                        getchar();
                                        break;
                                    case '2':
                                        printf("Mudar um cliente de fila\n");
                                        break;
                                    case '0':
                                        printf("A voltar ao menu anterior.\n");
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                        if (ch == 'q' || ch == 'Q')
                        {
                            printf("\nA voltar à simulação.\n");
                            break;
                        }
                    } while (ch != 'q' && ch != 'Q' && ch != '0');
                }
                else if (ch == '2')
                {
                    do
                    {
                        ch = '\0';
                        printMenuInSimulationCheckout(checkoutList->size);
                        while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                        {
                            if (kbhit)
                            {
                                ch = getch();
                                if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                                {
                                    printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                                }
                                else
                                {
                                    switch (ch)
                                    {
                                    case '1':
                                        printf("Consultar estado das caixas\n");
                                        printCheckoutList(checkoutList);
                                        break;
                                    case '2':
                                        printf("Abrir uma caixa\n");
                                        break;
                                    case '3':
                                        printf("Fechar uma caixa\n");
                                        break;
                                    case '0':
                                        printf("A voltar ao menu anterior.\n");
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                        if (ch == 'q' || ch == 'Q')
                        {
                            printf("\nA voltar à simulação.\n");
                            break;
                        }
                    } while (ch != 'q' && ch != 'Q' && ch != '0');
                }
                else if (ch == '3')
                {
                    do
                    {
                        ch = '\0';
                        printMenuInSimulationStatistics(checkoutList->size);
                        while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                        {
                            if (kbhit)
                            {
                                ch = getch();
                                if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                                {
                                    printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                                }
                            }
                        }
                        if (ch == 'q' || ch == 'Q')
                        {
                            printf("\nA voltar à simulação.\n");
                            break;
                        }
                    } while (ch != 'q' && ch != 'Q' && ch != '0');
                }
                else if (ch == '4')
                {
                    do
                    {
                        ch = '\0';
                        printMenuInSimulationEvents(numberOfProcesEvents);
                        while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                        {
                            if (kbhit)
                            {
                                ch = getch();
                                if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '0')
                                {
                                    printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                                }
                            }
                        }
                        if (ch == 'q' || ch == 'Q')
                        {
                            printf("\nA voltar à simulação.\n");
                            break;
                        }
                    } while (ch != 'q' && ch != 'Q' && ch != '0');
                }
            } while (ch != 'q' && ch != 'Q');
        }
        if (event->type == 0)
        {
            // Enter the store
            sprintf(sentence, "%s : Cliente %d entrou na loja", instanceToTime(event->time), event->client->id, event->time);
            writeLineToTxt(sentence);
            EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
            newEvent->client = event->client;
            newEvent->type = 1;
            newEvent->time = event->time + calculateTotalTimeInStore(event->client);
            numberOfClientsInStore++;
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
            sprintf(sentence, "%s : Cliente %d terminou de procurar produtos e entrou na fila da caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
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
                sprintf(sentence, "%s : Cliente %d vai ser atendido na caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
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
                sprintf(sentence, "%s : Cliente %d terminou de ser atendido da caixa %d e saiu da loja.", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                writeLineToTxt(sentence);
                numberOfClientsInStore--;
                numberOfClientsServed++;
                totalCash += calculateTotalPrice(event->client);
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
        numberOfProcesEvents++;
        int chance = rand() % 100; // Get a client with a 5% chance
        if (((EVENT *)eventHorizon->head->data)->time < 43200 && clientList->size != 0 && (chance < 5 || eventHorizon->size <= 10))
        {
            addSingleClient(eventHorizon, productList, clientList, ((EVENT *)eventHorizon->head->data)->time);
        }
        nextNode(eventHorizon);
        if (false) // Change to true to see the simulation in real time
        {
            system("cls");
            printf("Time: %s\n", instanceToTime(event->time));
            printf("Eventos: %d\n", eventHorizon->size);
        }
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
    sprintf(sentence, "A loja fechou com %d clientes atendidos.", numberOfClientsServed);
    writeLineToTxt(sentence);
    sprintf(sentence, "A loja fechou com %.2f€ de lucro.", totalCash);
    writeLineToTxt(sentence);
    printf("\nNúmero de clientes atendidos: %d\n", numberOfClientsServed);
    printf("Lucro total: %.2f€\n", totalCash);
    printf("\n\33[0;32mSimulação terminada com sucesso!\nObrigado por ter escolhido o Continente.\n\tOnde a sua satisfação é a nossa prioridade, menos nas ilhas\n\33[0;97m");
    return 0;
};
