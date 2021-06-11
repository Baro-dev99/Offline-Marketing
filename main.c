#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "structures.h"
#include "employee.h"
#include "customer.h"
#include "categ.h"
#include "menu.h"


int main()
{

    employeeList * empList = createEmployeeList();
    fillEmployeeList(empList);

    customerList * custList = createCustomerList();
    fillCustomerList(custList);

    categoryList * categList = createCategoryList();
    fillCategoryList(categList);

    welcomeMenu();
    mainMenu(*empList, *custList, *categList);

    return 0;
}
