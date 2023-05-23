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
