#include <stdio.h>

void printInt(void *data)
{
    printf("%d ", *(int *)data);
}