#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

productCell * createProductCell(Product);

productList * createProductList();

void addToHeadProd(productList *, Product);

void addToTailProd(productList *, Product);

void deleteHeadProd(productList *);

void emptyTheListProd(productList *);

void printProductCell(productCell);

void printProductCell2(productCell);

void printProductList(productList);

int nbOfProdList(productList);

int belongsIDToProdList(productList, int);

int belongsNameToProdList(productList, char []);

productList * fillTmpProdList();

int generateProdID();

void updateDataOfFileProd(Product);

void saveDataToFileProd(productList);

void addNewProduct(categoryList *);

void editProduct(categoryList *);

void removeProduct(categoryList *);

void removeProduct(categoryList *);

void searchProduct();

#endif // PRODUCT_H_INCLUDED

