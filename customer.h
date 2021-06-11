#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

customerCell * createCustomerCell(Customer);

customerList * createCustomerList();

void addToHeadCust(customerList *, Customer);

void addToTailCust(customerList*, Customer);

void signUp(customerList *);

int logIn(customerList , Customer * );

void fillCustomerList(customerList * );

void saveDataToFileCust(customerList );

void updateDataOfFileCust(Customer );

int belongsToCustList(customerList , char[] );

int belongsIDToCustList(customerList , int );

int nbOfCustList(customerList );

int generateCustID(customerList );

void emptyTheListCust(customerList * );

void registerForJob(employeeList * , Customer , customerList * );

int jobCompetition();

void buyProduct(Customer * , categoryList * , employeeList , customerList * );

void viewOwnedProduct(Customer );

void viewUserInformation(Customer );

void editUserInfo(Customer * , customerList * );

void transferMoney(Customer * , customerList * );

#endif // CUSTOMER_H_INCLUDED
