#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "product.h"
#include "categ.h"

productCell * createProductCell(Product prod)
{
    productCell * c = (productCell*)malloc(sizeof(productCell));
    c->data = prod;
    c->next = NULL;
    return c;
}

productList * createProductList()
{
    productList * l = (productList*)malloc(sizeof(productList));
    l->head = NULL;
    return l;
}

void addToHeadProd(productList * l, Product prod)
{
    productCell * c = createProductCell(prod);
    c->next = l->head;
    l->head = c;
}

void addToTailProd(productList * l, Product prod)
{
//    if(belongsIDToProdList(*l, prod.productId) == 1)
//        return;
    if(l->head == NULL)
    {
        addToHeadProd(l, prod);
        return;
    }

    productCell * tmp = l->head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    productCell * c = createProductCell(prod);
    tmp->next = c;
}

void deleteHeadProd(productList * l)
{
    if(l->head == NULL)
        return;
    productCell * tmp = l->head;
    l->head = l->head->next;
    free(tmp);
}

void emptyTheListProd(productList * l)
{
//    if(l->head == NULL)
//        return;
//    productCell * tmp = l->head;
//    l->head = l->head->next;
//    free(tmp);
//    emptyTheListProd(l);

    if(l->head == NULL)
        return;

    productCell * tmp = l->head;
    while(tmp != NULL)
    {
        l->head = l->head->next;
        free(tmp);
        tmp = l->head;
    }
}

void printProductCell(productCell c)
{
    printf("\t\t\t\t\t\t%d\t\t%s\t\t%.0f\t\t%d\t\t%s\n\n", c.data.productId, c.data.productName, c.data.productPrice, c.data.productStock, c.data.productCategory);
}

void printProductCell2(productCell c)
{
    printf("\t\t\t\t\t\t\t\t\tProduct Information:\n");
    printf("\t\t\t\t\t\t\t\t\t--------------------\n\n");
    printf("\t\t\t\t\t\t\t\t\t> > ID: %d\n", c.data.productId);
    printf("\t\t\t\t\t\t\t\t\t> > Name: %s\n", c.data.productName);
    printf("\t\t\t\t\t\t\t\t\t> > Unit Price: %.2f$\n", c.data.productPrice);
    printf("\t\t\t\t\t\t\t\t\t> > Stock: %d\n", c.data.productStock);
    printf("\n\t\t\t\t\t\t\t\t\t--------------------\n");
}

void printProductList(productList l)
{
    productCell * tmp = l.head;
    printf("\t\t\t\t\t\t\t\t\t     Product List:\n");
    printf("\t\t\t\t\t\t\t\t\t    ----------------\n\n");
    printf("\t\t\t\t\t\tID\t\tName\t\tPrice\t\tStock\t\tCategory\n");
    printf("\t\t\t\t\t\t--\t\t----\t\t-----\t\t-----\t\t--------\n\n");
    while(tmp != NULL)
    {
        printProductCell(*tmp);
        tmp = tmp->next;
    }
    printf("\t\t\t\t\t-----------------------------------------------------------------------------------------\n\n");
}

int nbOfProdList(productList l)
{
    int counter = 0;
    for(productCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        counter++;
    return counter;
}

/** Returns 1 if yes, 0 if no **/
int belongsIDToProdList(productList l, int id)
{
    for(productCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(tmp->data.productId == id)
            return 1;
    return 0;
}

/** Returns 1 if yes, 0 if no **/
int belongsNameToProdList(productList l, char name[])
{
    for(productCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(strcmp(tmp->data.productName, name) == 0)
            return 1;
    return 0;
}

/// NEW
productList * fillTmpProdList()
{
    Product prod;
    productList * tmpList = createProductList();
    FILE * pf = fopen("product.txt", "r");
    while(!feof(pf))
    {
        fscanf(pf, "%d %s %f %d %s", &prod.productId, prod.productName, &prod.productPrice, &prod.productStock, prod.productCategory);
        addToTailProd(tmpList, prod);
    }
    fclose(pf);
    return tmpList;
}
///

int generateProdID()
{
    static int prodID = 1000;
    productList * tmpProdList = fillTmpProdList();
    while(belongsIDToProdList(*tmpProdList, prodID) == 1)
        prodID++;

    /// free tmpList

    return prodID;
}

/** Updates the data from the product list to the file **/
void updateDataOfFileProd(Product prod)
{
    FILE * pf = fopen("product.txt", "a");
    fprintf(pf, "\n%d %s %.2f %d %s", prod.productId, prod.productName, prod.productPrice, prod.productStock, prod.productCategory);
    fclose(pf);
}

/** Saves the data from the product list to the file **/
void saveDataToFileProd(productList l)
{
    FILE * pf = fopen("product.txt", "w");
    productCell * tmp = l.head;
    while(tmp != NULL)
    {
        fprintf(pf, "\n%d %s %.2f %d %s", tmp->data.productId, tmp->data.productName, tmp->data.productPrice, tmp->data.productStock, tmp->data.productCategory);
        tmp = tmp->next;
    }
    fclose(pf);
}

void addNewProduct(categoryList * l)
{
    if(l->head == NULL)
    {
        printf("\t\t\t\t\t\t\t\t\tNo Available Categories! Please Create Some First!\n");
        return;
    }

    Product tmp;
    tmp.productId = generateProdID();

    printf("\n\t\t\t\t\t\t\t\t\tEnter the following information:\n");
    printf("\t\t\t\t\t\t\t\t\t--------------------------------\n\n");

    /// NEW tmpProdList
    productList * tmpProdList = fillTmpProdList();

    printf("\t\t\t\t\t\t\t\t\tProduct Name: ");
    scanf("%s", strlwr(tmp.productName));
    while(belongsNameToProdList(*tmpProdList, tmp.productName) == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tName Already Exist! (Enter -1 to exit)\n");
        printf("\n\t\t\t\t\t\t\t\t\tProduct Name: ");
        scanf("%s", tmp.productName);

        if(strcmp(tmp.productName, "-1") == 0)
        {
            printf("\n\t\t\t\t\t\t\t\t\t--------------------------");
            printf("\n\n\t\t\t\t\t\t\t\t\tNothing was Saved!");
            printf("\n\n\t\t\t\t\t\t\t\t\t--------------------------\n");
            return;
        }
    }

    /// free tmpProdList

    printf("\n\t\t\t\t\t\t\t\t\tPrice($): ");
    scanf("%f", &tmp.productPrice);
    printf("\n\t\t\t\t\t\t\t\t\tStock: ");
    scanf("%d", &tmp.productStock);
    printf("\t\t\t\t\t\t\t\t\t\n");


    /// NEW tmpCategList
    categoryList * tmpCategList = fillTmpCategList();
    printAvailableCateg(*tmpCategList);

    printf("\n\t\t\t\t\t\t\t\t\tCategory: ");
    scanf("%s", tmp.productCategory);
    while(belongsProdCategToCategList(*tmpCategList, tmp.productCategory) == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tCategory Not Available! (Enter -1 to exit)\n");
        printf("\n\t\t\t\t\t\t\t\t\tCategory: ");
        scanf("%s", tmp.productCategory);
        if(strcmp(tmp.productCategory, "-1") == 0)
        {
            printf("\n\t\t\t\t\t\t\t\t\t--------------------------");
            printf("\n\n\t\t\t\t\t\t\t\t\tNothing was Saved!");
            printf("\n\n\t\t\t\t\t\t\t\t\t--------------------------");
            return;
        }
    }

    /// free tmpCategList

    addToCategList(l, tmp);
    updateDataOfFileProd(tmp);

    FILE * pf = fopen("activityLog.txt", "a");
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(pf, "\nNew Product [%s] Added at %s         ------------------------", tmp.productName, asctime(timeinfo));
    fclose(pf);

    printf("\n\t\t\t\t\t\t\t\t\t--------------------------");
    printf("\n\n\t\t\t\t\t\t\t\t\tData saved successfully!");
    printf("\n\n\t\t\t\t\t\t\t\t\t--------------------------");
}

void editProduct(categoryList * categList)
{
    productList * tmpProdList = fillTmpProdList();
    printProductList(*tmpProdList);

    int prodID;
    printf("\n\t\t\t\t\t\t\t\t\tEnter the product ID: ");
    scanf("%d", &prodID);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    while(belongsIDToProdList(*tmpProdList, prodID) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tProduct ID Not Available!\n\n");
        printf("\t\t\t\t\t\t\t\t\tEnter the product ID (-1 to exit): ");
        scanf("%d", &prodID);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(prodID == -1)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }
    }

    productCell * tmpProd = tmpProdList->head;
    while(tmpProd->next != NULL && tmpProd->data.productId != prodID)
        tmpProd = tmpProd->next;

    printProductCell2(*tmpProd);

    char choice[1];

    /// Edit Name
    char newName[20];
    printf("\n\t\t\t\t\t\t\t\t\tChange Name? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Name: ");
        scanf("%s", newName);

        while(belongsNameToProdList(*tmpProdList, newName) == 1)
        {
            printf("\t\t\t\t\t\t\t\t\tName Already Exists!\n");
            printf("\n\t\t\t\t\t\t\t\t\tNew Name: ");
            scanf("%s", newName);

            strcpy(tmpProd->data.productName, newName);
        }

        printf("\n\n\t\t\t\t\t\t\t\t\tProduct Name Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t----------------------------------\n");
    }

    /// Edit Stock
    int newStock;
    printf("\n\t\t\t\t\t\t\t\t\tChange Stock? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Stock: ");
        scanf("%d", &newStock);

        tmpProd->data.productStock = newStock;

        printf("\n\n\t\t\t\t\t\t\t\t\tProduct Stock Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t-----------------------------------\n");
    }

    /// Edit Price
    float newPrice;
    printf("\n\t\t\t\t\t\t\t\t\tChange Price? (y: yes | else: no): ");
    scanf("%s", choice);
    printf("\n\t\t\t\t\t\t\t\t\t------------------------------------\n");
    if(strcmp(choice, "y") == 0)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNew Price: ");
        scanf("%f", &newPrice);

        tmpProd->data.productPrice = newPrice;

        printf("\n\n\t\t\t\t\t\t\t\t\tProduct Price Changed Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t-----------------------------------\n");
    }

    saveDataToFileProd(*tmpProdList);
    emptyTheListCateg(categList);
    fillCategoryList(categList);

    /// free tmpProdList
}

void removeProduct(categoryList * categList)
{
    productList * tmpProdList = fillTmpProdList();
    printProductList(*tmpProdList);

    int prodID;
    printf("\n\t\t\t\t\t\t\t\t\tEnter the product ID: ");
    scanf("%d", &prodID);
    printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

    while(belongsIDToProdList(*tmpProdList, prodID) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tProduct ID Not Available!\n\n");
        printf("\t\t\t\t\t\t\t\t\tEnter the product ID (-1 to exit): ");
        scanf("%d", &prodID);
        printf("\n\t\t\t\t\t\t\t\t\t~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n");

        if(prodID == -1)
        {
            printf("\t\t\t\t\t\t\t\t\tEnd Of Operation!\n");
            return;
        }
    }


    if(tmpProdList->head->data.productId == prodID)
    {
        FILE * pf = fopen("activityLog.txt", "a");
        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        fprintf(pf, "\nItem [%s] Removed at %s         ------------------------",tmpProdList->head->data.productName, asctime(timeinfo));
        fclose(pf);

        deleteHeadProd(tmpProdList);

        saveDataToFileProd(*tmpProdList);
        emptyTheListCateg(categList);
        fillCategoryList(categList);

        /// free tmpProdList
        printf("\t\t\t\t\t\t\t\t\tProduct Deleted Successfully!\n");
        printf("\t\t\t\t\t\t\t\t\t-----------------------------\n");
        return;
    }

    productCell * tmpProd = tmpProdList->head;
    while(tmpProd->next != NULL && tmpProd->next->data.productId != prodID)
        tmpProd = tmpProd->next;

    productCell * tmpDel = tmpProd->next;
    tmpProd->next = tmpProd->next->next;

    FILE * pf = fopen("activityLog.txt", "a");
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(pf, "\nProduct [%s] Removed at %s         ------------------------",tmpDel->data.productName, asctime(timeinfo));
    fclose(pf);

    free(tmpDel);

    saveDataToFileProd(*tmpProdList);
    emptyTheListCateg(categList);
    fillCategoryList(categList);

    /// free tmpProdList
    printf("\t\t\t\t\t\t\t\t\tProduct Deleted Successfully!\n");
    printf("\t\t\t\t\t\t\t\t\t-----------------------------\n");
}

void searchProduct()
{
    int counter = 0;
    char keyName[20];
    productList * tmpProdList = fillTmpProdList();
    productList * resultList = createProductList();

    printf("\t\t\t\t\t\t\t\t\tEnter a key word/character: ");
    scanf("%s", keyName);
    printf("\t\t\t\t\t\t\t\t\t---------------------------\n");

    productCell * tmpProdCell = tmpProdList->head;
    while(tmpProdCell != NULL)
    {
        if(strncasecmp(tmpProdCell->data.productName, keyName, strlen(keyName)) == 0)
        {
            addToTailProd(resultList, tmpProdCell->data);
            counter ++;
        }
        tmpProdCell = tmpProdCell->next;
    }

    if(resultList->head == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\t\tNo Result Found!!");
        printf("\n\t\t\t\t\t\t\t\t\t-----------------\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t\t\tDisplaying [%d] Result(s) Found: ", counter);
    printf("\n\t\t\t\t\t\t\t\t\t--------------------------------\n\n");

    printProductList(*resultList);
}
