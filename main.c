#include "genericList.h"
#include "functions.h"
#include "clients.h"
#include "employee.h"
#include "eventHorizon.h"
#include "checkout.h"
#include "checkoutList.h"

int main(void)
{
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

//    printf("\n\33[0;32mPressione ENTER para continuar.\n\33[0;97m");
//    getchar();
//    system("clear");
//    printf("Bem-vindo ao sistema de gestão de supermercados.\n");
//    printf("O que deseja fazer?\n");
//    printf("1 - Começar simulação\n");
//    printf("2 - Ver lista de clientes\n");
//    printf("3 - Ver lista de colaboradores\n");
//    printf("4 - Ver lista de eventos\n");
//    printf("5 - Ver lista de produtos\n");
//    printf("* - Sair\n");
//    printf ("Opção: ");
//    char option = getchar();
//    switch (option) {
//        case '1':
    //AINDA É SÓ UM TESTE
    printf("Começar simulação\n");
    FILE *txt = fopen("History.txt", "w");
    fprintf(txt, "Histórico de eventos:\n");
    fclose(txt);
    CHECKOUT *checkout = createCheckout(checkoutList->size + 1);
    openCheckout(checkoutList, checkout);
    struct List *clientListC = copyList(clientList);
    struct List *eventHorizonC = copyList(eventHorizon);
    CLIENT *client = (CLIENT *)clientListC->head->data;
    EVENT *event = (EVENT *)eventHorizonC->head->data;
    for (int i = 0; i < 5 ; i++) {
        char sentence[100];
        sprintf(sentence, "O cliente %d entrou na loja ao instante %d", client->id, event->time);
        writeLineToTxt(sentence);
        addToCheckoutQueue(checkout, client, event->time + calculateTotalTimeInStore(client));
        addServingClient(checkout, event->time + (int)calculateTotalTimeInStore(client));
        removeFromCheckoutQueue(checkout);
        removeServingClient(checkout, event->time + (int)calculateTotalTimeInStore(client) +
                                      (int)calculateTotalTimeInCheckOut(client));
        writeLineToTxt("\n\n");
//                free(event);
//                free(client);
        clientListC->head = clientListC->head->next;
        eventHorizonC->head = eventHorizonC->head->next;
        client = (CLIENT *)clientListC->head->data;
        event = (EVENT *)eventHorizonC->head->data;
    }
    closeCheckout(checkoutList, checkout);
    free(client);
    free(event);
    free(checkout);
    free(clientListC);
    free(eventHorizonC);
//            break;
//        case '2':
//            printf("Ver lista de clientes\n");
//            struct List *clientListCopy = copyList(clientList);
//            for (int i = 1; i <= clientListCopy->size; i++) {
//                printClient((struct Client *) clientListCopy->head->data);
//                printf("\n");
//                clientListCopy->head = clientListCopy->head->next;
//            }
//            free(clientListCopy);
//            break;
//
//        case '3':
//            printf("Ver lista de colaboradores\n");
//            struct List *employeeListCopy = copyList(employeeList);
//            for (int i = 1; i <= employeeListCopy->size; i++) {
//                printEmployee((struct Employee *) employeeListCopy->head->data);
//                printf("\n");
//                employeeListCopy->head = employeeListCopy->head->next;
//            }
//            free(employeeListCopy);
//            break;
//        case '4':
//            printf("Ver lista de eventos\n");
//            struct List *eventHorizonCopy = copyList(eventHorizon);
//            for (int i = 1; i <= eventHorizonCopy->size; i++) {
//                printEvent((struct Event *) eventHorizonCopy->head->data);
//                printf("\n");
//                eventHorizonCopy->head = eventHorizonCopy->head->next;
//            }
//            free(eventHorizonCopy);
//            break;
//        case '5':
//            printf("Ver lista de produtos\n");
//            struct List *productListCopy = copyList(productList);
//            for (int i = 1; i <= productListCopy->size; i++) {
//                printProduct((PRODUCT *) (struct Product *) productListCopy->head->data);
//                printf("\n");
//                productListCopy->head = productListCopy->head->next;
//            }
//            free(productListCopy);
//            break;
//        case '*':
//            printf("Espero acima de 9,5. Obrigado!\n");
//            break;
//        default:
//            break;
//    }
    return 0;
};
