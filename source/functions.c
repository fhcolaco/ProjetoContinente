#include <stdio.h>

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
    printf("\n\n1 - Consultar cliente (Ainda não está implementado)");
    printf("\n2 - Consultar caixas (Ainda não está implementado)");
    printf("\n3 - Consultar estatísticas (Ainda não está implementado)");
    printf("\n4 - Consultar próximo evento (Ainda não está implementado)");
    printf("\n0 - Sair da simulação");
    printf("\n\nPrima Q para voltar à simulação.");
}
