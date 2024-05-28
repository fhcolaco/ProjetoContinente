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
    int performanceMode = 0;
    printf("Run in performance mode ? (Y/N)\n");
    char ch = getch();
    if (ch == 'Y' || ch == 'y')
    {
        performanceMode = 1;
    }
    srand(time(NULL));
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList(performanceMode);
    struct List *clientList = createClientList(productList, performanceMode);
    struct List *employeeList = createEmployeeList(performanceMode);
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
    int numberOfClientsInStore = 0;
    int numberOfClientsServed = 0;
    int numberOfProcesEvents = 0;
    int numberOfProductsSold = 0;
    float totalCash = 0;
    int maxCheckouts = 9;
    int checkoutStatisticMatrix[maxCheckouts - 1][1];
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
                                        EVENT *event = findEventByClientId(eventHorizon, atoi(id));
                                        if (event)
                                        {
                                            printf("O cliente %d %s está na loja.\n", event->client->id, event->client->name);
                                            // if (event->type == 0)
                                            // {
                                            //     printf("Está à procura de produtos.\n");
                                            // }
                                            // else if (event->type == 1)
                                            // {

                                            //     printf("Entrou na fila de espera.\n");
                                            // }
                                            // else if (event->type == 2)
                                            // {
                                            //     printf("Está a ser atendido na caixa %d.\n", findCheckout(checkoutList, ((CLIENT *)event->client)->id)->numCheckout);
                                            // }
                                            // else if (event->type == 3)
                                            // {
                                            //     printf("Está a pagar o que deve na caixa %d e vai abandonar a loja.\n", findCheckout(checkoutList, ((CLIENT *)event->client)->id)->numCheckout);
                                            // }
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
                                        printf("A abrir uma caixa...\n");
                                        if (checkoutList->size < 9)
                                        {
                                            openCheckout(checkoutList, employeeList);
                                            printf("A caixa %d foi aberta.\n", ((CHECKOUT *)(checkoutList->tail->data))->numCheckout);
                                        }
                                        else
                                        {
                                            printf("\nNão é possível abrir uma caixa. Limite de caixas abertas foi atingido");
                                        }
                                        break;
                                    case '3':
                                        printf("Fechar uma caixa\nQual o número da caixa que pretende fechar? ");
                                        int checkoutNumber;
                                        scanf("%d", &checkoutNumber);
                                        CHECKOUT *checkout = findCheckoutByNumCheckout(checkoutList, checkoutNumber);
                                        if (checkout)
                                        {
                                            int result = closeCheckout(checkoutList, checkout);
                                            if (result == 0)
                                            {
                                                printf("A caixa %d foi fechada.\n", checkoutNumber);
                                            }
                                            else
                                            {
                                                printf("A caixa %d tem clientes à espera. Foi dada a ordem de despejo\n", checkoutNumber);
                                            }
                                        }
                                        else
                                        {
                                            printf("A caixa %d não está aberta.\n", checkoutNumber);
                                        }
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
                        while (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '3' && ch != '0')
                        {
                            if (kbhit)
                            {
                                ch = getch();
                                if (ch != 'q' && ch != 'Q' && ch != 'm' && ch != 'M' && ch != '1' && ch != '2' && ch != '3' && ch != '0')
                                {
                                    printf("\nOpção inválida.\nPrima M para apresentar o menu.");
                                }
                                else
                                {
                                    switch (ch)
                                    {
                                    case '1':
                                        printf("Estatísticas de Cliente\n");
                                        printf("Número de clientes que entraram na loja: %d\n", numberOfClientsInStore);
                                        printf("Número de clientes que saíram da loja: %d\n", numberOfClientsServed);
                                        break;
                                    case '2':
                                        printf("Estatísticas de Caixa\n");
                                        printf("Número de caixas abertas: %d\n", checkoutList->size);
                                        // checkoutStatisticMatriz
                                        int maxClientsServed = 0;
                                        int indexCheckout_maxCientsServer = 0;
                                        int maxProductsSold = 0;
                                        int indexCheckout_maxProductsSold = 0;
                                        for (int i = 0; i < maxCheckouts; i++)
                                        {
                                            for (int j = 0; j < 2; j++)
                                            {
                                                if (checkoutStatisticMatrix[i][j] > maxClientsServed)
                                                {
                                                    maxClientsServed = checkoutStatisticMatrix[i][j];
                                                    indexCheckout_maxCientsServer = i;
                                                }
                                                if (checkoutStatisticMatrix[i][j] > maxProductsSold)
                                                {
                                                    maxProductsSold = checkoutStatisticMatrix[i][j];
                                                    indexCheckout_maxProductsSold = i;
                                                }
                                            }
                                        }

                                        printf("Caixa que atendeu mais clientes: [Caixa %d]\n", indexCheckout_maxCientsServer + 1);
                                        printf("Caixa que vendeu mais produtos: [Caixa %d]\n", indexCheckout_maxProductsSold + 1);
                                        printf("Funcionario que atendeu menos clientes: [%s]\n", leastProductiveEmployee(employeeList)->name);
                                        // printf("Tempo médio de espera na fila: %s\n", instanceToTime(averageTimeInQueue(eventHorizon)));
                                        break;
                                    case '3':
                                        printf("Estatísticas de Loja\n");
                                        printf("Total de produtos vendidos: %d\n", numberOfProductsSold);
                                        printf("Total de ganhos: %.2f\n", totalCash);
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
                                else
                                {
                                    switch (ch)
                                    {
                                    case '1':
                                        printf("Consultar evento atual da simulação\n");

                                        break;
                                    case '2':
                                        printf("Consultar próximo evento da simulação\n");
                                        break;
                                    case '0':
                                        printf("A voltar ao menu anterior.\n");
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                            if (ch == 'q' || ch == 'Q')
                            {
                                printf("\nA voltar à simulação.\n");
                                break;
                            }
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
        if (((EVENT *)eventHorizon->head->data)->time < 43200 && clientList->size != 0 && eventHorizon->size <= 25)
        {
            addSingleClient(eventHorizon, clientList, ((EVENT *)eventHorizon->head->data)->time);
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
