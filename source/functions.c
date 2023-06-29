#include <stdio.h>
#include "CONSTANTS.h"

void printInt(void *data)
{
    printf("%d ", *(int *)data);
}

void printChar(void *data)
{
    printf("%c ", *(char *)data);
}

void printString(void *data)
{
    printf("%s ", (char *)data);
}

int compareEqualInt(void *data, void *data2)
{
    if (*(int *)data == *(int *)data2)
    {
        return 1;
    }
    return 0;
}

const char *instanceToTime(int instance)
{
    int hours = 9;
    if (instance >= 3600)
    {
        hours += instance / 3600;
    }
    int minutes = (instance % 3600) / 60;
    int seconds = (instance % 3600) % 60;
    static char time[5] = "";
    if (hours < 10)
    {
        sprintf(time, "0%d:", hours);
    }
    else
    {
        sprintf(time, "%d:", hours);
    }
    if (minutes < 10)
    {
        sprintf(time, "%s0%d:", time, minutes);
    }
    else
    {
        sprintf(time, "%s%d:", time, minutes);
    }
    if (seconds < 10)
    {
        sprintf(time, "%s0%d", time, seconds);
    }
    else
    {
        sprintf(time, "%s%d", time, seconds);
    }
    return time;
}

void printMenuInSimulation(int time)
{
    printf("\nMenu de simulação:");
    printf("\nTempo: %s", instanceToTime(time));
    printf("\n\n1 - Menu de cliente");
    printf("\n2 - Menu de caixas");
    printf("\n3 - Estatísticas");
    printf("\n4 - Menu de eventos");
    printf("\n0 - Sair da simulação");
    printf("\n\nPrima Q para voltar à simulação.");
}

void printMenuInSimulationClient(int numberOfClientsInStore)
{
    printf("\nMenu de simulação:");
    printf("\nVersão Cliente");
    printf("\nNumero de clientes em loja: %d", numberOfClientsInStore);
    printf("\n\n1 - Consultar se um cliente está na loja");
    printf("\n2 - Mudar um cliente de fila (Ainda não está implementado)");
    printf("\n0 - Voltar ao menu anterior");
    printf("\n\nPrima Q para voltar à simulação.");
}

void printMenuInSimulationCheckout(int numberOfCheckouts)
{
    printf("\nMenu de simulação:");
    printf("\nVersão Caixa");
    int max = MAX_CHECKOUTS;
    printf("\nNumero de caixas abertas: %d/%d", numberOfCheckouts, max);
    printf("\n\n1 - Consultar estado das caixas (Implementado mas não testado)");
    printf("\n2 - Abrir uma caixa (Ainda não está implementado)");
    printf("\n3 - Fechar uma caixa (Ainda não está implementado)");
    printf("\n0 - Voltar ao menu anterior");
    printf("\n\nPrima Q para voltar à simulação.");
}

void printMenuInSimulationStatistics()
{
    printf("\nMenu de simulação:");
    printf("\nVersão Estatísticas");
    printf("\n\n1 - Estatísticas de Cliente (Ainda não está implementado)");
    printf("\n2 - Estatísticas de Caixa (Ainda não está implementado)");
    printf("\n3 - Estatísticas de Loja (Ainda não está implementado)");
    printf("\n0 - Voltar ao menu anterior");
    printf("\n\nPrima Q para voltar à simulação.");
}

void printMenuInSimulationEvents(int numberOfProcessedEvents)
{
    printf("\nMenu de simulação:");
    printf("\nVersão Eventos");
    printf("\nNumero de caixas abertas: %d", numberOfProcessedEvents);
    printf("\n\n1 - Consultar evento atual (Ainda não está implementado)");
    printf("\n2 - Consultar próximo evento (Ainda não está implementado)");
    printf("\n0 - Voltar ao menu anterior");
    printf("\n\nPrima Q para voltar à simulação.");
}
