#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct Customer
{
    int customerId;     // can be generated automatically
    char firstName[20];
    char lastName[20];
    int age;
    char username[20];
    char password[30];
    char email[30];
    float cash;
    //CreditCard customerCard;
} Customer;


typedef struct customerCell
{
    Customer data;
    struct customerCell * next;
//    struct customerCell * prev;
} customerCell;


typedef struct customerList
{
    customerCell * head;
} customerList;

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

typedef struct Employee
{
    int employeeId;     // can be generated automatically
    char firstName[20];
    char lastName[20];
    char username[20];
    int age;
    char email[30];
} Employee;


typedef struct employeeCell
{
    Employee data;
    struct employeeCell * next;
//    struct employeeCell * prev;
} employeeCell;


typedef struct employeeList
{
    employeeCell * head;
} employeeList;

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


//typedef struct productNode
//{
//    Product data;
//    struct productNode * left;
//    struct productNode * right;
//} productNode;
//
//
//
//typedef struct productBTree
//{
//    productNode * root;
//} productBTree;
//
//
//typedef struct productCell
//{
//    char name[20];
//    productBTree data;
//    struct productCell * next;
//    struct productCell * prev;
//} productCell;
//
//
//typedef struct productCategoryList
//{
//    productCell * head;
//} productCategoryList;


/// NEW
typedef struct Product
{
    int productId;     // can be generated automatically
    char productName[20];
    float productPrice;
    int productStock;
    char productCategory[20];
} Product;


typedef struct productCell
{
    Product data;
    struct productCell * next;
//    struct productCell * prev;
} productCell;


typedef struct productList
{
    productCell * head;
} productList;


typedef struct categoryCell
{
    char name[20];
    productList * data;
    struct categoryCell * next;
//    struct categoryCell * prev;
} categoryCell;


typedef struct categoryList
{
    categoryCell * head;
} categoryList;

#endif // STRUCTURES_H_INCLUDED
