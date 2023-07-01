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
    int clientsServed;
} EMPLOYEE;

EMPLOYEE *createEmployee(int numMec, char *name);
struct List *createEmployeeList(int performanceMode);
EMPLOYEE *chooseRandomEmployee(struct List *employeeList);
EMPLOYEE *leastProductiveEmployee(struct List *employeeList);

#endif