#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "structures.h"
#include "customer.h"
#include "employee.h"
#include "product.h"
#include "categ.h"
#include "menu.h"

void welcomeMenu()
{
    printf("\n\t\t\t\t   =================================================================================================");
    printf("\n\n\t\t\t\t\t\t\t < < < WELCOME TO OUR ONLINE MARKETING PROGRAM! > > >");
    printf("\n\n\t\t\t\t   =================================================================================================");
    printf("\n\n\t\t\t\t   Here's a brief and simple introduction about this program, please consider reading the following:");
    printf("\n\n\n\t\t\t\t\t>> Our Online Marketing System Project is a simple console application designed to\n\n\t\t\t\t\t   demonstrate the practical use of C programming language and its features..");
    printf("\n\n\t\t\t\t\t>> The source code of our project has been written in C programming language without\n\n\t\t\t\t\t   the use of any graphics, and it is to be compiled in Code::Blocks using GCC compiler.");
    printf("\n\n\t\t\t\t\t>> This program is divided into two main major options with different access rights,\n\n\t\t\t\t\t   the ADMIN and the USER modes... More information will be available as you continue in\n\n\t\t\t\t\t   the program..");
    printf("\n\n\t\t\t\t\t>> For a better experience, please maximize the screen and set the font size to 16");
    printf("\n\n\t\t\t\t\t\t\t* * *  THANK   YOU   FOR   USING   OUR   PROGRAM  * * *");
    printf("\n\n\t\t\t\t\t\t\t=======================================================");
    printf("\n\n\t\t\t\t\t\t\t\t   Press any key to continue ...");
    getch();
    system("cls");
}

void mainMenu(employeeList empList, customerList custList, categoryList categList)
{
    char choice[1];
    char password[20];

    while(1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\t\t\t\t        MAIN MENU\n");
        printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

        printf("\n\t\t\t\t\t\t\t\t\t<1> Continue as an ADMIN\n");
        printf("\n\t\t\t\t\t\t\t\t\t<2> Continue as a USER\n");
        printf("\n\t\t\t\t\t\t\t\t\t<3> Exit the program\n");

        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        printf("\n\t\t\t\t\t\t\t\t\tEnter  your  choice:  ");
        scanf("%s", choice);
        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        switch(atoi(choice))
        {
        case 1:
            printf("\n\t\t\t\t\t\t\t\t\tadmin password: ");
            scanf("%s", password);
            if(strcmp(password, "a") == 0)
            {
                system("cls");
                adminMenu(empList, categList);
                break;
            }
            printf("\n\t\t\t\t\t\t\t\t\tInvalid Password!\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 2:
            system("cls");
            primaryUserMenu(custList, empList, categList);
            break;

        case 3:
            printf("\n\t\t\t\t\t\t\t\t\tEnd of program!\n");
            return;

        default:
            printf("\n\t\t\t\t\t\t\t\t\tError: Invalid Option!\n");
            printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        }

    }
}

void adminMenu(employeeList empList, categoryList categList)
{
    char choice[1], activityLog[100], inbox[100];
    int employeeID;

    while(1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\t\t\t\t        ADMIN MENU\n");
        printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

        printf("\n\t\t\t\t\t\t\t\t\t<1> Add a new Product\n");
        printf("\n\t\t\t\t\t\t\t\t\t<2> Edit a Product\n");
        printf("\n\t\t\t\t\t\t\t\t\t<3> Remove a Product\n");
        printf("\n\t\t\t\t\t\t\t\t\t<4> Add a new Category\n");
        printf("\n\t\t\t\t\t\t\t\t\t<5> Fire an Employee\n");
        printf("\n\t\t\t\t\t\t\t\t\t<6> View all Products\n");
        printf("\n\t\t\t\t\t\t\t\t\t<7> View Activity Log\n");
        printf("\n\t\t\t\t\t\t\t\t\t<8> View Mail Inbox");
        printf("\n\n\t\t\t\t\t\t\t\t\t<9> Go back to Main Menu\n");

        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        printf("\n\t\t\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%s", choice);
        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        switch(atoi(choice))
        {
        case 1:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    ADD A NEW PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            addNewProduct(&categList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 2:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t     EDIT A PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            editProduct(&categList);
            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t     DELETE A PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            removeProduct(&categList);
            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 4:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t     ADD A NEW CATEGORY\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            addNewCategory(&categList);
            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 5:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    FIRE AN EMPLOYEE\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            printEmployeeList(empList);
            printf("\t\t\t\t\t\t\t\t\tEnter the Employee's id: ");
            scanf("%d", &employeeID);
            printf("\n");

            fireEmployee(&empList, employeeID);
            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 6:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW ALL PRODUCTS\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            productList * tmpProdList = fillTmpProdList();
            printProductList(*tmpProdList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 7:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW ACTIVITY LOG\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n");

            FILE * pf = fopen("activityLog.txt", "r");
            while(!feof(pf))
            {
                fgets(activityLog, 100, pf);
                printf("\t\t\t\t\t\t\t\t%s\n", activityLog);
            }
            fclose(pf);

            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 8:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW MAIL INBOX\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            FILE * pf1 = fopen("inbox.txt", "r");
            while(!feof(pf1))
            {
                fgets(inbox, 100, pf1);
                printf("\t\t\t\t\t\t\t\t\t%s\n\n", inbox);
            }
            fclose(pf1);

            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 9:
            system("cls");
            return;

        default:
            printf("\n\t\t\t\t\t\t\t\t\tError: Invalid Option!\n");
            printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;
        }

    }
}

void primaryUserMenu(customerList custList, employeeList empList, categoryList categList)
{
    char choice[1];
    Customer cust;

    while(1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\t\t\t\t        SignUp/LogIn\n");
        printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

        printf("\n\t\t\t\t\t\t\t\t\t<1> Sign up a new account\n");
        printf("\n\t\t\t\t\t\t\t\t\t<2> Login to an existing account\n");
        printf("\n\t\t\t\t\t\t\t\t\t<3> Go back to Main Menu\n");

        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        printf("\n\t\t\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%s", choice);
        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        switch(atoi(choice))
        {
        case 1:
            signUp(&custList);
            printf("\n\n\t\t\t\t\t\t\t\t\tPress any key to continue ...");
            getch();
            system("cls");
            break;

        case 2:
            if(logIn(custList, &cust) == 0)
            {
                printf("\n\t\t\t\t\t\t\t\t\tPress any key to continue ...");
                getch();
                system("cls");
                break;
            }
            printf("\n\t\t\t\t\t\t\t\t\tPress any key to continue ...");
            getch();
            system("cls");
            secondaryUserMenu(cust, empList, custList, categList);
            system("cls");
            break;

        case 3:
            system("cls");
            return;

        default:
            printf("\n\t\t\t\t\t\t\t\t\tError: Invalid Option!\n");
            printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        }

    }
}

void secondaryUserMenu(Customer cust, employeeList empList, customerList custList, categoryList categList)
{
    char choice[1], message[100], categName[20];
    categoryList * tmpCategList = fillTmpCategList();

    while(1)
    {
        printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t\t\t\t\t        USER MENU\n");
        printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

        printf("\t\t\t\t\t\t\t\t\t Welcome, %s\n\n\t\t\t\t\t\t\t\t\t You have: %.2f$", cust.username, cust.cash);
        printf("\n\t\t\t\t\t\t\t\t\t ---------\n");

        printf("\n\t\t\t\t\t\t\t\t\t<1> View all Products\n");
        printf("\n\t\t\t\t\t\t\t\t\t<2> View Products by Category\n");
        printf("\n\t\t\t\t\t\t\t\t\t<3> Search for a Product\n");
        printf("\n\t\t\t\t\t\t\t\t\t<4> Buy a new Product\n");
        printf("\n\t\t\t\t\t\t\t\t\t<5> View User Information\n");
        printf("\n\t\t\t\t\t\t\t\t\t<6> Edit User Information\n");
        printf("\n\t\t\t\t\t\t\t\t\t<7> View Owned Products\n");
        printf("\n\t\t\t\t\t\t\t\t\t<8> Register for a Job here!\n");
        printf("\n\t\t\t\t\t\t\t\t\t<9> Transfer Money!\n");
        printf("\n\t\t\t\t\t\t\t\t\t<10> Contact Admins!\n");
        printf("\n\t\t\t\t\t\t\t\t\t<11> Logout\n");

        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        printf("\n\t\t\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%s", choice);
        printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");

        switch(atoi(choice))
        {
        case 1:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW ALL PRODUCTS\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            productList * tmpProdList = fillTmpProdList();
            printProductList(*tmpProdList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 2:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW PROD BY CATEG\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            printAvailableCateg(*tmpCategList);
            printf("\n\n\t\t\t\t\t\t\t\t\tChoose the Category: ");
            scanf("%s", categName);
            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

            while(belongsProdCategToCategList(categList, categName) == 0)
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

            categoryCell * tmpCateg = categList.head;
            while(tmpCateg->next != NULL && strcasecmp(tmpCateg->name, categName) != 0)
                tmpCateg = tmpCateg->next;

            printProductList(*tmpCateg->data);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t   SEARCH FOR A PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            searchProduct();
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 4:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t     BUY A PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            buyProduct(&cust, &categList, empList, &custList);
            printf("\n\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 5:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t  VIEW USER INFORAMTION\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            viewUserInformation(cust);
            printf("\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 6:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t  EDIT USER INFORMATION\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            editUserInfo(&cust, &custList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 7:
            system("cls");
            printf("\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    VIEW OWNED PRODUCT\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            viewOwnedProduct(cust);
            printf("\n\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 8:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    REGISTER FOR A JOB\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            registerForJob(&empList, cust, &custList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 9:
            system("cls");
            printf("\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t     TRANSFER MONEY\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n\n");

            transferMoney(&cust, &custList);
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 10:
            system("cls");
            printf("\n\t\t\t\t\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t\t\t\t\t    CONTACT ADMINS\n");
            printf("\t\t\t\t\t\t\t\t\t=========================\n");


            fputs("\n\t\t\t\t\t\t\t\t\tWrite your message here: ",stdin);
            printf("\n\t\t\t\t\t\t\t\t\t");
            gets(message);
            fflush(stdin);
            FILE * pf2 = fopen("inbox.txt", "a");
            fprintf(pf2, "\nMessage from user [%s]: {%s}", cust.username, message);
            fclose(pf2);

            printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        case 11:
            system("cls");
            return;

        default:
            printf("\n\t\t\t\t\t\t\t\t\tError: Invalid Option!\n");
            printf("\n\t\t\t\t\t\t\t\t\t-------------------------\n");
            printf("\n\t\t\t\t\t\t\t\t\tPress an key to continue...");
            getch();
            system("cls");
            break;

        }

    }
}
