#pragma once
#include "clsDate.h"

/// PRODUCT
extern int productId;
extern char productName[50];
extern char brand[50];
extern int productType;
extern float purchasePrice;
extern float sellingPrice;

/// PERSON
extern char identifier[12];
extern int personType; // 1 - Natural person / 2 - Legal entity
extern char phoneNumber[30];
extern char email[50];

/// SUPPLIER
extern int supplierId;
extern char supplierName[50];

/// CUSTOMER
extern int customerId;
extern char customerName[50];

/// PURCHASE AND SALE
extern float unitPrice;
extern float totalPrice;
extern int quantity;


void newString(char *word, int length);
void toUppercase(char* word);
int readInt();
bool dateLessThanOrEqual(Date dateRecord, Date toDate);
bool dateGreaterThanOrEqual(Date dateRecord, Date fromDate);

template <typename T>
bool isNonNegative(T number){
    if(number >= 0){
        return true;
    }else{
        return false;
    }
}

