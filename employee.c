#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "employee.h"

employeeCell * createEmployeeCell(Employee emp)
{
    employeeCell * c = (employeeCell*)malloc(sizeof(employeeCell));
    c->data = emp;
    c->next = NULL;
    return c;
}

employeeList * createEmployeeList()
{
    employeeList * l = (employeeList*)malloc(sizeof(employeeList));
    l->head = NULL;
    return l;
}

void addToHeadEmp(employeeList * l, Employee e)
{
    employeeCell * c = createEmployeeCell(e);
    c->next = l->head;
    l->head = c;
}

void addToTailEmp(employeeList * l, Employee e)
{
    if(l->head == NULL)
    {
        addToHeadEmp(l, e);
        return;
    }

    employeeCell * tmp = l->head;
    while(tmp->next != NULL)
        tmp = tmp->next;

    employeeCell * c = createEmployeeCell(e);
    tmp->next = c;
}

/** Gets data from files then adds it to the list **/
void fillEmployeeList(employeeList * l)
{
    Employee emp;
    FILE * pf = fopen("employee.txt", "r");
    while(!feof(pf))
    {
        fscanf(pf, "%d %s %s %s %d %s", &emp.employeeId, emp.username, emp.firstName, emp.lastName, &emp.age, emp.email);
        addToTailEmp(l, emp);
    }
    fclose(pf);
}

/** Saves the data from the employee list to the file **/
void saveDataToFileEmp(employeeList l)
{
    FILE * pf = fopen("employee.txt", "w");
    employeeCell * tmp = l.head;
    while(tmp != NULL)
    {
        fprintf(pf, "\n%d %s %s %s %d %s", tmp->data.employeeId, tmp->data.username, tmp->data.firstName, tmp->data.lastName, tmp->data.age, tmp->data.email);
        tmp = tmp->next;
    }
    fclose(pf);
}

/** Updates the data from the employee list to the file **/
void updateDataOfFileEmp(Employee emp)
{
    FILE * pf = fopen("employee.txt", "a");
    fprintf(pf, "\n%d %s %s %s %d %s", emp.employeeId, emp.username, emp.firstName, emp.lastName, emp.age, emp.email);
    fclose(pf);
}

void printEmployeeCell(employeeCell c)
{
    printf("\t\t\t\t\t%d\t\t%s\t\t%s\t\t%d\t\t%s\n\n", c.data.employeeId, c.data.firstName, c.data.lastName, c.data.age, c.data.email);
}

void printEmployeeList(employeeList l)
{
    employeeCell * tmp = l.head;
    printf("\t\t\t\t\t\t\t\t\t     Employee List:\n");
    printf("\t\t\t\t\t\t\t\t\t    ----------------\n\n");
    printf("\t\t\t\t\tID\t\tName\t\tLastName\tAge\t\tEmail\n");
    printf("\t\t\t\t\t--\t\t----\t\t--------\t---\t\t-----\n\n");
    while(tmp != NULL)
    {
        printEmployeeCell(*tmp);
        tmp = tmp->next;
    }
    printf("\t\t\t\t\t-----------------------------------------------------------------------------------------\n\n");
}

/** Returns 1 if yes, 0 if no **/
int belongsIDToEmpList(employeeList l, int id)
{
    for(employeeCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(tmp->data.employeeId == id)
            return 1;
    return 0;
}

/** Returns 1 if yes, 0 if no **/
int belongsUsernameToEmpList(employeeList l, char name[])
{
    for(employeeCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(strcmp(tmp->data.username, name) == 0)
            return 1;
    return 0;
}

int nbOfEmpList(employeeList l)
{
    int counter = 0;
    for(employeeCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        counter++;
    return counter;
}

void deleteHeadEmp(employeeList * l)
{
    if(l->head == NULL)
        return;
    employeeCell * tmp = l->head;
    l->head = l->head->next;
    free(tmp);
}

void fireEmployee(employeeList * l, int id)
{
    if(l->head == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\tEmpty list!\n");
        return;
    }

    if(belongsIDToEmpList(*l, id) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tInvalid Employee Id!\n");
        return;
    }

    if(l->head->data.employeeId == id)
    {
        deleteHeadEmp(l);
        printf("\t\t\t\t\t\t\t\t\tEmployee Removed Successfully!\n");
        saveDataToFileEmp(*l);
        return;
    }

    employeeCell * tmp = l->head;
    while(tmp->next != NULL && tmp->next->data.employeeId != id)
        tmp = tmp->next;

    employeeCell * tmp2 = tmp->next;
    tmp->next = tmp2->next;     // tmp->next->next;
    free(tmp2);
    printf("\t\t\t\t\t\t\t\t\tEmployee Removed Successfully!");
    saveDataToFileEmp(*l);
}

int generateEmpID(employeeList l)
{
    static int empID = 1000;
    while(belongsIDToEmpList(l, empID) == 1)
        empID++;
    return empID;
}

//int main()
//{
//    employeeList * empList = createEmployeeList();
//    fillEmployeeList(empList);
//    printEmployeeList(*empList);
//    fireEmployee(empList, empList->head->next->data);
//    printEmployeeList(*empList);
//    free(empList);
//    return 0;
//}
