#include <iostream>
#include <clocale>
#include "generalFunctions.h"
using namespace std;


// THESE VARIABELS ARE USED IN SUPPLIER MENU, CUSTOMER MENU, PRODUCT MENU AND PURCHASE MENU
/// PRODUCT
int productId;
char productName[50];
char brand[50];
int productType;
float purchasePrice;
float sellingPrice;

/// PERSON
char identifier[12];
int personType; // 1 - Natural person / 2 - Legal entity
char phoneNumber[30];
char email[50];

/// SUPPLIER
int supplierId;
char supplierName[50];

/// CUSTOMER
int customerId;
char customerName[50];

/// PURCHASE AND SALE
float unitPrice;
float totalPrice;
int quantity;


// To put a text with spaces into a char variable
void newString(char *word, int length) {
    int i = 0;
    fflush(stdin);
    for (i=0; i<length; i++){
        word[i] = cin.get();
        if (word[i] == '\n'){
            break;
        }
    }
    word[i] = '\0';
    fflush(stdin);
}


void toUppercase(char* word) {
    for(int i = 0; word[i] != '\0'; i++) {
        word[i] = toupper(word[i]);
    }
}


int readInt() {
    int number;
    while (true) {
        if (cin >> number) {
            return number; // If it is a cin, return the number
        } else {
            cin.clear(); // Clears the error state of cin
            cin.ignore(10000, '\n'); // Ignores up to the end of the line or 10,000 characters
            return -1;
        }
    }
}


bool dateLessThanOrEqual(Date dateRecord, Date toDate){
    if(dateRecord.getYear() < toDate.getYear()){
        return true;
    // The years are the same, so we compare the months
    }else if(dateRecord.getYear() == toDate.getYear()){
        if(dateRecord.getMonth() < toDate.getMonth()){
            return true;
        // The months are the same, so we compare the days
        }else if(dateRecord.getMonth() == toDate.getMonth()){
            if(dateRecord.getDay() <= toDate.getDay()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool dateGreaterThanOrEqual(Date dateRecord, Date fromDate){
    if(dateRecord.getYear() > fromDate.getYear()){
        return true;
    // The years are the same, so we compare the months
    }else if(dateRecord.getYear() == fromDate.getYear()){
        if(dateRecord.getMonth() > fromDate.getMonth()){
            return true;
        // The months are the same, so we compare the days
        }else if(dateRecord.getMonth() == fromDate.getMonth()){
            if(dateRecord.getDay() >= fromDate.getDay()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}
