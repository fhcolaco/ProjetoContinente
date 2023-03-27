#include <stdio.h>
#include <stdlib.h>
#include "genericList.h"
#include "functions.h"

int main(void)
{
    struct List *list = createList();
    int array[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        addToBackOfList(list, &array[i]);
    }
    printList(list, printInt);

    return 0;
}