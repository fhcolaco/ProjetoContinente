#include <stdio.h>

void printInt(void *data)
{
    printf("%d ", *(int *)data);
}

void compareQuickFind(void *data, void *data2)
{
    if (*(int *)data == *(int *)data2)
    {
        printf("Found it!");
    }
}