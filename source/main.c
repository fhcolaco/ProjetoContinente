#include "functions.c"
#include "eventHorizon.h"
#include "checkoutList.h"
#include <conio.h>

int main(void)
{
    int performanceMode = 0;
    printf("Performance mode? (y/n)\n");
    char ch = getch();
    if (ch == 'y')
    {
        performanceMode = 1;
    }

    srand(time(NULL));
    printf("Please wait while loading data...\n");
    struct List *productList = createProductList(performanceMode);
    struct List *clientList = createClientList(productList, performanceMode);
    struct List *employeeList = createEmployeeList(performanceMode);
    struct List *eventHorizon = createEventHorizon(clientList, performanceMode);
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
                                            if (event->type == 0)
                                            {
                                                printf("Está à procura de produtos.\n");
                                            }
                                            else if (event->type == 1)
                                            {

                                                printf("Entrou na fila de espera da caixa %d.\n", findCheckout(checkoutList, ((CLIENT *)event->client)->id)->numCheckout);
                                            }
                                            else if (event->type == 2)
                                            {
                                                printf("Está a ser atendido na caixa %d.\n", findCheckout(checkoutList, ((CLIENT *)event->client)->id)->numCheckout);
                                            }
                                            else if (event->type == 3)
                                            {
                                                printf("Está a pagar o que deve na caixa %d e vai abandonar a loja.\n", findCheckout(checkoutList, ((CLIENT *)event->client)->id)->numCheckout);
                                            }
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
                                        if (checkoutList->size < maxCheckouts)
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
                                        printf("Tempo médio de espera na fila: %s\n", instanceToTime(averageTimeInQueue(eventHorizon)));
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
            int sizeOfEventHorizon = eventHorizon->size;
            addToMiddle(eventHorizon, newEvent, *compareTimes);
        }
        else if (event->type == 1)
        {
            // Finish searching for products and enter a queue
            checkStatusOfCheckouts(checkoutList, employeeList);
            CHECKOUT *checkout = chooseCheckout(checkoutList, event->client);
            if (checkout)
            {
                sprintf(sentence, "%s : Cliente %d terminou de procurar produtos e entrou na fila da caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                writeLineToTxt(sentence);
                addToCheckoutQueue(checkout, event->client);
                if (checkout->servingClient == NULL && checkout->queue->size == 1)
                {
                    sprintf(sentence, "%s : Cliente %d vai ser atendido na caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                    writeLineToTxt(sentence);
                    if (addServingClient(checkout) == 1)
                    {

                        EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                        newEvent->client = event->client;
                        newEvent->type = 3;
                        newEvent->time = event->time + (int)calculateTotalTimeInCheckOut(event->client);
                        removeFromCheckoutQueue(checkout);
                        addToMiddle(eventHorizon, newEvent, *compareTimes);
                    }
                }
            }
        }
        else if (event->type == 2)
        {
            // Start being served
            checkStatusOfCheckouts(checkoutList, employeeList);
            CHECKOUT *checkout = findCheckout(checkoutList, event->client);
            if (checkout)
            {
                sprintf(sentence, "%s : Cliente %d vai ser atendido na caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                writeLineToTxt(sentence);
                if (addServingClient(checkout) == 1)
                {

                    EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                    newEvent->client = event->client;
                    newEvent->type = 3;
                    newEvent->time = event->time + (int)calculateTotalTimeInCheckOut(event->client);
                    removeFromCheckoutQueue(checkout);
                    addToMiddle(eventHorizon, newEvent, *compareTimes);
                }
            }
            else
            {
                printf("ERRO: Cliente %d não está em nenhuma fila.\n", event->client->id);
                printf("Tipo de evento: %d\n", event->type);
                printf("Tempo do evento: %s\n", instanceToTime(event->time));
            }
        }
        else if (event->type == 3)
        {
            // finished being served and left the store
            checkStatusOfCheckouts(checkoutList, employeeList);
            if (findIfServingClient(checkoutList, event->client))
            {
                printf("ERRO: Cliente %d já está a ser atendido.\n", event->client->id);
                printf("Tipo de evento: %d\n", event->type);
                printf("Tempo do evento: %s\n", instanceToTime(event->time));
            }
            else
            {
                CHECKOUT *checkout = findServingClient(checkoutList, event->client);
                if (checkout)
                {
                    checkoutStatisticMatrix[checkout->numCheckout - 1][0] += 1;
                    checkoutStatisticMatrix[checkout->numCheckout - 1][1] += event->client->shoppingList->size;
                    checkout->employee->clientsServed++;
                    numberOfProductsSold += event->client->shoppingList->size;
                    sprintf(sentence, "%s : Cliente %d terminou de ser atendido da caixa %d e saiu da loja.", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                    writeLineToTxt(sentence);
                    numberOfClientsInStore--;
                    numberOfClientsServed++;
                    totalCash += calculateTotalPrice(event->client);
                    checkout->servingClient = NULL;
                    event->client->inStore = 0;
                    changeShoppingList(event->client, productList);
                    if (checkout->servingClient == NULL && checkout->queue->head)
                    {
                        sprintf(sentence, "%s : Cliente %d vai ser atendido na caixa %d", instanceToTime(event->time), event->client->id, checkout->numCheckout, event->time);
                        writeLineToTxt(sentence);
                        if (addServingClient(checkout) == 1)
                        {

                            EVENT *newEvent = (EVENT *)malloc(sizeof(EVENT));
                            newEvent->client = checkout->queue->head;
                            newEvent->type = 3;
                            newEvent->time = event->time + (int)calculateTotalTimeInCheckOut(checkout->queue->head);
                            removeFromCheckoutQueue(checkout);
                            addToMiddle(eventHorizon, newEvent, *compareTimes);
                        }
                    }
                }
                else
                {
                    printf("ERRO: Cliente %d não está a ser atendido.\n", event->client->id);
                    printf("Tipo de evento: %d\n", event->type);
                    printf("Tempo do evento: %s\n", instanceToTime(event->time));
                }
            }
        }
        numberOfProcesEvents++;
        int chance = rand() % 100; // Get a client with a 10% chance
        if (((EVENT *)eventHorizon->head->data)->time < 43200 && clientList->size != 0 && (chance < 10 || eventHorizon->size <= 10))
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
    sprintf(sentence, "A loja fechou com %d produtos vendidos.", numberOfProductsSold);
    writeLineToTxt(sentence);
    sprintf(sentence, "A loja fechou com %.2f€ de lucro.", totalCash);
    writeLineToTxt(sentence);
    printf("\nNúmero de clientes atendidos: %d\n", numberOfClientsServed);
    printf("Número de produtos vendidos: %d\n", numberOfProductsSold);
    printf("Lucro total: %.2f€\n", totalCash);
    printf("\n\33[0;32mSimulação terminada com sucesso!\nObrigado por ter escolhido o Continente.\n\tOnde a sua satisfação é a nossa prioridade, menos nas ilhas\n\33[0;97m");
    return 0;
};
