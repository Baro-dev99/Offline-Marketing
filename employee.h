#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

employeeCell * createEmployeeCell(Employee);

employeeList * createEmployeeList();

void addToHeadEmp(employeeList*, Employee);

void addToTailEmp(employeeList*, Employee);

void fillEmployeeList(employeeList*);

void saveDataToFileEmp(employeeList);

void printEmployeeCell(employeeCell);

void printEmployeeList(employeeList);

void updateDataOfFileEmp(Employee);

int belongsIDToEmpList(employeeList, int);

int belongsUsernameToEmpList(employeeList, char[]);

int nbOfEmpList(employeeList);

void deleteHeadEmp(employeeList*);

void fireEmployee(employeeList*, int);

int generateEmpID(employeeList);

#endif // EMPLOYEE_H_INCLUDED
