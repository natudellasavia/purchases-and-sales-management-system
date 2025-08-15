#pragma once
#include "clsSale.h"

int saleMenu();

void addSale();
int addSaleProductId();
int addSaleCustomerId();
void addSalePrice();
void addSaleQuantity();

int modifySale();
void deactivateSale();
void saleLists();
void saleQueries();
void saleReports();

int displayWithId(Sale record);
int displayWithoutId(Sale record);

