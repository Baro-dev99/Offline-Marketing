#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "customer.h"
#include "employee.h"
#include "product.h"
#include "categ.h"

customerCell * createCustomerCell(Customer cust)
{
    customerCell * c = (customerCell*)malloc(sizeof(customerCell));
    c->data = cust;
    c->next = NULL;
    return c;
}

customerList * createCustomerList()
{
    customerList * l = (customerList*)malloc(sizeof(customerList));
    l->head = NULL;
    return l;
}

void addToHeadCust(customerList * l, Customer cust)
{
    customerCell * c = createCustomerCell(cust);
    c->next = l->head;
    l->head = c;
}

void addToTailCust(customerList * l, Customer cust)
{
    if(l->head == NULL)
    {
        addToHeadCust(l, cust);
        return;
    }

    customerCell * tmp = l->head;
    while(tmp->next != NULL)
        tmp = tmp->next;

    customerCell * c = createCustomerCell(cust);
    tmp->next = c;
}

void signUp(customerList * l)
{
    Customer tmp;
    tmp.customerId = generateCustID(*l);
    printf("\n\t\t\t\t\t\t\t\t\tEnter the following information:\n");
    printf("\t\t\t\t\t\t\t\t\t--------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tFirst Name: ");
    scanf("%s", tmp.firstName);
    printf("\n\t\t\t\t\t\t\t\t\tLast Name: ");
    scanf("%s", tmp.lastName);
    printf("\n\t\t\t\t\t\t\t\t\tAge: ");
    scanf("%d", &tmp.age);
    printf("\n\t\t\t\t\t\t\t\t\tUsername: ");
    scanf("%s", tmp.username);
    while(belongsToCustList(*l, tmp.username) == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tUsername already exists!\n");
        printf("\t\t\t\t\t\t\t\t\t------------------------\n");
        printf("\n\t\t\t\t\t\t\t\t\tUsername: ");
        scanf("%s", tmp.username);
    }
    printf("\n\t\t\t\t\t\t\t\t\tPassword: ");
    scanf("%s", tmp.password);
    printf("\n\t\t\t\t\t\t\t\t\tEmail: ");
    scanf("%s", tmp.email);
    printf("\n\t\t\t\t\t\t\t\t\tCash($): ");
    scanf("%f", &tmp.cash);

    addToTailCust(l, tmp);
    updateDataOfFileCust(tmp);

    FILE * pf = fopen("activityLog.txt", "a");
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(pf, "\nNew User [%s] Created at %s         ------------------------", tmp.username, asctime(timeinfo));
    fclose(pf);

    printf("\n\t\t\t\t\t\t\t\t\t--------------------------");
    printf("\n\n\t\t\t\t\t\t\t\t\tData saved successfully!");
    printf("\n\n\t\t\t\t\t\t\t\t\t--------------------------");
}

/** Returns 1 if username & password are correct otherwise returns 0 **/
int logIn(customerList l, Customer * cust)
{
    char username[20];
    char password[20];
    printf("\n\t\t\t\t\t\t\t\t\tUsername: ");
    scanf("%s", username);
    if(belongsToCustList(l, username) == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tUsername not available!\n");
        printf("\n\t\t\t\t\t\t\t\t\t-----------------------\n");
        return 0;
    }

    customerCell * tmp = l.head;
    while(tmp != NULL && strcmp(tmp->data.username, username) != 0)
        tmp = tmp->next;
    printf("\n\t\t\t\t\t\t\t\t\tPassword: ");
    scanf("%s", password);
    printf("\n\t\t\t\t\t\t\t\t\t-----------------------\n");
    if(strcmp(tmp->data.password, password) != 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tIncorrect password!\n");
        printf("\n\t\t\t\t\t\t\t\t\t-----------------------\n");
        return 0;
    }
    *cust = tmp->data;
    printf("\n\t\t\t\t\t\t\t\t\tLoading Data ...\n");
    printf("\n\t\t\t\t\t\t\t\t\t-----------------------\n");
    return 1;
}

/** Gets data from files then adds it to the list **/
void fillCustomerList(customerList * l)
{
    Customer cust;
    FILE * pf = fopen("customer.txt", "r");
    while(!feof(pf))
    {
        fscanf(pf, "%d %s %s %d %s %s %f %s", &cust.customerId, cust.firstName, cust.lastName, &cust.age, cust.username, cust.password, &cust.cash, cust.email);
        addToTailCust(l, cust);
    }
    fclose(pf);
}

/** Saves the data from the customer list to the file **/
void saveDataToFileCust(customerList l)
{
    FILE * pf = fopen("customer.txt", "w");
    customerCell * tmp = l.head;
    while(tmp != NULL)
    {
        fprintf(pf, "\n%d %s %s %d %s %s %.2f %s", tmp->data.customerId, tmp->data.firstName, tmp->data.lastName, tmp->data.age, tmp->data.username, tmp->data.password, tmp->data.cash, tmp->data.email);
        tmp = tmp->next;
    }
    fclose(pf);
}

/** Updates the data from the customer list to the file **/
void updateDataOfFileCust(Customer cust)
{
    FILE * pf = fopen("customer.txt", "a");
    fprintf(pf, "\n%d %s %s %d %s %s %.2f %s", cust.customerId, cust.firstName, cust.lastName, cust.age, cust.username, cust.password, cust.cash, cust.email);
    fclose(pf);
}

/** Returns 1 if yes, 0 if no **/
int belongsToCustList(customerList l, char username[])
{
    for(customerCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(strcmp(tmp->data.username, username) == 0)
            return 1;
    return 0;
}

/** Returns 1 if yes, 0 if no **/
int belongsIDToCustList(customerList l, int id)
{
    for(customerCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(tmp->data.customerId == id)
            return 1;
    return 0;
}

int nbOfCustList(customerList l)
{
    int counter = 0;
    for(customerCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        counter++;
    return counter;
}

int generateCustID(customerList l)
{
    static int custID = 1000;
    while(belongsIDToCustList(l, custID) == 1)
        custID++;
    return custID;
}

void emptyTheListCust(customerList * l)
{
    if(l->head == NULL)
        return;
    customerCell * tmp = l->head;
    l->head = l->head->next;
    free(tmp);
    emptyTheListCust(l);
}

void registerForJob(employeeList * l, Customer c, customerList * cl)
{
    int result;

    if(belongsUsernameToEmpList(*l, c.username) == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tYou Already Got The Job!!\n");
        printf("\t\t\t\t\t\t\t\t\t-------------------------\n");
        return;
    }

    result = jobCompetition();

    if(result < 30)
    {
        printf("\n\t\t\t\t\t\t\t\t\tYour Overall Score is: %d/50\n", result);
        printf("\t\t\t\t\t\t\t\t\t----------------------------\n");
        printf("\n\t\t\t\t\t\t\t\t\tSorry, You didn't get the Job!\n");
        printf("\t\t\t\t\t\t\t\t\t------------------------------\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\t\tYour Overall Score is: %d/50\n", result);
    printf("\t\t\t\t\t\t\t\t\t----------------------------\n");
    printf("\n\t\t\t\t\t\t\t\t\tCongratulations, You Got The Job!\n");
    printf("\t\t\t\t\t\t\t\t\t---------------------------------\n");

    Employee e;
    strcpy(e.firstName, c.firstName);
    strcpy(e.lastName, c.lastName);
    strcpy(e.username, c.username);
    strcpy(e.email, c.email);
    e.age = c.age;
    e.employeeId = generateEmpID(*l);

    addToTailEmp(l, e);
    updateDataOfFileEmp(e);
}

int jobCompetition()
{
    int score1 = 0, score2 = 0, score3 = 0, score4 = 0, score5 = 0;
    char choice[1];

    printf("\n\t\t\t\t\t\t\t\t\tAnswer the Following Questions:\n");
    printf("\t\t\t\t\t\t\t\t\t-------------------------------\n\n");

    /// Question #1
    printf("\t\t\t\t\t\t\t\t\t1-Why did you choose this Job?\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t<1>To earn money!\n\n");
    printf("\t\t\t\t\t\t\t\t\t<2>I like this domain!\n\n");
    printf("\t\t\t\t\t\t\t\t\t<3>Both 1 & 2\n\n");
    printf("\t\t\t\t\t\t\t\t\t<4>None of the above!\n\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    switch(atoi(choice))
    {
    case 1:
        score1 += 0;
        break;
    case 2:
        score1 += 5;
        break;
    case 3:
        score1 += 10;
        break;
    case 4:
        score1 += 3;
        break;
    }

    /// Question #2
    printf("\t\t\t\t\t\t\t\t\t2-What are your salary expectations?\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t<1>More than 5000$\n\n");
    printf("\t\t\t\t\t\t\t\t\t<2>Less than 3000$\n\n");
    printf("\t\t\t\t\t\t\t\t\t<3>Less than 1500$\n\n");
    printf("\t\t\t\t\t\t\t\t\t<4>More than 7000$\n\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    switch(atoi(choice))
    {
    case 1:
        score2 += 10;
        break;
    case 2:
        score2 += 5;
        break;
    case 3:
        score2 += 3;
        break;
    case 4:
        score2 += 0;
        break;
    }

    /// Question #3
    printf("\t\t\t\t\t\t\t\t\t3-Can you work extra hours on the weekend?\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t<1>Yes, always\n\n");
    printf("\t\t\t\t\t\t\t\t\t<2>No, never\n\n");
    printf("\t\t\t\t\t\t\t\t\t<3>Sometimes\n\n");
    printf("\t\t\t\t\t\t\t\t\t------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    switch(atoi(choice))
    {
    case 1:
        score3 += 5;
        break;
    case 2:
        score3 += 0;
        break;
    case 3:
        score3 += 10;
        break;
    }

    /// Question #4
    printf("\t\t\t\t\t\t\t\t\t4-Will you quit for a double-pay job offer?\n");
    printf("\t\t\t\t\t\t\t\t\t-------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t<1>Yes, of course!\n\n");
    printf("\t\t\t\t\t\t\t\t\t<2>No, never!\n\n");
    printf("\t\t\t\t\t\t\t\t\t-------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    switch(atoi(choice))
    {
    case 1:
        score4 += 10;
        break;
    case 2:
        score4 += 0;
        break;
    }

    /// Question #5
    printf("\t\t\t\t\t\t\t\t\t5-Which language is better? Java or C?\n");
    printf("\t\t\t\t\t\t\t\t\t--------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t<1>C language\n\n");
    printf("\t\t\t\t\t\t\t\t\t<2>Java language\n\n");
    printf("\t\t\t\t\t\t\t\t\t<3>None of the above!\n\n");
    printf("\t\t\t\t\t\t\t\t\t--------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    switch(atoi(choice))
    {
    case 1:
        score5 += 0;
        break;
    case 2:
        score5 += 0;
        break;
    case 3:
        score5 += 10;
        break;
    }

    return score1 + score2 + score3 + score4 + score5;
}

void buyProduct(Customer * cust, categoryList * categList, employeeList empList, customerList * custList)
{
    char categName[20];
    printAvailableCateg(*categList);
    printf("\n\n\t\t\t\t\t\t\t\t\tChoose the Category: ");
    scanf("%s", categName);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    while(belongsProdCategToCategList(*categList, categName) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tCategory Not Available!\n");
        printf("\n\t\t\t\t\t\t\t\t\tChoose the Category (-1 to exit): ");
        scanf("%s", categName);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(strcmp(categName, "-1") == 0)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }

    }

    categoryCell * tmpCateg = categList->head;
    while(tmpCateg->next != NULL && strcasecmp(tmpCateg->name, categName) != 0)
        tmpCateg = tmpCateg->next;

    printProductList(*tmpCateg->data);

    char prodID[1];
    printf("\n\t\t\t\t\t\t\t\t\tEnter the product ID: ");
    scanf("%s", prodID);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    while(belongsIDToProdList(*tmpCateg->data, atoi(prodID)) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tProduct ID Not Available!\n\n");
        printf("\t\t\t\t\t\t\t\t\tEnter the product ID (-1 to exit): ");
        scanf("%s", prodID);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(atoi(prodID) == -1)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }
    }

    productCell * tmpProd = tmpCateg->data->head;
    while(tmpProd->next != NULL && tmpProd->data.productId != atoi(prodID))
        tmpProd = tmpProd->next;

    printProductCell2(*tmpProd);

    char prodStock[1];
    printf("\t\t\t\t\t\t\t\t\tEnter the quantity: ");
    scanf("%s", prodStock);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    while(atoi(prodStock) == 0 || atoi(prodStock) > tmpProd->data.productStock)
    {
        printf("\t\t\t\t\t\t\t\t\tQuantity Not Available!\n\n");
        printf("\t\t\t\t\t\t\t\t\tEnter the quantity (-1 to exit): ");
        scanf("%s", prodStock);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(atoi(prodStock) == -1)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }
    }

    float balance;
    balance = tmpProd->data.productPrice * atoi(prodStock);

    /// Employee Offer 20%
    int employeeOffer = 0;
    if(belongsUsernameToEmpList(empList, cust->username) == 1)
    {
        balance *= 0.8;
        employeeOffer = 1;
    }

    if(balance > cust->cash)
    {
        printf("\n\t\t\t\t\t\t\t\t\tInsufficient Funds!\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\t\tAvailable Shipping Fees:");
    printf("\n\t\t\t\t\t\t\t\t\t------------------------\n");

    printf("\n\t\t\t\t\t\t\t\t\t1-Fast Shipment: +%.2f$\n", balance * 0.1);
    printf("\n\t\t\t\t\t\t\t\t\t2-Normal Shipment: +%.2f$\n", balance * 0.05);
    printf("\n\t\t\t\t\t\t\t\t\t3-Slow Shipment: +%.2f$\n", balance * 0.02);
    printf("\n\t\t\t\t\t\t\t\t\t----------------------------\n");

    int choice;
    printf("\n\t\t\t\t\t\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");

    while(choice != 1 && choice != 2 && choice != 3)
    {
        printf("\t\t\t\t\t\t\t\t\tOption Not Available!\n\n");
        printf("\t\t\t\t\t\t\t\t\tEnter your choice (-1 to exit): ");
        scanf("%d", &choice);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(choice == -1)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }
    }

    float tmpBal = balance;
    if(choice == 1)
        balance += balance * 0.1;
    else if(choice == 2)
        balance += balance * 0.05;
    else
        balance += balance * 0.02;

    if(balance > cust->cash)
    {
        printf("\n\t\t\t\t\t\t\t\t\tInsufficient Funds!\n");
        return;
    }

    printf("\n\n\t\t\t\t\t\t\t\t\t   Payment Successful!");
    printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t        YOUR BILL:\n");
    printf("\t\t\t\t\t\t\t\t\t=========================\n");
    printf("\t\t\t\t\t\t\t\t\tProduct Price: %.2f$\n\n", tmpProd->data.productPrice);
    printf("\t\t\t\t\t\t\t\t\tPurchased Quantity: %d\n\n", atoi(prodStock));

    if(employeeOffer == 1)
        printf("\t\t\t\t\t\t\t\t\tEmployee Offer -20%%%: -%.2f$\n\n", tmpProd->data.productPrice * 0.2);

    if(choice == 1)
        printf("\t\t\t\t\t\t\t\t\tFast Shipment +10%%%: +%.2f$\n\n", tmpBal * 0.1);
    else if(choice == 2)
        printf("\t\t\t\t\t\t\t\t\tNormal Shipment +5%%%: +%.2f$\n\n", tmpBal * 0.05);
    else
        printf("\t\t\t\t\t\t\t\t\tSlow Shipment +2%%%: +%.2f$\n\n", tmpBal * 0.02);

    printf("\t\t\t\t\t\t\t\t\tTotal Price: %.2f$\n\n", balance);
    cust->cash -= balance;
    printf("\t\t\t\t\t\t\t\t\tRemaining Cash: %.2f$\n", cust->cash);
    printf("\t\t\t\t\t\t\t\t\t=========================");

    customerCell * tmpCust = custList->head;
    while(tmpCust->next != NULL && strcmp(tmpCust->data.username, cust->username) != 0)
        tmpCust = tmpCust->next;

    tmpCust->data.cash = cust->cash;


    productList * tmpProdList = fillTmpProdList();
    productCell * tmp = tmpProdList->head;
    while(tmp->next != NULL && strcasecmp(tmpProd->data.productName, tmp->data.productName) != 0)
        tmp = tmp->next;
    tmp->data.productStock -= atoi(prodStock);

    saveDataToFileCust(*custList);
    saveDataToFileProd(*tmpProdList);
    emptyTheListCateg(categList);
    fillCategoryList(categList);

    FILE * pf = fopen("activityLog.txt", "a");
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(pf, "\nProduct [%s] bought by [%s] at %s         ------------------------", tmpProd->data.productName, tmpCust->data.username, asctime(timeinfo));
    fclose(pf);

    // free tmpProdList

    FILE * op = fopen(cust->username, "a");
    fprintf(op, "\n%s %d", tmpProd->data.productName, atoi(prodStock));
    fclose(op);
}

void viewOwnedProduct(Customer cust)
{
    char prodName[20];
    int prodStock, counter = 1;

    FILE * op = fopen(cust.username, "r");

    while(!feof(op))
    {
        fscanf(op, "%s %d", prodName, &prodStock);
        printf("\n\t\t\t\t\t\t\t\t\t%d- Product: %s, Purchased Qt: %d", counter, prodName, prodStock);
        printf("\n\t\t\t\t\t\t\t\t\t-----------------------------------");
        counter ++;
    }

    fclose(op);
}

void viewUserInformation(Customer cust)
{
    printf("\t\t\t\t\t\t\t\t\tFirst Name: %s\n", cust.firstName);
    printf("\t\t\t\t\t\t\t\t\t-----------\n");
    printf("\n\t\t\t\t\t\t\t\t\tLast Name: %s\n", cust.lastName);
    printf("\t\t\t\t\t\t\t\t\t----------\n");
    printf("\n\t\t\t\t\t\t\t\t\tAge: %d\n", cust.age);
    printf("\t\t\t\t\t\t\t\t\t----\n");
    printf("\n\t\t\t\t\t\t\t\t\tCash: %.2f$\n", cust.cash);
    printf("\t\t\t\t\t\t\t\t\t-----\n");
    printf("\n\t\t\t\t\t\t\t\t\tUsername: %s\n", cust.username);
    printf("\t\t\t\t\t\t\t\t\t---------\n");
    printf("\n\t\t\t\t\t\t\t\t\tEmail: %s\n", cust.email);
    printf("\t\t\t\t\t\t\t\t\t------\n\n");
}

void editUserInfo(Customer * cust, customerList * custList)
{
    char choice[1];
    customerCell * tmpCust = custList->head;
    while(tmpCust->next != NULL && tmpCust->data.customerId != cust->customerId)
        tmpCust = tmpCust->next;

    /// Edit FirstName
    char newFName[20];
    printf("\n\t\t\t\t\t\t\t\t\tChange First Name? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t---------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew First Name: ");
        scanf("%s", newFName);

        strcpy(tmpCust->data.firstName, newFName);
        strcpy(cust->firstName, newFName);

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's First Name Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t---------------------------------------\n");
    }

    /// Edit LastName
    char newLName[20];
    printf("\n\t\t\t\t\t\t\t\t\tChange Last Name? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t--------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Last Name: ");
        scanf("%s", newLName);

        strcpy(tmpCust->data.lastName, newLName);
        strcpy(cust->lastName, newLName);

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's Last Name Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t--------------------------------------\n");
    }

    /// Edit Age
    int newAge;
    printf("\n\t\t\t\t\t\t\t\t\tChange Age? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t--------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Age: ");
        scanf("%d", &newAge);

        tmpCust->data.age = newAge;
        cust->age = newAge;

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's Age Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t--------------------------------\n");
    }

    /// Edit Username
    char newUsername[20], oldUsername[20];
    strcpy(oldUsername, tmpCust->data.username);
    printf("\n\t\t\t\t\t\t\t\t\tChange Username? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t-------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Username: ");
        scanf("%s", newUsername);

        while(belongsToCustList(*custList, newUsername) == 1)
        {
            printf("\t\t\t\t\t\t\t\t\tUsername Already Exists!\n");
            printf("\n\t\t\t\t\t\t\t\t\tNew Username: ");
            scanf("%s", newUsername);
        }

        strcpy(tmpCust->data.username, newUsername);
        strcpy(cust->username, newUsername);

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's Username Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t-------------------------------------\n");
    }

    rename(oldUsername, newUsername);

    /// Edit Password
    char newPassword[20];
    printf("\n\t\t\t\t\t\t\t\t\tChange Password? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t-------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Password: ");
        scanf("%s", newPassword);

        strcpy(tmpCust->data.password, newPassword);
        strcpy(cust->password, newPassword);

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's Password Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t-------------------------------------\n");
    }

    /// Edit Email
    char newEmail[20];
    printf("\n\t\t\t\t\t\t\t\t\tChange Email? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t----------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Email: ");
        scanf("%s", newEmail);

        strcpy(tmpCust->data.email, newEmail);
        strcpy(cust->email, newEmail);

        printf("\n\n\t\t\t\t\t\t\t\t\tUser's Email Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------------------\n");
    }

    saveDataToFileCust(*custList);
}

void transferMoney(Customer * cust, customerList * custList)
{
    float money;
    customerCell * tmpCust = custList->head;
    while(tmpCust->next != NULL && tmpCust->data.customerId != cust->customerId)
        tmpCust = tmpCust->next;

    printf("\n\t\t\t\t\t\t\t\t\tYour current balance is: %.2f$", cust->cash);
    printf("\n\t\t\t\t\t\t\t\t\t------------------------");
    printf("\n\n\t\t\t\t\t\t\t\t\tEnter how much you want to transfer: ");
    scanf("%f", &money);
    printf("\t\t\t\t\t\t\t\t\t------------------------------------\n");

    tmpCust->data.cash += money;
    cust->cash += money;
    saveDataToFileCust(*custList);

    printf("\n\t\t\t\t\t\t\t\t\tYour new balance is: %.2f$", cust->cash);
    printf("\n\t\t\t\t\t\t\t\t\t--------------------\n");
}
