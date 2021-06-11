#ifndef CATEG_H_INCLUDED
#define CATEG_H_INCLUDED

categoryCell * createCategoryCell();

categoryList * createCategoryList();

void addToHeadCateg(categoryList * , char[]);

void addToTailCateg(categoryList * , char[]);

void deleteHeadCateg(categoryList * );

void emptyTheListCateg(categoryList * );

void deleteAllOccurenceCateg(productList * , char );

int belongsProdCategToCategList(categoryList , char[]);

int belongsNameToCategList(categoryList , char[]);

void addToCategList(categoryList * , Product );

void fillCategoryList(categoryList * );

void printAvailableCateg(categoryList );

categoryList * fillTmpCategList();

void updateDataOfFileCateg(char[]);

void saveDataToFileCateg(categoryList );

void addNewCategory(categoryList * );

void removeCategory(categoryList * );

#endif // CATEG_H_INCLUDED
