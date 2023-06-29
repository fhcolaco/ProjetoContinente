#include "employee.h"

EMPLOYEE *createEmployee(int numMec, char *name)
{
    EMPLOYEE *employee = (EMPLOYEE *)malloc(sizeof(EMPLOYEE));
    employee->numMec = numMec;
    strcpy(employee->name, name);
    employee->isWorking = false;
    return employee;
}

struct List *createEmployeeList()
{
    struct List *employeeList = createList();
    FILE *file;
    file = fopen("funcionariosOriginal.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {
        printf("Creating employee list...\n");
        char ch;
        int numMec;
        char name[40];
        while (ch != EOF)
        {
            name[0] = 0;
            ch = '\0';
            for (int i = 0; i < 2; i++)
            {
                char aux[40] = "\0";
                ch = fgetc(file);
                while (ch != '\t' && ch != '\n' && ch != EOF)
                {
                    strncat(aux, &ch, 1);
                    ch = fgetc(file);
                }
                if (i == 0)
                {
                    numMec = atoi(aux);
                }
                if (i == 1)
                {
                    strcpy(name, aux);
                }
            }
            addToBackOfList(employeeList, createEmployee(numMec, name));
        }
    }
    printf("\33[0;32mEmployee list created!\n\33[0;97m");
    fclose(file);
    return employeeList;
}

EMPLOYEE *chooseRandomEmployee(struct List *employeeList)
{
    int randomEmployee = rand() % (employeeList->size / 2);
    struct Node *current = employeeList->head;
    for (int i = 0; i < randomEmployee; i++)
    {
        current = current->next;
    }
    while (((EMPLOYEE *)current->data)->isWorking == true && current != NULL)
    {
        current = current->next;
    }
    if (current->data == NULL)
    {
        return NULL;
    }
    EMPLOYEE *employee = (EMPLOYEE *)current->data;
    ((EMPLOYEE *)current->data)->isWorking = true;
    return employee;
}