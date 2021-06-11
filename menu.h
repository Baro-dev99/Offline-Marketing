#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void welcomeMenu();

void mainMenu(employeeList, customerList, categoryList);

void adminMenu(employeeList, categoryList);

void primaryUserMenu(customerList, employeeList, categoryList);

void secondaryUserMenu(Customer, employeeList, customerList, categoryList);

void helpMenu();


#endif // MENU_H_INCLUDED
