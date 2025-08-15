#pragma once
#include "clsProduct.h"

extern char identifier[12];
extern int personType; // 1 - Natural person / 2 - Legal entity


int productMenu();
int modifyProduct();
void deactivateProduct();
void productLists();
void productQueries();

void addProduct();
int displayWithId(Product record);
int displayWithoutId(Product record);


