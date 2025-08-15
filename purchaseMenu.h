 #pragma once
#include "clsPurchase.h"

int purchaseMenu();

void addPurchase();
int addProductId();
int addSupplierId();
void addPrice();
void addQuantity();

int modifyPurchase();
void deactivatePurchase();
void purchaseLists();
void purchaseQueries();

int displayWithId(Purchase record);
int displayWithoutId(Purchase record);


