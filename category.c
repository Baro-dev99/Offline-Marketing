#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "categ.h"
#include "product.h"

categoryList * fillTmpCategList();

categoryCell * createCategoryCell()
{
    categoryCell * c = (categoryCell*)malloc(sizeof(categoryCell));
    c->next = NULL;
    return c;
}

categoryList * createCategoryList()
{
    categoryList * l = (categoryList*)malloc(sizeof(categoryList));
    l->head = NULL;
    return l;
}

void addToHeadCateg(categoryList * l, char name[])
{
    categoryCell * c = createCategoryCell();
    c->next = l->head;
    strcpy(c->name, name);
    l->head = c;
}

void addToTailCateg(categoryList * l, char name[])
{
    if(l->head == NULL)
    {
        addToHeadCateg(l, name);
        return;
    }

    categoryCell * tmp = l->head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    categoryCell * c = createCategoryCell();
    strcpy(c->name, name);
    tmp->next = c;
}

void deleteHeadCateg(categoryList * l)
{
    if(l->head == NULL)
        return;
    categoryCell * tmp = l->head;
    l->head = l->head->next;
    free(tmp);
}

void emptyTheListCateg(categoryList * l)
{
    if(l->head == NULL)
        return;
    categoryCell * tmp = l->head;
    l->head = l->head->next;
    free(tmp);
    emptyTheListCateg(l);
}

void deleteAllOccurenceCateg(productList * prodList, char name)
{
    if(prodList->head == NULL)
        return;

    while(prodList->head != NULL && strcasecmp(prodList->head->data.productCategory, name) == 0)
    {
        printf("hello\n");
        productCell * tmp = prodList->head;
        prodList->head = prodList->head->next;
        free(tmp);
    }

    if(prodList->head == NULL)
        return;

    productCell * tmp2 = prodList->head;
    while(tmp2->next != NULL)
    {
        if(strcasecmp(tmp2->next->data.productCategory, name) == 0)
        {
            productCell * tmp3 = tmp2->next;
            tmp2->next = tmp2->next->next;
            free(tmp3);
        }
        else
            tmp2 = tmp2->next;
    }
}

/** Returns 1 if yes, 0 if no **/
int belongsProdCategToCategList(categoryList l, char prodCateg[])
{
    for(categoryCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(strcmp(tmp->name, prodCateg) == 0)
            return 1;
    return 0;
}

/** Returns 1 if yes, 0 if no **/
int belongsNameToCategList(categoryList l, char name[])
{
    for(categoryCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        if(strcmp(tmp->name, name) == 0)
            return 1;
    return 0;
}

/** Used ONLY for fillCategoryList() method **/
void addToCategList(categoryList * l, Product prod)
{
    if(l->head == NULL)
    {
        categoryCell * c = createCategoryCell(prod.productName);
        strcpy(c->name, prod.productCategory);
        l->head = c;
        c->data = createProductList();
        addToTailProd(c->data, prod);
        return;
    }

    if(belongsProdCategToCategList(*l, prod.productCategory) == 0)
    {
        categoryCell * tmp = l->head;
        while(tmp->next != NULL)
            tmp = tmp->next;
        categoryCell * c = createCategoryCell(prod.productName);
        strcpy(c->name, prod.productCategory);
        tmp->next = c;
        c->data = createProductList();
        addToTailProd(c->data, prod);
        return;
    }

    categoryCell * tmp = l->head;
    while(tmp->next != NULL && (strcmp(tmp->name, prod.productCategory) != 0))
        tmp = tmp->next;
    addToTailProd(tmp->data, prod);
}

/** Gets data from files then adds it to the list **/
void fillCategoryList(categoryList * l)
{
    Product prod;
    FILE * pf = fopen("product.txt", "r");
    while(!feof(pf))
    {
        fscanf(pf, "%d %s %f %d %s", &prod.productId, prod.productName, &prod.productPrice, &prod.productStock, prod.productCategory);
        addToCategList(l, prod);
    }
    fclose(pf);
}

void printAvailableCateg(categoryList l)
{
    printf("\t\t\t\t\t\t\t\t\tAvailable categories:\n");
    printf("\t\t\t\t\t\t\t\t\t---------------------\n\n");
    for(categoryCell * tmp = l.head; tmp != NULL; tmp = tmp->next)
        printf("\t\t\t\t\t\t\t\t\t> > > > %s\n\n", tmp->name);
    printf("\t\t\t\t\t\t\t\t\t---------------------");
}

/// NEW
categoryList * fillTmpCategList()
{
    char name[20];
    categoryList * tmpCategList = createCategoryList();
    FILE * pf = fopen("category.txt", "r");
    while(!feof(pf))
    {
        fscanf(pf, "%s", name);
        addToTailCateg(tmpCategList, name);
    }
    fclose(pf);
    return tmpCategList;
}
///

/** Updates the data from the category list to the file **/
void updateDataOfFileCateg(char name[])
{
    FILE * pf = fopen("category.txt", "a");
    fprintf(pf, "\n%s", name);
    fclose(pf);
}

/** Saves the data from the category list to the file **/
void saveDataToFileCateg(categoryList l)
{
    FILE * pf = fopen("category.txt", "w");
    categoryCell * tmp = l.head;
    while(tmp != NULL)
    {
        fprintf(pf, "\n%s", tmp->name);
        tmp = tmp->next;
    }
    fclose(pf);
}

void addNewCategory(categoryList * categList)
{
    categoryList * tmpCategList = fillTmpCategList();

    char newName[20];
    printf("\n\t\t\t\t\t\t\t\t\tEnter the new name: ");
    scanf("%s", newName);
    printf("\t\t\t\t\t\t\t\t\t-----------------------\n");

    while(belongsNameToCategList(*tmpCategList, newName) == 1)
    {
        printf("\n\t\t\t\t\t\t\t\t\tName Already Exists!\n");
        printf("\n\t\t\t\t\t\t\t\t\tEnter the new name: ");
        scanf("%s", newName);
        printf("\t\t\t\t\t\t\t\t\t-----------------------\n");
    }

    addToTailCateg(tmpCategList, newName);
    saveDataToFileCateg(*tmpCategList);
    emptyTheListCateg(categList);
    fillCategoryList(categList);

    /// free tmpCategList
    free(tmpCategList);

    FILE * pf = fopen("activityLog.txt", "a");
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(pf, "\nNew Category [%s] Added at %s         ------------------------", newName, asctime(timeinfo));
    fclose(pf);

    printf("\n\t\t\t\t\t\t\t\t\tCategory Added Successfully!\n");
    printf("\t\t\t\t\t\t\t\t\t----------------------------\n");
}
