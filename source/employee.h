#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdbool.h>
#include <stdlib.h>
#include "genericList.h"

typedef struct Employee
{
    int numMec;
    char name[40];
    bool isWorking;
} EMPLOYEE;

EMPLOYEE *createEmployee(int numMec, char *name);
struct List *createEmployeeList();
EMPLOYEE *chooseRandomEmployee(struct List *employeeList);

#endif